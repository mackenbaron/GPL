#include "stdafx.h"
#include "util.h" 
#include "confile.h"
#include "JSON_checker.h"
#include "parsingargs.h"
#include "Encrypt.h"

#include "md5.h"
#include "sha1.h"
#include "sha256.h"
#include "crc32.h"
//定义读入文件有buffer
class DataBuffer
{
public:
	DataBuffer();
	~DataBuffer();

	static unsigned int preflen;

	unsigned int datalen;
	unsigned char *data;
};

unsigned int DataBuffer::preflen = 1048576; // 2^20
#define BOX_LEN 256

void gpl::util::readINIFileString(std::string path,std::string root,std::string userkey,std::string &uservalue,std::string def)
{
	INI_CONFIG *ini = ini_config_create_from_file(const_cast<char*>(path.c_str()),1);
	uservalue = ini_config_get_string(ini,root.c_str(),userkey.c_str(),const_cast<char*>(def.c_str()));
	ini_config_destroy(ini);
}

void gpl::util::readINIFileInt(std::string path,std::string root,std::string userkey,int &userValue,int def)
{
	INI_CONFIG *ini = ini_config_create_from_file(const_cast<char*>(path.c_str()), 1);
	userValue = ini_config_get_int(ini, root.c_str(), userkey.c_str(),def);
	ini_config_destroy(ini);
}

bool gpl::util::writeINIFileString(std::string path,std::string root,std::string userkey,std::string value)
{
	INI_CONFIG *ini = ini_config_create_from_file(const_cast<char*>(path.c_str()), 1);
	int a  = ini_config_set_string(ini, root.c_str(), userkey.c_str(),userkey.size(),value.c_str(),value.size());
	if (a == 1)
	{
		int b = ini_config_save(ini, path.c_str());
		if (b == 1)
			return true;
		else
			return false;
	}
	else
		return false;

	ini_config_destroy(ini);
}

bool gpl::util::writeINIFileInt(std::string path, std::string root, std::string userkey, int value)
{
	INI_CONFIG *ini = ini_config_create_from_file(const_cast<char*>(path.c_str()), 1);
	int a = ini_config_set_int(ini, root.c_str(), userkey.c_str(), userkey.size(), value);
	if (a == 1)
	{
		int b = ini_config_save(ini, path.c_str());
		if (b == 1)
			return true;
		else
			return false;
	}
	else
		return false;
	ini_config_destroy(ini);
}


void gpl::util::UTF_8ToUnicode(wchar_t* pOut,char *pText){
	char* uchar = (char *)pOut;
	uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
	uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);
	return;
}

void gpl::util::UnicodeToUTF_8(char* pOut,wchar_t* pText){
	// 注意 WCHAR高低字的顺序,低字节在前，高字节在后z
	char* pchar = (char *)pText;
	pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
	pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
	pOut[2] = (0x80 | (pchar[0] & 0x3F));
	return;
}

void gpl::util::UnicodeToGB2312(char* pOut,wchar_t uData){
	WideCharToMultiByte(CP_ACP,NULL,&uData,1,pOut,sizeof(wchar_t),NULL,NULL);
	return;
}    

void gpl::util::Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer){
	::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
	return ;
}

void gpl::util::GB2312ToUTF_8(std::string& pOut,char *pText, int pLen){
	char buf[4];
	int nLength = pLen* 3;
	char* rst = new char[nLength];

	memset(buf,0,4);
	memset(rst,0,nLength);

	int i = 0;
	int j = 0;     
	while(i < pLen){
		//如果是英文直接复制就能
		if( *(pText + i) >= 0){
			rst[j++] = pText[i++];
		}else{
			wchar_t pbuffer;
			Gb2312ToUnicode(&pbuffer,pText+i);
			UnicodeToUTF_8(buf,&pbuffer);
			unsigned short int tmp = 0;
			tmp = rst[j] = buf[0];
			tmp = rst[j+1] = buf[1];
			tmp = rst[j+2] = buf[2];   
			j += 3;

			i += 2;

		}

	}

	rst[j] ='\0';
	//返回结果
	pOut = rst;            
	delete []rst;    
	return;
}

