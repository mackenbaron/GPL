#ifndef UTIL_H
#define UTIL_H
/**
	*  Copyright (c) 2016, DayBreak(https://github.com/DayBreakZhang)
	*  All rights reserved.
	*
	*  @file        util.h
	*  @author      DayBreakZhang(a365316465@gmail.com)
	*  @date        2016/05/31 10:48
	*
	*  @brief       常用的函数类，这些函数可以独立使用也可以结合使用
	*  @note        函数分为wchar 和 char 两种类型，如果没有特殊说明，中文是需要进行转换否则会乱码
	*
	*  @version
	*    - v1.0     2016/05/31 10:48    DayBreakZhang    0.1
	*  @todo	    -代办事宜
	*					-#修改内存泄露问题
	*/
namespace gpl
{
	/** 计算文件校验码的返回结构 */
	typedef struct ResultData
	{
		bool bDone; /**< 计算是否成功 */
		std::string strPath; /**< 路径 */
		__int64 ulSize; /**< 大小 */
		std::string strMDate; /**< 修改日期 */
		std::string strVersion;/**< 版本 */
		std::string strMD5;/**< MD5 */
		std::string strSHA1;/**< SHA1 */
		std::string strSHA256;/**< SHA256 */
		std::string strCRC32;/**< CRC32 */
		std::string strError;/**<Error string */
		ResultData()
			:bDone(false)
			, strPath("")
			, ulSize(0)
			, strMDate("")
			, strVersion("")
			, strMD5("")
			, strSHA1("")
			, strSHA256("")
			, strCRC32("")
			, strError("")
		{}
	}Result;
	/**< 计算文件校验码的返回结构 */

