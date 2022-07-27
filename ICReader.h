#include <uchar.h>
#ifndef __IC_READER_H_
#define __ID_ERADER_H_

#ifndef CallReader	
#define CallReader			__stdcall
#else
#define	CallReader			__cdecl
#endif

#ifdef	READER
#define ReaderDLL			extern "C"	__declspec(dllexport)
#else
#define	ReaderDLL			extern "C"	__declspec(dllimport)
#endif
typedef unsigned char BYTE;
typedef unsigned char UCHAR;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned short UINT;
typedef struct D147_AUTO_READ_HEADER_PARAMETERS
{
	unsigned char TypeASnrSelect;
	unsigned char UsbTypeAdirection;
	unsigned char Usb4byteTypeAstartbyte;
	unsigned char Usb8byteTypeAstartbyte;
	unsigned char AplusSnrSelect;
	unsigned char UsbAplusdirection;			
	unsigned char UsbAplusstartbyte;
	unsigned char MifareContentSelect;					// 1 读取MF内容
	unsigned char MifareOneBlockaddress;				// 块号地址
	unsigned char MifareOneKeyType;						// 验证密钥类型  0x60 验证A  0x61 验证B
	unsigned char MifareOneKey[6];						// 验证密码
	unsigned char UsbMifaredirection;					// 正反序    0 正序  1反序
	unsigned char UsbMifarestartByte;					// 起始字节
	unsigned char AplusContentSelect;
	unsigned char AplusBlockaddress;
	unsigned char AplusKey[4];
	unsigned char UsbAplusContentdirection;
	unsigned char UsbAplusContentstartByte;
	unsigned char FM1208ContentSelect;
    UCHAR FM1208MFID[2];
    UCHAR FM1208EFID[2];
	unsigned char FM1208Offset;
	unsigned char FM1208EXITAUTHKey[16];
	unsigned char UsbFM1208direction;
	unsigned char UsbFM1208startByte;
	unsigned char UsbMode;
}D147AutoReadheaderParameters;


//错误代码
#define DEVICE_ERROR_OK					 0		/* 成功 */
#define DEVICE_ERROR_OUT_OF_INDEX		-1		/* 索引越界或没有找到合适的索引值 */
#define DEVICE_ERROR_OUT_OF_SIZE		-2		/* 提供的Buffer长度数据错误 */
#define DEVICE_ERROR_INVALID_HANDLE		-3		/* 无效句柄 */
#define DEVICE_ERROR_INVALID_ADDR		-4		/* 无效地址*/
#define DEVICE_ERROR_INVALID_DATA		-5		/* 无效数据*/
#define DEVICE_ERROR_NO_MEM				-6		/* 申请内存失败 */
#define DEVICE_ERROR_NOT_SUPPORTED		-7		/* 不提供该支持 */
#define DEVICE_ERROR_DATA_CODE			-8		/* 数据编码错误 */
#define DEVICE_ERROR_DATA				-9		/* 数据错误 */
#define DEVICE_ERROR_DATA_TOO_LONG		-10		/* 数据太长 */
#define DEVICE_ERROR_NO_DATA			-11		/* 没有数据 */
#define DEVICE_ERROR_PARAMTER			-12		/* 参数错误 */
#define DEVICE_ERROR_TIMEOUT			-13		/* 超时 */
#define DEVICE_ERROR_CMD_EXIST			-14		/* 设备命令已经存在 */
#define DEVICE_ERROR_NO_CONNECT			-15		/* USB或串口未连接 */
#define DEVICE_ERROR_CARD_ERRPR			-16		/* 非接卡操作错误 */
#define DEVICE_ERROR_PSAM_ERRPR			-17		/* PSAM卡操作错误 */

//API

//1、释放USB
ReaderDLL int CallReader USBHidExitCommunicate();

//2、USB通讯初始化
ReaderDLL int CallReader USBHidInitCommunicate();

//3、3DES解密
ReaderDLL void CallReader Triple3DESDecrypt(unsigned char  *Key,unsigned char  *Source, unsigned char  *result);

