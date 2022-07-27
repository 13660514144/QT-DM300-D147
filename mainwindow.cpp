#include <string>
#include <iostream>
#include <sstream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#define random(x)(rand()%x)

#pragma execution_character_set("utf-8")
using namespace std;
FILE* file;
char bott[16] = { 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f };
unsigned char key[6] = { 0x00,  0x00,  0x00,  0x00,  0x00,  0x00 };
QSettings *configsets;
QString URL;
QString ContentType;
unsigned char startBlockwrite[1]={0};//read 扇区
unsigned char blockAmountwrite[1]={0};//write 扇区

unsigned char startBlockread[1]={2};//read 磁道  要读的块的起点地址。取值范围：十六进制00-3F即00块到63
unsigned char blockAmountread [1]={0};//write 磁道  要读的块数长度值，即读多少块。取值范围01-04




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadconfig();

    // 初始化服务器
       //m_pWebSocketClinet = new WebSocketClinet;
       //m_pWebSocketClinet->connectUrl("ws://127.0.0.1:8888");
       //connect(m_pWebSocketClinet, SIGNAL(sigRecvTextMsg(QString)), this, SLOT(slotRecvTextMsg(QString)));

       help=new HelperS;
       api=new callapi;
       drivers=new driverhelper;
       //建立信号槽获取读到的卡号
       connect(drivers,SIGNAL(signCardMsg(QString)),this,SLOT(soltsetreadcode(QString)));
       qmsg=new qmessage;
        //加载背景
       //QPalette PAllbackground = this->palette();
       //QImage ImgAllbackground("FaceBackgroup.png");
       //QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
       //PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
        //setPalette(QPalette(Qt::));//设置窗口为白色背景
       //this->setPalette(PAllbackground);
       QColor color(207, 207, 207);
       //QPalette pal;
       //pal.setColor(QPalette::Window, color);
        setPalette(QPalette(color));

        QPalette pal;
        pal.setColor(QPalette::WindowText,Qt::red );
        ui->label_7->setPalette(pal);
        ui->label_8->setPalette(pal);

        pal.setColor(QPalette::WindowText,Qt::blue);
        ui->readdefault->setPalette(pal);
        ui->readcustor->setPalette(pal);

        ui->radioA->setChecked(true);
        ui->radioA->setVisible(0);
        ui->radioB->setVisible(0);

        ui->readcustor->setChecked(true);
       //定时器
       /*fTimer=new QTimer(this);
       fTimer->stop();
       fTimer->setInterval (1000) ;//设置定时周期，单位：毫秒
       connect(fTimer,SIGNAL(timeout()),this,SLOT(on_timer_timeout()));
       inittimer();*/
       connect(ui->tbview, SIGNAL(clicked(QModelIndex)), this, SLOT(onTableClicked(QModelIndex)));
       connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(showClick(QModelIndex)));
       connect(this,SIGNAL(buildtb_signal(QJsonObject)),this,SLOT(buildtb_slots(QJsonObject)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadconfig()
{
    QString iniFilePath = QCoreApplication::applicationDirPath() + "/config.ini";
    configsets=new QSettings(iniFilePath,QSettings::IniFormat);
    //设置编码，使支持中文
    configsets->setIniCodec("UTF-8");
    URL = configsets->value("APISERVER/url").toString();
    URL +=":"+configsets->value("APISERVER/port").toString();
    ContentType=configsets->value("APISERVER/Content-Type").toString();

    string _variant=configsets->value("APISERVER/startBlockwrite").toString().toStdString();
    sscanf(_variant.c_str(), "%01X", &startBlockwrite[0]);
    ui->qwritesector->setText(QString::fromStdString(_variant.c_str()));

    string _variantr1=configsets->value("APISERVER/blockAmountwrite").toString().toStdString();
    sscanf(_variantr1.c_str(), "%01X", &blockAmountwrite[0]);
    ui->qreadsector->setText(QString::fromStdString(_variantr1)+"\r\n");

    string _variantr2=configsets->value("APISERVER/startBlockread").toString().toStdString();
    int strvalue=atoi(_variantr2.c_str());
    if(strvalue<10)
    {
        sscanf(_variantr2.c_str(), "%01X", &startBlockread[0]);
    }
    else
    {
         sscanf(_variantr2.c_str(), "%02X", &startBlockread[0]);
    }

    ui->qwritetrack->setText(QString::fromStdString(_variantr2)+"\r\n");

    string _variantr3=configsets->value("APISERVER/blockAmountread").toString().toStdString();
    sscanf(_variantr3.c_str(), "%01X", &blockAmountread[0]);
    ui->qreadtrack->setText(QString::fromStdString(_variantr3)+"\r\n");

    string _variantr4=configsets->value("APISERVER/keys").toString().toStdString();
    sscanf(_variantr4.c_str(), "%02X%02X%02X%02X%02X%02X", &key[0], &key[1], &key[2], &key[3], &key[4], &key[5]);
    ui->qkeys->setText(QString::fromStdString(_variantr4)+"\r\n");


    // string _encryption=configsets->value("APISERVER/encryption").toString().toStdString();
    //sscanf(_encryption.c_str(), "%02X", &encryption[0]);

    ui->btnnext->setEnabled(false);
    ui->btnpre->setEnabled(false);
    this->setFixedSize(this->width(),this->height());

}


void MainWindow::on_btnwrite_clicked()
{
    try
    {
        bool cardflg = drivers->cardtureflg(ui->lineEdit->text().toStdString());
        if (cardflg)
        {
            bool link = drivers->Isconnect();
            if (link)
            {
                int st = 0;
                unsigned char resCardSerialNum[4] = { 0 };
                string code = ui->lineEdit->text().toStdString();
                int lg=code.length();
                /*if(code.substr(0,1)=="0")
                {
                    code=code.substr(1,lg-1);
                }*/
               // string strs = CT2A(code.GetBuffer()); //转化为非unicode.
               // string str1 = code.substr(0, 3);
               // string str2 = code.substr(3, 5);
               // long head = atoi(str1.c_str());
                unsigned int  bottom = atoi(code.c_str());
                //srand((int)time(0));
                //int rands = random(15);
                char* p=drivers->_10_to_16(bottom);
                //string st2 = drivers->DecIntToHexStr(bottom);//转16进制
                string st2=p;
                int strlen=st2.length();
                if(st2.length()==1)
                {
                     st2="0000000"+st2;
                }
                else if(st2.length()==2)
                {
                     st2="000000"+st2;
                }
                else if(st2.length()==3)
                {
                     st2="00000"+st2;
                }
                else if(st2.length()==4)
                {
                    st2="0000"+st2;
                }
                else if(st2.length()==5)
                {
                    st2="000"+st2;
                }
                else if(st2.length()==6)
                {
                    st2="00"+st2;
                }
                else if(st2.length()==7)
                {
                    st2="0"+st2;
                }
                ui->msgline->setText("转16进制=>"+QString::fromStdString(st2));
                char MAC[4];
                sscanf(st2.c_str(), "%02X%02X%02X%02X", &MAC[0], &MAC[1], &MAC[2], &MAC[3]);


                unsigned char cdata[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x04, 0x00, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69 };

                cdata[0] = MAC[3];
                cdata[1] = MAC[2];
                cdata[2] = MAC[1];
                cdata[3] = MAC[0];
                cdata[4] =0x00;// (unsigned char)bott[rands];

                int ft = ControlBuzzerTest(0, 1, 1);

                //memcpy(startBlock, &_startBlock[0], _startBlock.size());
                st = MFHLWrite(0, 1, 0, blockAmountread[0], startBlockread[0], key, cdata, 16, resCardSerialNum);

                if (st == 0)
                {
                     qmsg->QMsg("写卡成功");
                     ui->writecode->setText("");
                     ui->readcode->setText("");
                     ui->lineEdit->setText("");
                     ui->msgline->setText("写卡成功："+QString::fromStdString(code));
                }
                else
                {
                    qmsg->QmsgErr(st);
                    ui->writecode->setText("");
                    ui->readcode->setText("");
                    ui->lineEdit->setText("");
                    ui->msgline->setText("写卡失败："+QString::fromStdString(code));
                }
            }           
        }
    }
    catch (std::exception& ex)
    {
        qmsg->QMsginfo("错误信息",ex.what());
    }
}


void MainWindow::on_btnread_clicked()
{
    try
    {
        int st = 0;

        unsigned char cardSetialNum[4] = { 0 };
        unsigned char data[16] = { 0 };
        unsigned short dataLength = 0;
        bool link = drivers->Isconnect();
        if (!link)
        {
            return;
        }
        if(ui->readcustor->isChecked())
        {
            st = MFHLRead(0, 1, 0, blockAmountread[0], startBlockread[0], key, cardSetialNum, data, &dataLength);
        }
        else
        {
            st = MFHLRead(0, 1, 0, blockAmountread[0], 0, key, cardSetialNum, data, &dataLength);
        }
        int ft = ControlBuzzerTest(0, 1, 1);
        if (st != 0)
        {
            qmsg->QmsgErr(st);
        }
        else
        {
            qmsg->QMsg("读卡成功");
            drivers->readcodechange147(data);            
        }
    }
    catch (std::exception& ex)
    {
        qmsg->QMsginfo("错误信息",ex.what());
    }
}


void MainWindow::on_getgroup_clicked()
{
    ItemModel = new QStandardItemModel(this);

           QStringList strList;
           strList.append("公司A");
           strList.append("公司B");
           strList.append("C");
           strList.append("D");
           strList.append("E");
           strList.append("F");
           strList.append("G");

           int nCount = strList.size();
           for(int i = 0; i < nCount; i++)
           {
               QString string = static_cast<QString>(strList.at(i));
               QStandardItem *item = new QStandardItem(string);
               ItemModel->appendRow(item);
           }
          ui->listView->setModel(ItemModel);          
}
void MainWindow::showClick(QModelIndex index)
{
    QString strTemp;
    strTemp = index.data().toString();
    qmsg->QMsg(strTemp);
}

void MainWindow::on_buildview_clicked()
{
    try
    {
        PageMothed=CurrentMothed="first";
        LastId="";
        QString API=configsets->value("APISERVER/controller_map").toString();
        pagejobject=api->sendPostRequest(URL+API,help->buildjson(LastId,PageMothed),ContentType);
        emit buildtb_signal(pagejobject);
    }
    catch (std::exception& ex)
    {
        qmsg->QMsginfo("错误信息",ex.what());
    }
}
void MainWindow::buildtb_slots(QJsonObject json)
{
    pagejarray=json.value("data").toArray();
    QJsonObject jsonValue=pagejarray.at(0).toObject();
    int headnum=jsonValue.count();
    int arraynum=pagejarray.count();
    pagenum=arraynum;
    if(pagenum<=0) return;

    QString topid=jsonValue.value("_id").toString();
    jsonValue=pagejarray.at(pagenum-1).toObject();
    QString bottid=jsonValue.value("_id").toString();

    if(pagenum==20 && CurrentMothed=="first")
    {
        ui->btnpre->setEnabled(false);
        ui->btnnext->setEnabled(true);        
    }
    else if(pagenum==20 && CurrentMothed=="next")
    {
        ui->btnpre->setEnabled(true);
        ui->btnnext->setEnabled(true);
    }
    else if(pagenum<20 && CurrentMothed=="first")
    {
        ui->btnpre->setEnabled(false);
        ui->btnnext->setEnabled(false);
    }
    else if(pagenum<20 && CurrentMothed=="next")
    {
        ui->btnpre->setEnabled(true);
        ui->btnnext->setEnabled(false);
    }
    else if(pagenum<20 && CurrentMothed=="pre")
    {
        ui->btnpre->setEnabled(false);
        ui->btnnext->setEnabled(true);
    }
    else if(pagenum==20 && CurrentMothed=="pre")
    {
        ui->btnpre->setEnabled(true);
        ui->btnnext->setEnabled(true);
    }
    getlastid(bottid,topid);
    //qmsg->QMsg(LastId + "->"+bottid+"->"+topid+"->"+QString::number(pagenum-1));
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(headnum);
    int cells=0;
    ui->tbview->setAlternatingRowColors(true);
        //根据内容自动调整列宽
        ui->tbview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        QJsonObject::Iterator it;
        for(it=jsonValue.begin();it!=jsonValue.end();it++)
        {
             model->setHorizontalHeaderItem(cells, new QStandardItem(QString::fromStdString(it.key().toStdString())));
             cells ++;
        }
        ui->tbview->setModel(model);
        //表头信息显示居中
        ui->tbview->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
        int cols=0;
        for(int x=0;x<arraynum;x++)
        {
            jsonValue=pagejarray.at(x).toObject();
            for(it=jsonValue.begin();it!=jsonValue.end();it++)
            {
                model->setItem(x,cols,new QStandardItem(it.value().toString()));
                cols ++;
            }
            cols=0;
        }
}
void MainWindow::getlastid(QString bottid,QString topid)
{
    int cflg=CurrentMothed=="first" ? 0 : (CurrentMothed=="next" ? 1 : 2);
    int pflg=PageMothed   =="first" ? 0 : (PageMothed   =="next" ? 1 : 2);
    if(pagenum==20)
    {
        switch (cflg) {
        case 0:
            LastId=bottid;
            break;
        case 1:
            if(PageMothed=="next")
            {
                LastId=bottid;
            }
            else if(PageMothed=="pre")
            {
                 LastId=topid;
            }
            break;
        case 2:
            if(PageMothed=="next")
            {
                LastId=topid;
            }
            else if(PageMothed=="pre")
            {
                 LastId=bottid;
            }
            break;
        }
    }
    else
    {
        switch (cflg) {
        case 0:
            LastId="";
            break;
        case 1:
            LastId=topid;
            break;
        case 2:
            LastId=topid;
            break;
        default:
            break;
        }
    }
}
void MainWindow::onTableClicked(QModelIndex index)
{
    int row=index.row();
    qmsg->QMsginfo("row",QString::number(row));
    QString cellText = index.data().toString();
    qmsg->QMsginfo("data",cellText);
}

void MainWindow::slotSendMsg()
{
    QString content = ui->msgline->text(); //获取单行文本框内要发送的内容
        if(!content.isEmpty())
        {
            QDateTime datetime = QDateTime::currentDateTime();
            QString str = "send to server : " + datetime.toString("yyyy-M-dd hh:mm:ss") + tr("\n");
            str += content;
            //listwidget->addItem(str);   // 将要发送的内容显示在listwidget
            m_pWebSocketClinet->sendTextMsg(str); // 发送消息到服务器
        }
        else
        {
            qmsg->QMsginfo("错误", "不能发送空消息!");
        }
}

void MainWindow::slotRecvTextMsg(QString sMessage)
{
    // 加上时间帧
       QDateTime datetime = QDateTime::currentDateTime();
       QString str = tr("recv from server : \n") + datetime.toString("yyyy-M-dd hh:mm:ss") + tr("\n");
       str += sMessage;       
       qmsg->QMsginfo("消息", sMessage);
       //ui->msglbl->clear();
       //ui->msglbl->setStyleSheet("color:white");
       //ui->msglbl->setText(str);
}

void MainWindow::soltsetreadcode(QString code)
{
    ui->lineEdit->setText(code );
    ui->writecode->setText(code+"\r\n");
}

void MainWindow::inittimer()
{
    fTimer->start () ;//定时器开始工作
}

void MainWindow::stoptimer()
{
    fTimer->stop () ; //定时器停止
    //int tmMsec=fTimeCounter.elapsed() ;//毫秒数
}
/*
void MainWindow::on_timer_timeout()
{
    //定时器中断响
    QDateTime qdate = QDateTime::currentDateTime();
    QTime curTime=QTime::currentTime(); //获取当前时间
    ui->msgline->setText(qdate.toString("yyyy年MM月dd日-hh:mm:ss"));
}
*/


void MainWindow::on_btnpre_clicked()
{
    //if(pagenum=20)
    //{
    PageMothed=CurrentMothed;
        QString API=configsets->value("APISERVER/controller_map").toString();
        CurrentMothed="pre";
        pagejobject=api->sendPostRequest(URL+API,help->buildjson(LastId,PageMothed),ContentType);        
        emit buildtb_signal(pagejobject);
    //}
}

void MainWindow::on_btnnext_clicked()
{
    //if(pagenum=20)
    //{
    PageMothed=CurrentMothed;
        QString API=configsets->value("APISERVER/controller_map").toString();
        CurrentMothed="next";
        pagejobject=api->sendPostRequest(URL+API,help->buildjson(LastId,PageMothed),ContentType);        
        emit buildtb_signal(pagejobject);
    //}
}

void MainWindow::on_btnconfigread_clicked()
{
    QString iniFilePath = QCoreApplication::applicationDirPath() + "/config.ini";
    configsets=new QSettings(iniFilePath,QSettings::IniFormat);
    string _startBlockread=ui->qwritetrack->toPlainText().toStdString();
    string _blockAmountread=ui->qreadtrack->toPlainText().toStdString();
    string _keys=ui->qkeys->toPlainText().toStdString();

    bool flg=drivers->trackflg(_startBlockread);
    if(flg==false)
    {
        return;
    }

    configsets->beginGroup("APISERVER");
    configsets->setValue("startBlockread",QString::fromStdString(_startBlockread));
    //configsets->setValue("blockAmountread",QString::fromStdString(_blockAmountread));
    configsets->setValue("keys",QString::fromStdString(_keys));
    configsets->endGroup();
    int strvalue=atoi(_startBlockread.c_str());
    if(strvalue>9)
    {
        sscanf(_startBlockread.c_str(), "%02X", &startBlockread[0]);
    }
    else
    {
        sscanf(_startBlockread.c_str(), "%01X", &startBlockread[0]);
    }

    sscanf(_keys.c_str(), "%02X%02X%02X%02X%02X%02X", &key[0], &key[1], &key[2], &key[3], &key[4], &key[5]);
    qmsg->QMsginfo("提示","保存成功");
}

void MainWindow::on_btnactive_clicked()
{
     bool link = drivers->Isconnect();
     if(!link)
     {
         return;
     }
     int ft = ControlBuzzerTest(0, 1, 1);
     int st = 0;
     st= SetWorkmode (0, 1);
     qmsg->QmsgErr(st);

/*
    D147AutoReadheaderParameters paramtersBean;
    paramtersBean.TypeASnrSelect=0x00;
    paramtersBean.UsbTypeAdirection=0x00;
    paramtersBean.Usb4byteTypeAstartbyte=0x00;
    paramtersBean.Usb8byteTypeAstartbyte=0x00;
    paramtersBean.AplusSnrSelect=0x00;
    paramtersBean.UsbAplusdirection=0x00;
    paramtersBean.UsbAplusstartbyte=0x00;
    paramtersBean.MifareContentSelect=0x01;					// 1 读取MF内容
    paramtersBean.MifareOneBlockaddress=startBlockread[0];				// 块号地址
    paramtersBean.MifareOneKeyType=0x60;
    // 验证密钥类型  0x60 验证A  0x61 验证B
    memcpy(paramtersBean.MifareOneKey,key,6);

    if(ui->radioA->isChecked())
    {
        paramtersBean.UsbMifaredirection=0x00;//正序
         paramtersBean.UsbMifarestartByte=0x00;
    }
    else
    {
        paramtersBean.UsbMifaredirection=0x01;//反序
         paramtersBean.UsbMifarestartByte=0x04;
    }					// 正反序    0 正序  1反序
                // 起始字节
    paramtersBean.AplusContentSelect=0x00;
    paramtersBean.AplusBlockaddress=0x00;
    paramtersBean.AplusKey[4]={0};
    paramtersBean.UsbAplusContentdirection=0x00;
    paramtersBean.UsbAplusContentstartByte=0x00;
    paramtersBean.FM1208ContentSelect=0x00;
    UCHAR FM1208MFID[2]={0x00,0x00};
    UCHAR FM1208EFID[2]={0x00,0x00};
    paramtersBean.FM1208Offset=0x00;
    paramtersBean.FM1208EXITAUTHKey[16]={0};
    paramtersBean.UsbFM1208direction=0x00;
    paramtersBean.UsbFM1208startByte=0x00;
    paramtersBean.UsbMode=34;
    st=SetD147AutoWorkParameters(0,&paramtersBean);
    if(st!=0)
    {
         qmsg->QmsgErr(st);
    }
    else
    {
         qmsg->QMsginfo("提示","设置工作参数成功");
    }
*/
}

void MainWindow::on_btpassive_clicked()
{
    bool link = drivers->Isconnect();
    if(!link)
    {
        return;
    }
    int st = 0;
    int ft = ControlBuzzerTest(0, 1, 1);
    st= SetWorkmode (0, 0);
    qmsg->QmsgErr(st);

}

void MainWindow::on_radioA_clicked()
{
    ui->radioA->setChecked(true);
    ui->radioB->setChecked(false);
}

void MainWindow::on_radioB_clicked()
{
    ui->radioB->setChecked(true);
    ui->radioA->setChecked(false);
}
//擦除配置块类容
void MainWindow::on_pushButton_clicked()
{
    bool link = drivers->Isconnect();
    if (link)
    {
        int st = 0;
        unsigned char resCardSerialNum[4] = { 0 };

        unsigned char cdata[32] = { 0 };
        unsigned char ddata[48] = { 0 };
        unsigned char skey[6]={0x00,0x00,0x00,0x00,0x00,0x00};
        int ft = ControlBuzzerTest(0, 1, 1);
        unsigned char area=0;
        //st = MFHLWrite(0, 1, 0, blockAmountread[0], startBlockread[0], key, cdata, 16, resCardSerialNum);
        for(int x=0;x<16;x++)
        {
            if(x==0)
            {
                st = MFHLWrite(0, 1, 0, 2, 1, key, cdata, 32, resCardSerialNum);
            }
            else
            {
                area=(unsigned char)x*4;
                st = MFHLWrite(0, 1, 0, 3, area, key, ddata, 48, resCardSerialNum);
            }
        }
        if (st == 0)
        {
             qmsg->QMsg("擦除卡成功");
             ui->writecode->setText("");
             ui->readcode->setText("");
             ui->lineEdit->setText("");
             ui->msgline->setText("擦除卡成功");
        }
        else
        {
            qmsg->QmsgErr(st);
            ui->writecode->setText("");
            ui->readcode->setText("");
            ui->lineEdit->setText("");
            ui->msgline->setText("擦除卡失败：");
        }
    }
}