void gpl::util::UTF_8ToGB2312(std::string &pOut, char *pText, int pLen){
	char * newBuf = new char[pLen];
	char Ctemp[4];
	memset(Ctemp,0,4);
	int i =0;
	int j = 0;

	while(i < pLen){

		if(pText > 0){
			newBuf[j++] = pText[i++];                      
		}else{
			WCHAR Wtemp;
			UTF_8ToUnicode(&Wtemp,pText + i);
			UnicodeToGB2312(Ctemp,Wtemp);
			newBuf[j] = Ctemp[0];
			newBuf[j + 1] = Ctemp[1];

			i += 3;   
			j += 2;  
		}
	}

	newBuf[j] ='\0';
	pOut = newBuf;
	delete []newBuf;
	return;
}

std::string gpl::util::intTOStirng(const int n)
{
	char *_temp=new char[128];
	memset(_temp,'\0',128);
	if(n>=0)
	{
		sprintf(_temp,"%d",n);
		
	}else
	{
		sprintf(_temp,"%d",0);
	}
	std::string _tmepsrc(_temp);
	delete[]_temp;
	return _tmepsrc;
	
}

std::string gpl::util::DoubleTOString(const double n)
{
	char *_temp=new char[128];
	memset(_temp,'\0',128);
	if(n>=0)
	{
		sprintf(_temp,"%f",n);

	}else
	{
		sprintf(_temp,"%f",0.0);
	}
	std::string _tmepsrc(_temp);
	delete[]_temp;
	return _tmepsrc;
}

int gpl::util::StringToInt(const char* src)
{
	return atoi(src);
}
double gpl::util::StringTODouble(const char* src)
{
	return atof(src);
}

std::vector<std::string> gpl::util::split(std::string &str,std::string &pattern)
{
	std::string::size_type pos; 
	std::vector<std::string> result;
	str+=pattern;
	int size=str.size(); 

	for(int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);
		if(pos<(std::string::size_type)size)
		{
			std::string s=str.substr(i,pos-i);
			if(s.size()>0)
				result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}     
	return result;
}

std::string gpl::util::GBKToUTF8(const std::string& strGBK)
{
	std::string strOutUTF8 = "";  
	WCHAR * str1;  
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);  
	str1 = new WCHAR[n];  
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);  
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);  
	char * str2 = new char[n];  
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);  
	strOutUTF8 = str2;  
	delete[]str1;  
	str1 = NULL;  
	delete[]str2;  
	str2 = NULL;  
	return strOutUTF8;  
}

std::string gpl::util::UTF8ToGBK(const std::string& strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);  
	WCHAR * wszGBK = new WCHAR[len + 1];  
	memset(wszGBK, 0, len * 2 + 2);  
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUTF8.c_str(), -1, wszGBK, len);  

	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);  
	char *szGBK = new char[len + 1];  
	memset(szGBK, 0, len + 1);  
	WideCharToMultiByte(CP_ACP,0, wszGBK, -1, szGBK, len, NULL, NULL);  
	//strUTF8 = szGBK;  
	std::string strTemp(szGBK);  
	delete[]szGBK;  
	delete[]wszGBK;  
	return strTemp;  
}

void gpl::util::ReplaceSrc(std::string&s1,const std::string&s2,const std::string&s3)
{
	std::string::size_type pos=0;
	std::string::size_type a=s2.size();
	std::string::size_type b=s3.size();
	while((pos=s1.find(s2,pos))!=std::string::npos)
	{
		s1.replace(pos,a,s3);
		pos+=b;
	}
}