//4、3DES加密
ReaderDLL void CallReader Triple3DES(unsigned char *key, unsigned char *src,unsigned char *outData);
 
//5、DES加密
ReaderDLL void CallReader SingleDES(unsigned char *key, unsigned char *s_test, unsigned char *d_text);

//6、DES解密
ReaderDLL void CallReader SingleDESDecrypt(unsigned char *key, unsigned char *s_test,unsigned char *d_text);

//7、获取器件通信地址
ReaderDLL int CallReader GetAddress(unsigned char addr, unsigned char *addrData);

//8、得到器件固件版本号
ReaderDLL int CallReader GetSoftwareVersion(unsigned char addr, unsigned char *version, UCHAR maxLen);

//9、设置器件通讯地址
ReaderDLL int CallReader SetAddress(unsigned char addr, unsigned char setAddr);

//10、设置器件8字节序列号
ReaderDLL int CallReader SetReaderSerialNum(unsigned char addr, unsigned char *serNum, unsigned char serialLen);

//11、读取器件八字节序列号
ReaderDLL int CallReader GetReaderSerialNum(unsigned char addr, unsigned char *getNum, unsigned char *serialLen, UCHAR maxLen);

//12、获取硬件版本号
ReaderDLL int CallReader GetHardwareVersion(unsigned char addr, unsigned char *version, UCHAR maxLen);

//13、启射频天线
ReaderDLL int CallReader OpenRFAntenna(unsigned char addr); 

//14、关闭射频天线
ReaderDLL int CallReader CloseRFAntenna(unsigned char addr);

//15、获取读到卡片的物理UID，只要是设备支持的卡片均会有返回
ReaderDLL int CallReader GetModuleSupportCardUID(unsigned char addr, UCHAR *uid, UCHAR *uidLen, UCHAR *cardType, UCHAR maxLen);

//16、蜂鸣器测试
ReaderDLL int CallReader ControlBuzzerTest(UCHAR addr, UCHAR time, UCHAR cycleCount);

//17、LED测试
ReaderDLL int CallReader ControlLedTest(UCHAR addr, UCHAR time, UCHAR cycleCount);

//18、版权信息
ReaderDLL int CallReader GetCopyrightInformations(unsigned char *data, unsigned char *recLen, unsigned char maxLen);

//19、寻卡
ReaderDLL int CallReader MFRequest(unsigned char addr, unsigned char mode);

//20、防碰撞
ReaderDLL int CallReader MFAnticoll(UCHAR addr, UCHAR layer, UCHAR *cardCount, UCHAR *cardNum);

//21、选择卡片
ReaderDLL int CallReader MFSelect(UCHAR addr, UCHAR layer, UCHAR *cardNum, UCHAR *sak, UCHAR *cardChipNum);

//22、获取卡号
ReaderDLL int CallReader MFGetCardID(unsigned char addr,												//设备地址					
	unsigned char *cardType,	
	unsigned char *cardSnr,												//返回卡片序列号						
	unsigned char *snrLen,												//长度
	unsigned char maxLen
	);

//23、ISO15693_Inventory
ReaderDLL int CallReader ISO15693Inventory(unsigned char addr, unsigned char flags, unsigned char afi, unsigned char masklength,
	unsigned char *maskvalue, unsigned char *cardID);


//24、获取CPU卡UID    //只读CPU卡的UID，其他卡不读
ReaderDLL int CallReader GetTypeACpuCardUID(UCHAR addr, UCHAR *cpuCardType, UCHAR *uid, UCHAR *uidLength, UCHAR maxLen);

//25、读取身份证序列号
ReaderDLL int CallReader GetTypeBCardUID(UCHAR addr, UCHAR *uid, UCHAR *uidLength, UCHAR maxLen);

//26、获取Felica UID
ReaderDLL int CallReader GetFelicaCardUID(UCHAR addr, UCHAR *uid, UCHAR *uidLength, UCHAR maxLen);

//27、获取HID Iclass uid
ReaderDLL int CallReader GetHIDIClassUID(UCHAR addr, UCHAR *uid, UCHAR *uidLength, UCHAR maxLen);