	/**
		*  @author      DayBreakZhang(a365316465@gmail.com)
		*  @date        2016/05/31 11:01
		*  @class       util
		*  @brief       常用函数公共类，其中包括了字符转换，ini文件读写，字符串查找替换，字符串分割符提取，url中文编码解码，读写文件，json格式验证，文件校验，文件加密解密
		*  @attention   函数如果没有指定wchar的函数，要使用转换函数将中文转换
		*  @bug	        -已解决问题列表\n -#解决转换函数内存泄露问题
		*  @warning     -警告列表\n -#如果 函数返回/参数 中引用到了函数内部变量指针的使用完成之后要释放
		*  @note		-更新列表\n -#加入加密解密\n -#加入文件校验算码
		*/
	class util
	{
	public:
		/**
			*  @date        2016/05/31 11:03
			*  @brief       读出ini文件string类型
			*  @param[in]   path[string] ini文件路径，绝对/相对
			*  @param[in]   root[string] ini文件的节点名字，e.g [Data]
			*  @param[in]	userkey[string] ini节点key的名字， e.g DSN=
			*  @param[out]  uservalue[string &] 返回节点key对应该的值 e.g 192.168.0.1
			*  @param[in]	def[string] 节点key对应的值为空时使用def中的值做为默认
			*  @return      void
			*  @pre         -#中文需要转换\n -#文件路径一写要能找到
			*  @remarks     使用这个函数可以读取string类型的key
			*  @see         参考内容
			*  @par 代码实例
			*  @code
			std::string _tempDSN;
			readINIFileString(".\\config","Net","DSN",_tempDSN,"127.0.0.1");
			@endcode
			*/
		void readINIFileString(std::string path, std::string root, std::string userkey, std::string &uservalue, std::string def);
		/**
			*  @date        2016/05/31 13:41
			*  @brief       读取ini文件int类型
			*  @param[in]   path[string] ini文件路径，绝对/相对
			*  @param[in]   root[string] ini文件的节点名字，e.g [Data]
			*  @param[in]	userkey[string] ini节点key的名字， e.g Port=
			*  @param[out]  uservalue[int &] 返回节点key对应该的值 e.g 8080
			*  @param[in]	def[int] 节点key对应的值为空时使用def中的值做为默认
			*  @return      void
			*  @pre         -#中文需要转换\n -#文件路径一写要能找到
			*  @remarks     使用这个函数可以读取int类型的key
			*  @see         参考内容
			*  @par 代码实例
			*  @code
			int _tempDSN;
			readINIFileString(".\\config","Net","DSN",_tempDSN,8080);
			@endcode
			*/
		void readINIFileInt(std::string path, std::string root, std::string userkey, int &userValue, int def);
		/**
			*  @date        2016/05/31 13:49
			*  @brief       将string字符串写入ini文件
			*  @param[in]   path[string] ini文件路径，绝对/相对
			*  @param[in]   root[string] ini文件的节点名字，e.g [Data]
			*  @param[in]	userkey[string] ini节点key的名字， e.g Port=
			*  @param[in]	value[string] ini节点key的值， e.g 8000
			*  @return      void
			*  @pre         -#中文需要转换\n -#文件路径一写要能找到
			*  @remarks     使用这个函数可以读取int类型的key
			*  @see         参考内容
			*  @par 代码实例
			*  @code
			std::string _tempDSN="192.168.0.25";
			writeINIFileString(".\\config","Net","DSN",_tempDSN);
			@endcode
			*/
		bool writeINIFileString(std::string path, std::string root, std::string userkey, std::string value);
		/**
			*  @date        2016/05/31 13:49
			*  @brief       将int数值写入ini文件
			*  @param[in]   path[string] ini文件路径，绝对/相对
			*  @param[in]   root[string] ini文件的节点名字，e.g [Data]
			*  @param[in]	userkey[string] ini节点key的名字， e.g Port=
			*  @param[in]	value[int] ini节点key的值， e.g 8000
			*  @return      void
			*  @pre         -#中文需要转换\n -#文件路径一写要能找到
			*  @remarks     使用这个函数可以读取int类型的key
			*  @see         参考内容
			*  @par 代码实例
			*  @code
			int _tempDSN=8000;
			writeINIFileString(".\\config","Net","DSN",_tempDSN);
			@endcode
			*/
		bool writeINIFileInt(std::string path, std::string root, std::string userkey, int value);
		/**
			*  @date        2016/05/31 14:07
			*  @brief       将单字节utf-8的编码转换成双字节Unicode的编码
			*  @param[out]  pOut[wchar_t*] 由char*转换wchar*的存放地址
			*  @param[in]   pTest[char*] 传入一个utf-8的字符
			*  @return      void
			*  @pre         -#传入的单个char \n -#输出的一个单个的wchar
			*  @remarks     使用这个函数可以将 utf-8 char=>wcahr
			*  @see         参考内容
			*/
		void UTF_8ToUnicode(wchar_t* pOut, char *pText);
		/**
			*  @date        2016/05/31 14:26
			*  @brief       将双字节unicode的编码转换成单字节utf-8的编码
			*  @param[in]   pText[wchar_t*]传入一个unicode编码的双字节
			*  @param[out]  pOut[char*]输出utf-8的编码单字节
			*  @return      void
			*  @pre         -#输入双字节unicode字符\n -#输出一个单字节utf-8字符
			*  @remarks     使用这个函数可以将unicode wchar=>char utf-8
			*  @see         参考内容
			*/
		void UnicodeToUTF_8(char* pOut, wchar_t* pText);  //Unicode 转换成UTF-8
		void UnicodeToGB2312(char* pOut, wchar_t uData);  // 把Unicode 转换成 GB2312
		void Gb2312ToUnicode(wchar_t* pOut, char *gbBuffer);// GB2312 转换成　Unicode
		void GB2312ToUTF_8(std::string& pOut, char *pText, int pLen);//GB2312 转为 UTF-8
		void UTF_8ToGB2312(std::string &pOut, char *pText, int pLen);//UTF-8 转为 GB2312
		std::string intTOStirng(const int n);//int to char
		std::string DoubleTOString(const double n);//double to char
		int StringToInt(const char* src); //char to int
		double StringTODouble(const char* src);// char to double
		std::vector<std::string> split(std::string &str, std::string &pattern);//取分隔符之间的多个字符
		std::string GBKToUTF8(const std::string& strGBK); //gbk to utf8
		std::string UTF8ToGBK(const std::string& strUTF8);//utf8 to gbk
		void ReplaceSrc(std::string&s1, const std::string&s2, const std::string&s3);//查询替换字符串
		std::string Base64Encode(const unsigned char* Data, int DataByte);//编码base64
		std::string Base64Decode(const char* Data, int DataByte, int& OutByte);//解码base64
		std::string UrlEncode(const std::string& szToEncode);//编码url 中文
		std::string UrlDecode(const std::string& szToDecode);//解码url 中文
		bool CheckFormatJson(std::string src);//验证json是否合法
		std::string U2A(const std::wstring& str);//Unicode字符转Ascii字符
		std::wstring A2U(const std::string& str);//Ascii字符转Unicode
		std::string U2Utf(const std::wstring& wstrUnicode);//Unicode转utf8 
		std::wstring Utf2U(const std::string &str);//utf8转Unicode 		 
		bool SplitStringW(const std::wstring& strSource, const std::wstring& strFlag, std::vector<std::wstring>& paramList);//分割字符串	
		bool SplitStringA(const std::string& strSource, const std::string& strFlag, std::vector<std::string>& paramList);//分割字符串
		std::wstring StrReplaceW(const std::wstring& strContent, const std::wstring& strTag, const std::wstring& strReplace);//替换字符串  
		std::string StrReplaceA(const std::string& strContent, const std::string& strTag, const std::string& strReplace);//替换字符串 

		int ReadFileDate(std::string filePaht, std::string &message);//读文件
		int WriteFileDate(std::string filename, unsigned char* date, int len);//写文件

		std::map<std::string, std::vector<std::string> > ParsingArgsSrc(std::string tmpPara, char*item, ...);//解析传入参数
		std::string SrcEncrypt(std::string szSource, std::string szPassWord); // 加密，返回加密结果
		std::string SrcDecrypt(std::string szSource, std::string szPassWord); // 解密，返回解密结果
		int getFileVerify(std::vector<std::string> &infile, std::vector<Result> &outre);//计算MD5、SHA1、SHA256、CRC32
	};

}


#endif // UTIL_H
