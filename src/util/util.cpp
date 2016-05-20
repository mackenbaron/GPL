#include "stdafx.h"
#include "util.h" 
//#include "JsonString.h"
#include "JSON_checker.h"

void util::readINIFileString(std::string path,std::string root,std::string userkey,std::string &uservalue,std::string def)
{
	WCHAR char_temp[512] = {L'\0'};
	GetPrivateProfileString((A2U(root).c_str()),A2U(userkey).c_str(),A2U(def).c_str(),char_temp,MAX_PATH,A2U(path).c_str());
	uservalue = U2A(char_temp);
}

void util::readINIFileInt(std::string path,std::string root,std::string userkey,int &userValue,int def)
{
	userValue = GetPrivateProfileInt(A2U(root).c_str(),A2U(userkey).c_str(),def,A2U(path).c_str());
}

void util::writeINIFileString(std::string path,std::string root,std::string userkey,std::string value)
{
	WritePrivateProfileString(A2U(root).c_str(),A2U(userkey).c_str(),A2U(value).c_str(),A2U(path).c_str());
}

void util::UTF_8ToUnicode(wchar_t* pOut,char *pText){
	char* uchar = (char *)pOut;
	uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
	uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);
	return;
}

void util::UnicodeToUTF_8(char* pOut,wchar_t* pText){
	// 注意 WCHAR高低字的顺序,低字节在前，高字节在后z
	char* pchar = (char *)pText;
	pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
	pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
	pOut[2] = (0x80 | (pchar[0] & 0x3F));
	return;
}

void util::UnicodeToGB2312(char* pOut,wchar_t uData){
	WideCharToMultiByte(CP_ACP,NULL,&uData,1,pOut,sizeof(wchar_t),NULL,NULL);
	return;
}    

void util::Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer){
	::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
	return ;
}

void util::GB2312ToUTF_8(std::string& pOut,char *pText, int pLen){
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

void util::UTF_8ToGB2312(std::string &pOut, char *pText, int pLen){
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

std::string util::intTOStirng(const int n)
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

std::string util::DoubleTOString(const double n)
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

int util::StringToInt(const char* src)
{
	return atoi(src);
}
double util::StringTODouble(const char* src)
{
	return atof(src);
}

std::vector<std::string> util::split(std::string &str,std::string &pattern)
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

std::string util::GBKToUTF8(const std::string& strGBK)
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

std::string util::UTF8ToGBK(const std::string& strUTF8)
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

void util::ReplaceSrc(std::string&s1,const std::string&s2,const std::string&s3)
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

std::string util::Base64Encode(const unsigned char* Data,int DataByte)
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

std::string util::Base64Decode(const char* Data,int DataByte,int& OutByte)
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

std::string util::UrlEncode(const std::string& szToEncode)
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

std::string util::UrlDecode(const std::string& szToDecode)
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

bool util::CheckFormatJson(std::string src)
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

std::string util::U2A(const std::wstring& str)
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
std::wstring util::A2U(const std::string& str)//Ascii字符转  
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

std::string util::U2Utf(const std::wstring& wstrUnicode)//Unicode转utf8    
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

std::wstring util::Utf2U(const std::string &str)//utf8转Unicode  
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
bool util::SplitStringW(const std::wstring& strSource,const std::wstring& strFlag, std::vector<std::wstring>& paramList)  
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
std::wstring util::StrReplaceW(const std::wstring& strContent, const std::wstring& strTag, const std::wstring& strReplace)  
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

std::string util::StrReplaceA( const std::string& strContent, const std::string& strTag, const std::string& strReplace )  
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

bool util::SplitStringA(const std::string& strSource,const std::string& strFlag, std::vector<std::string>& paramList)
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

int util::ReadFileDate(std::string filePaht,std::string &message)
{
	FILE *in;
	if(filePaht.empty())
		return -1;
	if(_access(filePaht.c_str(), 0) == -1)
	{
		return -1;
	}
	if((in=fopen(filePaht.c_str(),"r"))!=NULL)
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

int util::WriteFileDate(std::string filename,unsigned char* date,int len)
{
	FILE *fp;
	fp=fopen(const_cast<char*>(filename.c_str()),"wb");
	if(fp!=NULL)
	{
		fwrite(date,sizeof(unsigned char),len,fp);
		fclose(fp);
		return 0;
	}
	return -1;
}