//28、ICODE 读多标签
ReaderDLL int CallReader ISO15693FastGetUID(UCHAR addr, UCHAR *uidCount, UCHAR *uidBuffer, UCHAR maxLen);

//29、ICODE 读
ReaderDLL int CallReader ISO15693Read(unsigned char addr, unsigned char flags, unsigned char blockAddr,
	unsigned char blockCount, unsigned char *UID, unsigned char *recData, unsigned char *recLength, unsigned char maxLen);

//30、ISO15693_Write
ReaderDLL int CallReader ISO15693Write(unsigned char addr, unsigned char flags, unsigned char blockAddr,
	unsigned char blockCount, unsigned char *UID, unsigned char *writeData, unsigned char writeLength);

//31、读卡
ReaderDLL int CallReader MFHLRead(unsigned char addr,												//设备地址
	unsigned char requestMode,										//请求模式										
	unsigned char authMode,											//密钥认证模式
	unsigned char blockAmount,										//块数量
	unsigned char startBlock,										//块号起始地址
	unsigned char *key,												//密钥
	unsigned char *resCardSerialNum,									//返回卡号
	unsigned char *cardData,											//返回块数据
	unsigned short *cardDataLen										//块数据长度
	);

//32、写卡
ReaderDLL int CallReader MFHLWrite(unsigned char addr,													//设备地址
	unsigned char requestMode,											//请求模式
	unsigned char authMode,												//密钥认证模式										
	unsigned char blockAmount,											//块长度
	unsigned char startBlock,											//块起始地址	
	unsigned char *key,													//密钥	
	unsigned char *cardData,												//写入数据
	unsigned short cardDataLen,											//写入数据长度					
	unsigned char *resCardSerialNum										//返回卡号
	);

//33、值块初始化
ReaderDLL int CallReader MfHLInitVal(unsigned char addr,												//设备地址
	unsigned char requestMode,										//请求模式	
	unsigned char authMode,											//密钥认证模式
	unsigned char sector,												//操作扇区号
	unsigned char *key,												//密钥
	int initValue,													//块初值
	unsigned char *resCardSerialNum									//返回序列号
	);

//34、充值
ReaderDLL int CallReader MfHLIncrement(unsigned char addr,																//设备地址						
	unsigned char requestMode,														//请求模式
	unsigned char authMode,															//密钥认证模式
	unsigned char sector,															//扇区位置
	unsigned char *key,																//密钥
	int incrementVlaue,																//操作数值
	unsigned char *resCardSerialNum,												//返回卡片序列号
	int *afterValue																	//操作后的数值
	);

//35、扣款
ReaderDLL int CallReader MfHLDecrement(unsigned char addr,														//设备地址
	unsigned char requestMode,												//请求模式
	unsigned char authMode,													//密钥认证模式			
	unsigned char sector,													//操作函数
	unsigned char *key,														//密钥	
	int decrementValue,														//操作数值
	unsigned char *resCardSerialNum,										//返回数据
	int *afterValue															//操作后的卡片数值
	);

//36、PSAM卡复位
ReaderDLL int CallReader PsamCpuReset(unsigned char addr, UCHAR samSlot, unsigned char *resData, UCHAR *len, UCHAR maxLen);

//37、PSAM通道
ReaderDLL int CallReader PsamApduTransfer(unsigned char addr, UCHAR samSlot, unsigned char *apduCmd, unsigned char apduCmdLength, unsigned char *resData, UCHAR *resDataLen, UCHAR maxLen);

//38、复位
ReaderDLL int CallReader TypeACpuReset(unsigned char addr, unsigned char *resData, unsigned char *resDataLen, UCHAR maxLen);

//39、TYPEA 通道
ReaderDLL int CallReader TypeAApduTransfer(unsigned char addr, unsigned char *apduCmd, unsigned char apduCmdLength, unsigned char *resData, UCHAR *resDataLen, UCHAR maxLen);

//40、获取软件版本号
ReaderDLL int CallReader GetBootladerVersion(unsigned char addr, UCHAR *verison, UCHAR *versionLength, UCHAR maxLen);

//41、擦除Flash
ReaderDLL int CallReader EarseFlashApp(unsigned char addr);

