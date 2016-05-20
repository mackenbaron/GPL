#ifndef UTIL_H
#define UTIL_H

class util
{
	public:
		void readINIFileString(std::string path,std::string root,std::string userkey,std::string &uservalue,std::string def);//读ini
		void readINIFileInt(std::string path,std::string root,std::string userkey,int &userValue,int def);//读ini
		void writeINIFileString(std::string path,std::string root,std::string userkey,std::string value);//写ini
		void UTF_8ToUnicode(wchar_t* pOut,char *pText);  // 把UTF-8转换成Unicode
		void UnicodeToUTF_8(char* pOut,wchar_t* pText);  //Unicode 转换成UTF-8
		void UnicodeToGB2312(char* pOut,wchar_t uData);  // 把Unicode 转换成 GB2312
		void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);// GB2312 转换成　Unicode
		void GB2312ToUTF_8(std::string& pOut,char *pText, int pLen);//GB2312 转为 UTF-8
		void UTF_8ToGB2312(std::string &pOut, char *pText, int pLen);//UTF-8 转为 GB2312
		std::string intTOStirng(const int n);//int to char
		std::string DoubleTOString(const double n);//double to char
		int StringToInt(const char* src); //char to int
		double StringTODouble(const char* src);// char to double
		std::vector<std::string> split(std::string &str,std::string &pattern);//取分隔符之间的多个字符
		std::string GBKToUTF8(const std::string& strGBK); //gbk to utf8
		std::string UTF8ToGBK(const std::string& strUTF8);//utf8 to gbk
		void ReplaceSrc(std::string&s1,const std::string&s2,const std::string&s3);//查询替换字符串
		std::string Base64Encode(const unsigned char* Data,int DataByte);//编码base64
		std::string Base64Decode(const char* Data,int DataByte,int& OutByte);//解码base64
		std::string UrlEncode(const std::string& szToEncode);//编码url 中文
		std::string UrlDecode(const std::string& szToDecode);//解码url 中文
		bool CheckFormatJson(std::string src);//验证json是否合法
		std::string U2A(const std::wstring& str);//Unicode字符转Ascii字符
		std::wstring A2U(const std::string& str);//Ascii字符转Unicode
		std::string U2Utf(const std::wstring& wstrUnicode);//Unicode转utf8 
		std::wstring Utf2U(const std::string &str);//utf8转Unicode 		 
		bool SplitStringW(const std::wstring& strSource,const std::wstring& strFlag, std::vector<std::wstring>& paramList);//分割字符串	
		bool SplitStringA(const std::string& strSource,const std::string& strFlag, std::vector<std::string>& paramList);//分割字符串
		std::wstring StrReplaceW(const std::wstring& strContent, const std::wstring& strTag, const std::wstring& strReplace);//替换字符串  
		std::string StrReplaceA( const std::string& strContent, const std::string& strTag, const std::string& strReplace );//替换字符串 

		int ReadFileDate(std::string filePaht,std::string &message);//读文件
		int WriteFileDate(std::string filename,unsigned char* date,int len);//写文件
};



#endif // UTIL_H