std::string gpl::util::Base64Encode(const char* Data,int DataByte)
{
	//编码表
	const char EncodeTable[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	//返回值
	std::string strEncode;
	unsigned char Tmp[4]={0};
	int LineLength=0;
	for(int i=0;i<(int)(DataByte / 3);i++)
	{
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;
		Tmp[3] = *Data++;
		strEncode+= EncodeTable[Tmp[1] >> 2];
		strEncode+= EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
		strEncode+= EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
		strEncode+= EncodeTable[Tmp[3] & 0x3F];
		if(LineLength+=4,LineLength==76) {strEncode+="\r\n";LineLength=0;}
	}
	//对剩余数据进行编码
	int Mod=DataByte % 3;
	if(Mod==1)
	{
		Tmp[1] = *Data++;
		strEncode+= EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode+= EncodeTable[((Tmp[1] & 0x03) << 4)];
		strEncode+= "==";
	}
	else if(Mod==2)
	{
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;
		strEncode+= EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode+= EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
		strEncode+= EncodeTable[((Tmp[2] & 0x0F) << 2)];
		strEncode+= "=";
	}

	return strEncode;
}

std::string gpl::util::Base64Decode(const char* Data,int DataByte,int& OutByte)
{
	//解码表
		const char DecodeTable[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		62, // '+'
		0, 0, 0,
		63, // '/'
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
		0, 0, 0, 0, 0, 0, 0,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
		13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
		0, 0, 0, 0, 0, 0,
		26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
		39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
	};
	//返回值
	std::string strDecode;
	int nValue;
	int i= 0;
	while (i < DataByte)
	{
		if (*Data != '\r' && *Data!='\n')
		{
			nValue = DecodeTable[*Data++] << 18;
			nValue += DecodeTable[*Data++] << 12;
			strDecode+=(nValue & 0x00FF0000) >> 16;
			OutByte++;
			if (*Data != '=')
			{
				nValue += DecodeTable[*Data++] << 6;
				strDecode+=(nValue & 0x0000FF00) >> 8;
				OutByte++;
				if (*Data != '=')
				{
					nValue += DecodeTable[*Data++];
					strDecode+=nValue & 0x000000FF;
					OutByte++;
				}
			}
			i += 4;
		}
		else// 回车换行,跳过
		{
			Data++;
			i++;
		}
	}
	return strDecode;
}

std::string gpl::util::UrlEncode(const std::string& szToEncode)
{
	std::string src = szToEncode;
	char hex[] = "0123456789ABCDEF";
	std::string dst;

	for (size_t i = 0; i < src.size(); ++i)
	{
		unsigned char cc = src[i];
		if (isascii(cc))
		{
			if (cc == ' ')
			{
				dst += "%20";
			}
			else
				dst += cc;
		}
		else
		{
			unsigned char c = static_cast<unsigned char>(src[i]);
			dst += '%';
			dst += hex[c / 16];
			dst += hex[c % 16];
		}
	}
	return dst;
}

std::string gpl::util::UrlDecode(const std::string& szToDecode)
{
	std::string result;
	int hex = 0;
	for (size_t i = 0; i < szToDecode.length(); ++i)
	{
		switch (szToDecode[i])
		{
		case '+':
			result += ' ';
			break;
		case '%':
			if (isxdigit(szToDecode[i + 1]) && isxdigit(szToDecode[i + 2]))
			{
				std::string hexStr = szToDecode.substr(i + 1, 2);
				hex = strtol(hexStr.c_str(), 0, 16);
				//字母和数字[0-9a-zA-Z]、一些特殊符号[$-_.+!*'(),] 、以及某些保留字[$&+,/:;=?@]
				//可以不经过编码直接用于URL
				if (!((hex >= 48 && hex <= 57) || //0-9
					(hex >=97 && hex <= 122) ||   //a-z
					(hex >=65 && hex <= 90) ||    //A-Z
					//一些特殊符号及保留字[$-_.+!*'(),]  [$&+,/:;=?@]
					hex == 0x21 || hex == 0x24 || hex == 0x26 || hex == 0x27 || hex == 0x28 || hex == 0x29
					|| hex == 0x2a || hex == 0x2b|| hex == 0x2c || hex == 0x2d || hex == 0x2e || hex == 0x2f
					|| hex == 0x3A || hex == 0x3B|| hex == 0x3D || hex == 0x3f || hex == 0x40 || hex == 0x5f
					))
				{
					result += char(hex);
					i += 2;
				}
				else result += '%';
			}else {
				result += '%';
			}
			break;
		default:
			result += szToDecode[i];
			break;
		}
	}
	return result;
}

bool gpl::util::CheckFormatJson(std::string src)
{
// 	JsonString a ;
// 	const char* _tempa = src.c_str();
// 	const char* _tempb = src.c_str()+src.size();
// 	bool ad = a.CheckFormat(_tempa,_tempb);
// 	return ad;

	int a = json_checker(src.c_str());
	if(a==0)
		return true;
	else
		return false;
}

std::string gpl::util::U2A(const std::wstring& str)
{
	std::string strDes;  
	if ( str.empty() )  
		goto __end;  
	int nLen=::WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.size(), NULL, 0, NULL, NULL);  
	if ( 0==nLen )  
		goto __end;  
	char* pBuffer=new char[nLen+1];  
	memset(pBuffer, 0, nLen+1);  
	::WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.size(), pBuffer, nLen, NULL, NULL);  
	pBuffer[nLen]='\0';  
	strDes.append(pBuffer);  
	delete[] pBuffer;  