//42、检查烧写是否成功
ReaderDLL int CallReader CheckBootloader(unsigned char addr, int startAddr, UINT fileSize, UINT checkSum);

//43、写Flash
ReaderDLL int CallReader WriteFlash(unsigned char addr, int startAddr, int length, unsigned char *outputStream, unsigned char outputStreamLength);

//44、跳转执行App
ReaderDLL int CallReader SwitchApp(unsigned char addr);

//45、设置工作模式
ReaderDLL int CallReader SetWorkmode(unsigned char addr, UCHAR workMode);

//46、获取工作模式
ReaderDLL int CallReader GetWorkmode(unsigned char addr, UCHAR *workMode);

//47、设置主动工作参数
ReaderDLL int CallReader SetAutoModuleWorkParameters(UCHAR addr, UCHAR UID, UCHAR ID, UCHAR contentType, UCHAR *content, UCHAR contentLength);

//48、获取主动工作参数
ReaderDLL int CallReader GetModuleAutoWorkParameters(unsigned char addr, UCHAR *cardType, unsigned char *parameters, unsigned char *parametersLength, UCHAR maxLen);

//49、Ultralight卡操作
ReaderDLL int CallReader ReadUltralight(unsigned char addr, unsigned char page, unsigned char *data);

//50、Ultralight卡操作
ReaderDLL int CallReader WriteUltralight(unsigned char addr, unsigned char page, unsigned char *data);

//51、Ntag卡操作
ReaderDLL int CallReader ReadNtag(unsigned char addr, unsigned char page, unsigned char *data);

//52、Ntag卡操作
ReaderDLL int CallReader WriteNtag(unsigned char addr, unsigned char page, unsigned char *data);

//53、Ntag 读版本信息
ReaderDLL int CallReader GetNtagVersion(unsigned char addr, unsigned char *version, UCHAR *verLen, unsigned char maxLen);

//54、Ntag 连续读读Page
ReaderDLL int CallReader ReadNtagforFast(unsigned char addr, unsigned char startPage, unsigned char endPage, unsigned char *data, unsigned char *recLen, unsigned char maxLen);

//55、Ntag 兼容性写
ReaderDLL int CallReader WriteNtagCompatiblity(unsigned char addr, unsigned char startPage, unsigned char *data, unsigned char writeLen);

//56、读取Ntag NFC 计数器值
ReaderDLL int CallReader ReadNtagforNFCCnt(unsigned char addr, unsigned char *nfcCountValue);

//57、读取Ntag 特定的ECC签名
ReaderDLL int CallReader ReadNtagSigName(unsigned char addr, unsigned char *sigName, unsigned char *dataLen, unsigned char maxLen);

/************************  Desfire卡操作 **********************************/
//58、Desfire格式化
ReaderDLL int CallReader DesfireHLFormat(BYTE addr, BYTE cid, BYTE keyType, BYTE *keyData);

//59、获取Desfire UID
ReaderDLL int CallReader DesfireHLGetUID(BYTE addr, BYTE *cardType, BYTE *uid, BYTE *uidLength, BYTE maxLen);

//60、Desfire获取容量
ReaderDLL int CallReader DesfireHLGetFreMemory(BYTE addr, int *mem);

//61、Defire高阶创应用
ReaderDLL int CallReader DesfireHLCreateApplication(		
	BYTE addr,							//设备地址
	BYTE cid, 							//通道号, 一般为0x01
	BYTE mainKeyType, 					//卡片主密钥加密类型    	  	 0—DES/3DES, 2—AES
	BYTE *mainKeyData, 					//AID 0密钥
	int AID, 							//子应用号
	BYTE masterKeySettings, 			//子应用密钥设置
	BYTE keyType, 						//子应用主密钥类型
	BYTE keyVersion,					//子应用密钥版本号
	BYTE *newKeyData, 					//子应用主密钥数据
	BYTE keyNum);						//子应用密钥个数，最多为14个，初始化为全为0x00