__end:  
	return strDes; 
}
std::wstring gpl::util::A2U(const std::string& str)//Ascii字符转  
{  
	std::wstring strDes;  
	if ( str.empty() )  
		goto __end;  
	int nLen=::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);  
	if ( 0==nLen )  
		goto __end;  
	wchar_t* pBuffer=new wchar_t[nLen+1];  
	memset(pBuffer, 0, nLen+1);  
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), pBuffer, nLen);  
	pBuffer[nLen]='\0';  
	strDes.append(pBuffer);  
	delete[] pBuffer;  
__end:  
	return strDes;  
}  

std::string gpl::util::U2Utf(const std::wstring& wstrUnicode)//Unicode转utf8    
{    
	std::string strRet;  
	if( wstrUnicode.empty() )  
		return strRet;  
	int nLen = WideCharToMultiByte(CP_UTF8, 0, wstrUnicode.c_str(), -1, NULL, 0, NULL, NULL);    
	char* pBuffer=new char[nLen+1];  
	pBuffer[nLen] = '\0';  
	nLen = WideCharToMultiByte(CP_UTF8, 0, wstrUnicode.c_str(), -1, pBuffer, nLen, NULL, NULL);   
	strRet.append(pBuffer);  
	delete[] pBuffer;  
	return strRet;    
}  

std::wstring gpl::util::Utf2U(const std::string &str)//utf8转Unicode  
{  
	int u16Len = ::MultiByteToWideChar(CP_UTF8, NULL,str.c_str(),(int)str.size(), NULL, 0);  
	wchar_t* wstrBuf = new wchar_t[u16Len + 1];  
	::MultiByteToWideChar(CP_UTF8, NULL, str.c_str(),(int)str.size(), wstrBuf, u16Len);  
	wstrBuf[u16Len] = L'\0';  
	std::wstring wStr;  
	wStr.assign(wstrBuf, u16Len);  
	delete [] wstrBuf;  
	return wStr;  
}  
//分割字符串  
bool gpl::util::SplitStringW(const std::wstring& strSource,const std::wstring& strFlag, std::vector<std::wstring>& paramList)
{  
	if ( strSource.empty() || strFlag.empty() )  
		return false;  
	paramList.clear();  
	size_t nBeg = 0;  
	size_t nFind = strSource.find(strFlag, nBeg);  
	if ( nFind == std::wstring::npos )  
		paramList.push_back(strSource);  
	else  
	{  
		while ( true )  
		{  
			if ( nFind != nBeg )  
				paramList.push_back(strSource.substr(nBeg, nFind-nBeg));  
			nBeg = nFind + strFlag.size();  
			if ( nBeg == strSource.size() )  
				break;  
			nFind = strSource.find(strFlag, nBeg);  
			if ( nFind == std::wstring::npos )  
			{  
				paramList.push_back(std::wstring(strSource.begin()+nBeg, strSource.end()));  
				break;  
			}  
		}  
	}  
	return true;  
}    
//替换字符串  
std::wstring gpl::util::StrReplaceW(const std::wstring& strContent, const std::wstring& strTag, const std::wstring& strReplace)
{  
	size_t nBegin=0, nFind=0;  
	nFind = strContent.find(strTag, nBegin);  
	if ( nFind == std::wstring::npos )  
		return strContent;  
	size_t nTagLen = strTag.size();  
	std::wstring strRet;  
	while ( true )  
	{  
		strRet.append(strContent.begin()+nBegin, strContent.begin()+nFind);  
		strRet.append(strReplace);  
		nBegin = nFind + nTagLen;  
		nFind = strContent.find(strTag, nBegin);  
		if ( nFind == std::wstring::npos )  
		{  
			strRet.append(strContent.begin()+nBegin, strContent.end());  
			break;  
		}  
	}  
	return strRet;  
}  

std::string gpl::util::StrReplaceA( const std::string& strContent, const std::string& strTag, const std::string& strReplace )
{  
	size_t nBegin=0, nFind=0;  
	nFind = strContent.find(strTag, nBegin);  
	if ( nFind == std::string::npos )  
		return strContent;  
	size_t nTagLen = strTag.size();  
	std::string strRet;  
	while ( true )  
	{  
		strRet.append(strContent.begin()+nBegin, strContent.begin()+nFind);  
		strRet.append(strReplace);  
		nBegin = nFind + nTagLen;  
		nFind = strContent.find(strTag, nBegin);  
		if ( nFind == std::string::npos )  
		{  
			strRet.append(strContent.begin()+nBegin, strContent.end());  
			break;  
		}  
	}  
	return strRet;  
}  