//62、Desfire获取应用个数								
ReaderDLL int CallReader DesfireHLGetApplication(
	BYTE addr, 								 //设备地址
	BYTE cid,								 //通道号, 一般为0x01
	BYTE keyType,							 //AID 0密钥类型
	BYTE *keyData,							 //AID 0主密钥数据
	BYTE *aidDataNum,						 //返回AID数量
	int *aidData,							 //返回AID数据
	BYTE maxLen);

//63、Desfire删除应用
ReaderDLL int CallReader DesfireHLDeleteApplication(
	BYTE addr, 								 //设备地址
	BYTE cid,								 //通道号, 一般为0x01
	int AID,								 //需要删除的子应用应用号
	BYTE keyType,							 //AID 0主密钥类型
	BYTE *keyData);							 //AID 0主密钥数据

//64、Defire高阶创文件																	
ReaderDLL int CallReader DesfireHLCreateFile(
	BYTE addr, 								 //设备地址
	BYTE cid,								 //通道号, 一般为0x01
	int AID,								 //子应用编号
	BYTE keyNo,								 //子应用主密钥编号 一般为0	
	BYTE keyType,							 //子应用主密钥类型
	BYTE *keyData,							 //子应用主密钥数据 
	BYTE fileID, 							 //文件ID
	BYTE fileType,							 //文件类型
	BYTE commType,							 //文件的通讯方式	0: Plain; 1: MACing;      	3: Full Enciphered; 
	BYTE keyNoFile1, 						 //更改文件的密钥KeyNO 和 读写文件KeyNo。
	BYTE keyNoFile2,						 //文件类型       写文件KeyNo， 读文件KeyNo
	DWORD fileSpace,						 //文件大小
	DWORD minValue,							 //最小值，4字节的整数，不能为负.
	DWORD maxValue,						 	 //最大值，4字节的整数
	DWORD initValue,						 //初始值
	BYTE creditFlag,						 //是否使用信用标志 0 不使用 1 使用
	DWORD oneRecordLen, 					 //一个记录的大小，4字节的整数
	DWORD maxRecordNum);					 //最大记录数

//65、Desfire获取应用文件个数
ReaderDLL int CallReader DesfireHLGetFile(
	BYTE addr, 								 //设备地址
	BYTE cid,								 //通道号, 一般为0x01
	int AID,								 //子应用编号
	BYTE keyNo,								 //子应用主密钥编号 一般为0		
	BYTE keyType,							 //子应用主密钥类型
	BYTE *keyData,							 //子应用主密钥数据
	BYTE *fileIdNum,						 //返回file数量
	BYTE *fileIdData,						 //返回file数据
	BYTE maxLen);

//66、Desfire删除应用文件
ReaderDLL int CallReader DesfireHLDeleteFile(
	BYTE addr,								 //设备地址
	BYTE cid,								 //通道号, 一般为0x01
	int AID,								 //子应用编号
	BYTE keyNo, 							 //子应用主密钥编号 一般为0		
	BYTE keyType,							 //子应用主密钥类型
	BYTE *keyData,							 //子应用主密钥数据
	BYTE fileID);							 //删除文件的ID

//67、Defire高阶获取值文件value值
ReaderDLL int CallReader DesfireHLGetValue(
	BYTE addr,								 //设备地址
	BYTE cid,								 //通道号, 一般为0x01
	int AID,								 //子应用编号
	BYTE keyNo, 							 //子应用主密钥编号 一般为0		 
	BYTE keyType,							 //子应用主密钥类型
	BYTE *keyData,							 //子应用主密钥数据
	BYTE fileID,							 //读取文件ID
	BYTE commType,							 //通讯设置		
	DWORD *value);						 	 //value值.

//68、Defire高阶读							
ReaderDLL int CallReader DesfireHLRead(
	BYTE addr,								 //设备地址
	BYTE cid,								 //通道号, 一般为0x01
	int AID,								 //子应用编号
	BYTE keyNo, 							 //子应用主密钥编号 一般为0	 
	BYTE keyType,							 //子应用主密钥类型
	BYTE *keyData,							 //子应用主密钥数据
	BYTE fileID,							 //读取文件ID
	BYTE fileType,							 //文件类型
	BYTE commType,							 //通讯设置		
	DWORD offset,							 //偏移量. 	
	DWORD readLength,						 //文件长度 			记录文件为读取记录的个数
	DWORD singleRecSize,					 //单个记录的数据长度，只有记录文件有用
	BYTE *readData,							 //数据内容
	DWORD *readDataLen,						 //数据长度
	DWORD maxLen);	