bool gpl::util::SplitStringA(const std::string& strSource,const std::string& strFlag, std::vector<std::string>& paramList)
{
	if ( strSource.empty() || strFlag.empty() )  
		return false;  
	paramList.clear();  
	size_t nBeg = 0;  
	size_t nFind = strSource.find(strFlag, nBeg);  
	if ( nFind == std::string::npos )  
		paramList.push_back(strSource);  
	else  
	{  
		while ( true )  
		{  
			if ( nFind != nBeg )  
				paramList.push_back(strSource.substr(nBeg, nFind-nBeg));  
			nBeg = nFind + strFlag.size();  
			if ( nBeg == strSource.size() )  
				break;  
			nFind = strSource.find(strFlag, nBeg);  
			if ( nFind == std::string::npos )  
			{  
				paramList.push_back(std::string(strSource.begin()+nBeg, strSource.end()));  
				break;  
			}  
		}  
	}  
	return true;
}

int gpl::util::ReadFileDate(std::string filePaht, std::string &message, std::string format/*="r"*/)
{
	FILE *in;
	if(filePaht.empty())
		return -1;
	if(_access(filePaht.c_str(), 0) == -1)
	{
		return -1;
	}
	if((in=fopen(filePaht.c_str(),format.c_str()))!=NULL)
	{
		std::string src ="";
		char* result1 = NULL;
		long length=0;//声明文件长度
		fseek(in,0,SEEK_END);//将文件内部指针放到文件最后面
		length=ftell(in);//读取文件指针的位置，得到文件字符的个数
		if(length <=0)
		{
			fclose(in);
			return -1;
		}
		rewind(in);//将文件指针重置到文件最前面
		result1 = new char[length+1];
		memset(result1,'\0',length+1);
		while(!feof(in))//判定文件是否结尾
		{
			if(fgets(result1,length+1,in)!=NULL)
			{
				src.append(result1);
			}
		}
		message = src;
		fclose(in);
		delete []result1;
		if(message.size() >0)
			return 0;
		else
			return -1;
	}else
	{
		return -1;
	}
}

int gpl::util::WriteFileDate(std::string filename, unsigned char* date, int len, std::string format/*="wb"*/)
{
	FILE *fp;
	fp = fopen(const_cast<char*>(filename.c_str()), format.c_str());
	if(fp!=NULL)
	{
		fwrite(date,sizeof(unsigned char),len,fp);
		fclose(fp);
		return 0;
	}
	return -1;
}

std::map<std::string, std::vector<std::string> > gpl::util::ParsingArgsSrc(std::string tmpPara, char*item, ...)
{
	std::map<std::string, std::vector<std::string> > result;
	ParsingArgs pa;
	result.clear();
	va_list arg_ptr;
	va_start(arg_ptr, item);

	char* itemsrc = item;
	while (itemsrc!=NULL)
	{
		std::vector<std::string> vsipl;
		SplitStringA(itemsrc, "%", vsipl);
		char a = vsipl[0][0];
		const char *b = vsipl[1].c_str();
		pa.AddArgType(a, b, ParsingArgs::MUST_VALUE);
		itemsrc = va_arg(arg_ptr, char*);
	}
	std::string errPos;
	int code = pa.Parse(tmpPara, result, errPos);
	va_end(arg_ptr);
	return result;
}

std::string gpl::util::SrcEncrypt(std::string szSource, std::string szPassWord)
{
	std::string src = "";
	char *result1 = NULL;
	result1 = Encrypt(szSource.c_str(), szPassWord.c_str());
	if (result1 != NULL)
	{
		src = result1;
	}	
	delete[]result1;
	return src;
}

std::string gpl::util::SrcDecrypt(std::string szSource, std::string szPassWord)
{
	std::string src = "";
	char *result1 = NULL;
	result1 = Decrypt(szSource.c_str(), szPassWord.c_str());
	if (result1 != NULL)
	{
		src = result1;
	}
	delete[]result1;
	return src;
}