//69、Defire高阶写
ReaderDLL int CallReader DesfireHLWrite(
	BYTE addr,								 //设备地址
	BYTE cid,								 //通道号, 一般为0x01
	int AID,								 //子应用编号
	BYTE keyNo, 							 //子应用主密钥编号 一般为0	 
	BYTE keyType,							 //子应用主密钥类型
	BYTE *keyData,							 //子应用主密钥数据
	BYTE fileID,							 //读取文件ID
	BYTE fileType,							 //文件类型
	BYTE commType,							 //通讯设置		
	DWORD offset,							 //偏移量. 	
	DWORD writeLength,						 //文件长度 			记录文件为读取记录的个数						
	BYTE *writeData);						 //数据内容

//70、Defire高阶值文件消费
ReaderDLL int CallReader DesfireHLDebit(
	BYTE addr,								 //设备地址
	BYTE cid,								 //通道号, 一般为0x01
	int AID,								 //子应用编号
	BYTE keyNo, 							 //子应用主密钥编号 一般为0	  
	BYTE keyType,							 //子应用主密钥类型
	BYTE *keyData,							 //子应用主密钥数据
	BYTE fileID,							 //读取文件ID
	BYTE commType,							 //通讯设置		
	DWORD decValue);						 //value文件消费

//71、Defire高阶值文件增值和信用增值
ReaderDLL int CallReader DesfireHLCredit(
	BYTE addr,								 //设备地址
	BYTE cid,								 //通道号, 一般为0x01
	int AID,								 //子应用编号
	BYTE keyNo, 							 //子应用主密钥编号 一般为0	 
	BYTE keyType,							 //子应用主密钥类型
	BYTE *keyData,							 //子应用主密钥数据
	BYTE fileID,							 //读取文件ID
	BYTE commType,							 //通讯设置 	
	DWORD incValue,							 //增值额度
	BYTE creditValue);						 //信用增值

//72、Defire高阶改密钥				
ReaderDLL int CallReader DesfireHLChangeKey(
	BYTE addr,								 //设备地址
	BYTE cid,								 //通道号, 一般为0x01
	int AID,								 //应用编号
	BYTE mainKeyNO, 						 //一般为0 
	BYTE keyType,							 //应用主密钥类型
	BYTE *mainKeyData,						 //应用主密钥数据
	BYTE keyVersion, 						 //密钥版本号
	BYTE newKeyNo,							 //一般为0
	BYTE *newKeyData);						 //新密钥数据

//73、Desfire复位
ReaderDLL int CallReader DesFireRATS(BYTE addr, BYTE *data, BYTE *dataLen, BYTE maxLen);

//74、Desfire APDU通道				
ReaderDLL int CallReader DesfireAPDUTransfer(BYTE addr, BYTE *data, int dataLength, BYTE *resData, int *resDataLen, DWORD maxLen);

//75、设置主动工作参数   -- 只适用于 ICM451E - T(M171) 、ICM451E - I(M172)、ICM451EL - T(M173)、ICM451EL - I(M174)
ReaderDLL int CallReader SetAutoModuleWorkParametersForICM451E(UCHAR addr, UCHAR UID, UCHAR SFZInformation, UCHAR contentType, UCHAR *content, UCHAR contentLength);

//76、获取主动模块参数  -- 只适用于 ICM451E - T(M171) 、ICM451E - I(M172)、ICM451EL - T(M173)、ICM451EL - I(M174)
ReaderDLL int CallReader GetModuleAutoWorkParametersForICM451E(unsigned char addr, UCHAR *cardType, unsigned char *parameters, unsigned char *parametersLength, UCHAR maxLen);

//77、TypeB 复位
ReaderDLL int CallReader TypeBCpuReset(UCHAR addr, UCHAR *resetData, UCHAR *resetLength, UCHAR maxLen);

//78、TypeB APU 
ReaderDLL int CallReader TypeBApduTranfser(unsigned char addr, unsigned char *apduCmd, unsigned char apduCmdLength, unsigned char *resData, UCHAR *resDataLen, UCHAR maxLen);

//79、写Flash
ReaderDLL int CallReader WriteFlashForTooBigFile(unsigned char addr, int startAddr, int length, unsigned char *outputStream, unsigned char outputStreamLength);

//80、检查烧写是否成功
ReaderDLL int CallReader CheckBootloaderForTooBigFile(unsigned char addr, int startAddr, UINT fileSize, UINT checkSum);

//81、设置ICX1556 参数
ReaderDLL int CallReader SetIcx1556UsbAutoParameters(UCHAR addr, UCHAR *parameters, UCHAR paramtersLength);

//82、读取ICX1556 参数
ReaderDLL int CallReader GetIcx1556UsbAutoParameters(UCHAR addr, UCHAR *parameters, UCHAR *paramtersLength, UCHAR maxLen);

//83、读取发卡器支持卡类型
ReaderDLL int CallReader GetReaderSupportCard(UCHAR addr, UCHAR *supportParams, UCHAR *supportParamsLength, UCHAR maxLen);

//84、设置发卡器支持卡类型
ReaderDLL int CallReader SetReaderSupportCard(UCHAR addr, UCHAR *supportParams, UCHAR supportParamsLength);

//85. 获取APLUS 卡号
ReaderDLL int CallReader GetAPlusUID(UCHAR addr, UCHAR uid[], UCHAR *uidLength, UCHAR maxLen);

//86. APLUS 下载密钥
ReaderDLL int CallReader APlusLoadKey(UCHAR addr, UCHAR key[], UCHAR keyLength);

//87. 读APLUS 卡
ReaderDLL int CallReader ReadAPlus(UCHAR addr, UCHAR block, UCHAR blockCount, UCHAR dataStream[], UCHAR *dataStreamLength, UCHAR maxLen);

//88. 写APLUS 卡
ReaderDLL int CallReader WriteAPlus(UCHAR addr, UCHAR block, UCHAR blockCount, UCHAR dataStream[], UCHAR dataStreamLength);

//89. 设置D147 主动读卡参数
ReaderDLL int CallReader SetD147AutoWorkParameters(UCHAR addr, D147AutoReadheaderParameters *paramtersBean);

//90. 设置D147 主动读卡参数
ReaderDLL int CallReader GetD147AutoWorkParameters(UCHAR addr, D147AutoReadheaderParameters *paramtersBean);

//91. 设置ID1 主动读卡参数
ReaderDLL int CallReader SetIDAutoWorkParameters(UCHAR addr, UCHAR paramters[], UCHAR paramtersLength);

//92. 设置ID1 主动读卡参数
ReaderDLL int CallReader GetIDAutoWorkParameters(UCHAR addr, UCHAR paramters[], UCHAR *paramtersLength, UCHAR maxLen);

//93. 连接模块
ReaderDLL int CallReader HostConnectModule();

//94. 同步
ReaderDLL int CallReader HostSyncPackno();

//95. 获取boot 版本号
ReaderDLL int CallReader HostGetBootloaderVersion(unsigned char *version);

//96. 获取boot id
ReaderDLL int CallReader HostGetBootLoaderID(unsigned char *idStream, unsigned char *idStreamLength);

//97. 写配置
ReaderDLL int CallReader HostReadConfig(unsigned int *config);

//98. 下载固件信息
ReaderDLL int CallReader LoadingAppDataStream(unsigned long startAddr, unsigned long totalLength, unsigned long curAddr, unsigned char *appStream, unsigned long *appStreamLength);

//99. boot 跳转到App
ReaderDLL int CallReader HostBootJumpApp();

//100. ISO15693_Read
ReaderDLL int CallReader ISO15693ReadBlockSecurity(unsigned char addr, unsigned char flags, unsigned char blockAddr,
	unsigned char blockCount, unsigned char *UID, unsigned char *recData, unsigned char *recLength, unsigned char maxLen);

#endif