int API_TimeToStringEX(std::string &strDateStr, const __time64_t &timeData)
{
	char chTmp[100] = { '\0' };
	struct tm *p;
	p = localtime(&timeData);
	p->tm_year = p->tm_year + 1900;
	p->tm_mon = p->tm_mon + 1;

	sprintf(chTmp, "%04d-%02d-%02d %02d:%02d:%02d",
		p->tm_year, p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
	strDateStr = chTmp;
	return 0;
}

int gpl::util::getFileVerify(std::vector<std::string> &infile, std::vector<Result> &outre)
{
	__int64 finishedSize = 0;
	std::vector<__int64> fSizes(infile.size());
	std::string strFileSize;
	std::string strFileMD5;
	std::string strFileSHA1;
	std::string strFileSHA256;
	std::string strFileCRC32;

	//开始计算,循环处理每个文件
	for (int i = 0; i < infile.size(); i++)
	{
		// Declaration for calculator
		char* path = const_cast<char*>(infile[i].c_str());
		__int64 fsize = 0;
		finishedSize = 0;
		DataBuffer databuf;

		MD5_CTX mdContext; // MD5 context

		CSHA1 sha1; // SHA1 object
		char strSHA1[256];

		SHA256_CTX sha256Ctx; // SHA256 context
		std::string strSHA256 = "";

		unsigned long ulCRC32; // CRC32 context

		ResultData result;
		result.strPath = infile[i];
		//打开文件
		FILE *fp = fopen(infile[i].c_str(), "rb+");
		if (fp != NULL)
		{
			//成功打开文件
			MD5Init(&mdContext, 0); // MD5开始
			sha1.Reset(); // SHA1开始
			sha256_init(&sha256Ctx); // SHA256开始
			crc32Init(&ulCRC32); // CRC32开始

			//获取文件信息
			std::string lastModifiedTime;
			struct _stat64 info;
			_wstat64(A2U(infile[i].c_str()).c_str(), &info);
			fsize = info.st_size;
			API_TimeToStringEX(lastModifiedTime, info.st_mtime);
			do
			{
				//读取文件
				databuf.datalen = fread(databuf.data, 1, DataBuffer::preflen, fp);

				MD5Update(&mdContext, databuf.data, databuf.datalen); // MD5更新
				sha1.Update(databuf.data, databuf.datalen); // SHA1更新
				sha256_update(&sha256Ctx, databuf.data, databuf.datalen); // SHA256更新
				crc32Update(&ulCRC32, databuf.data, databuf.datalen); // CRC32更新

				finishedSize += databuf.datalen;

				//设置偏移
				if (databuf.datalen >= DataBuffer::preflen)
					_fseeki64(fp, finishedSize, SEEK_SET);
			} while (databuf.datalen >= DataBuffer::preflen);
			fclose(fp);//关闭文件
			MD5Final(&mdContext); // MD5完成
			sha1.Final(); // SHA1完成
			sha256_final(&sha256Ctx); // SHA256完成
			crc32Finish(&ulCRC32); //CRC32完成

			//格式化校验码
			char _tempmd5[256] = { '\0' };
			sprintf(_tempmd5, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
				mdContext.digest[0],
				mdContext.digest[1],
				mdContext.digest[2],
				mdContext.digest[3],
				mdContext.digest[4],
				mdContext.digest[5],
				mdContext.digest[6],
				mdContext.digest[7],
				mdContext.digest[8],
				mdContext.digest[9],
				mdContext.digest[10],
				mdContext.digest[11],
				mdContext.digest[12],
				mdContext.digest[13],
				mdContext.digest[14],
				mdContext.digest[15]);
			strFileMD5 = _tempmd5;
			sha1.ReportHash(strSHA1, CSHA1::REPORT_HEX);
			strFileSHA1 = (strSHA1);
			sha256_digest(&sha256Ctx, &strSHA256);
			strFileSHA256 = strSHA256;
			//strFileCRC32.Format(_T("%08X"), ulCRC32);
			char _tempcrc[128] = { '\0' };
			sprintf(_tempcrc, "%08X", ulCRC32);
			strFileCRC32 = _tempcrc;

			result.bDone = TRUE;
			result.strPath = infile[i];
			result.ulSize = fsize;
			result.strMDate = lastModifiedTime;
			// 在没做转换前，结果都是大写的
			result.strMD5 = strFileMD5;
			result.strSHA1 = strFileSHA1;
			result.strSHA256 = strFileSHA256;
			result.strCRC32 = strFileCRC32;
			//转换大小写
		}
		else
		{
			result.bDone = FALSE;
			result.strError = "Open file error";
		}

		outre.push_back(result);
	}
	return 0;
}

DataBuffer::DataBuffer() 
	:datalen(0), data(NULL)
{
	data = new unsigned char[DataBuffer::preflen];
	memset(data, '\0', DataBuffer::preflen);
}

DataBuffer::~DataBuffer()
{
	delete[] data;
	datalen = 0;
}
