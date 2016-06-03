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
	/**
	*  @author      DayBreakZhang(a365316465@gmail.com)
	*  @date        2016/05/31 11:01
	*  @class       ResultData
	*  @brief       校验文件返回结果的结构体
	*/
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
		*  @par	        utf-8,GB2312,unicode介绍
		*  @code
		UTF-8：Unicode TransformationFormat-8bit，允许含BOM，但通常不含BOM。是用以解决国际上字符的一种多字节编码，它对英文使用8位（即一个字节），中文使用24为（三个字节）来编码。UTF-8包含全世界所有国家需要用到的字符，是国际编码，通用性强。UTF-8编码的文字可以在各国支持UTF8字符集的浏览器上显示。如，如果是UTF8编码，则在外国人的英文IE上也能显示中文，他们无需下载IE的中文语言支持包。
		GBK是国家标准GB2312基础上扩容后兼容GB2312的标准。GBK的文字编码是用双字节来表示的，即不论中、英文字符均使用双字节来表示，为了区分中文，将其最高位都设定成1。GBK包含全部中文字符，是国家编码，通用性比UTF8差，不过UTF8占用的数据库比GBD大。
		GBK、GB2312等与UTF8之间都必须通过Unicode编码才能相互转换
		GBK、GB2312－－Unicode－－UTF8
		UTF8－－Unicode－－GBK、GB2312
		*  @endcode
		*  @par			Base64介绍
		*  @code
		Base64是一种用64个字符来表示任意二进制数据的方法。
		用记事本打开exe、jpg、pdf这些文件时，我们都会看到一大堆乱码，因为二进制文件包含很多无法显示和打印的字符，所以，如果要让记事本这样的文本处理软件能处理二进制数据，就需要一个二进制到字符串的转换方法。Base64是一种最常见的二进制编码方法.
		Base64是一种任意二进制到文本字符串的编码方法，常用于在URL、Cookie、网页中传输少量二进制数据。
		*  @endcode
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
			*  @brief       将双字节unicode的编码转换成单字节utf-8的编码(单个字符输入/输出)
			*  @param[in]   pText[wchar_t*]传入一个unicode编码的双字节
			*  @param[out]  pOut[char*]输出utf-8的编码单字节
			*  @return      void
			*  @pre         -#输入双字节unicode字符\n -#输出一个单字节utf-8字符
			*  @remarks     使用这个函数可以将unicode wchar=>char utf-8
			*  @see         参考内容
			*/
		void UnicodeToUTF_8(char* pOut, wchar_t* pText);
		/**
			*  @date        2016/06/01 10:13
			*  @brief       将unicode编码转换成GB2312的编码(单个字符输入/输出)
			*  @param[in]   uDate[wchr_t*] 输入Unicode编码数据
			*  @param[out]  pOut[char*] 输出GB2312编码数据
			*  @return      void
			*  @pre         -#输入双字节unicode字符\n -#输出一个单字节GB2312字符
			*  @remarks     使用这个函数可以将unicode字符转换成GB2312
			*  @see         参考内容
			*/
		void UnicodeToGB2312(char* pOut, wchar_t uData);
		/**
			*  @date        2016/06/01 10:17
			*  @brief       将GB2312编码转换成Unicode编码(单个字符输入/输出)
			*  @param[in]	gbBuffer[char*] 输入GB2312编码字符
			*  @param[out]  pOut[wchar_t*] 输出Unicode编码字符
			*  @return      void
			*  @pre          -#输出一个单字节GB2312字符\n -#输入双字节unicode字符
			*  @remarks     使用这个函数可以将GB2312字符转换成unicode
			*  @see         参考内容
			*/
		void Gb2312ToUnicode(wchar_t* pOut, char *gbBuffer);
		/**
			*  @date        2016/06/01 10:41
			*  @brief       将GB2312编码转换成utf-8编码（多个字符输入/输出）
			*  @param[in]    pText[char*] 输入GB2312的字符串指针（std::string src.c_src()）
			*  @param[in]    pLen[int]输入pText字符串的长度（std::string src.size()）
			*  @param[out]   pOut[string&] 输出转换之后的字符
			*  @return      void
			*  @pre         -#输入多个字符指针\n -#流程：GB2312->Unicode->Utf-8
			*  @remarks      使用这个函数可以将GB2312编码转换成utf-8编码
			*  @see         参考内容
			*/
		void GB2312ToUTF_8(std::string& pOut, char *pText, int pLen);
		/**
			*  @date        2016/06/01 10:50
			*  @brief       将utf-8编码转换成GB2312编码（多个字符输入/输出）
			*  @param[in]   pText[char*]输入utf-8编码格式字符串
			*  @param[in]   pLen[int]输入pText的字符串长度
			*  @param[out]  pOut[string&]输出转换之后的字符串
			*  @return      void
			*  @pre         -#输入多个字符指针\n -#流程：UTF-8->Unicode->GB2312
			*  @remarks     使用这个函数可以将UTF-8编码转换成GB2312编码
			*  @see         参考内容
			*/
		void UTF_8ToGB2312(std::string &pOut, char *pText, int pLen);
		/**
			*  @date        2016/06/01 11:38
			*  @brief       将int转成的string
			*  @param[in]   n[int] 输入要转化的int数字
			*  @return      返回转化之后的字符串
			*/
		std::string intTOStirng(const int n);
		/**
		*  @date        2016/06/01 11:38
		*  @brief       将double转成的string
		*  @param[in]   n[double] 输入要转化的double数字
		*  @return      返回转化之后的字符串
		*/
		std::string DoubleTOString(const double n);
		/**
		*  @date        2016/06/01 11:38
		*  @brief       将string转成的数字
		*  @param[in]   src[char*] 输入要转化的字符串
		*  @return      返回转化之后的数字
		*/
		int StringToInt(const char* src);
		/**
		*  @date        2016/06/01 11:38
		*  @brief       将string转成的数字
		*  @param[in]   src[char*] 输入要转化的字符串
		*  @return      返回转化之后的数字
		*/
		double StringTODouble(const char* src);
		/**
			*  @date        2016/06/01 13:48
			*  @brief       以分割符来切分字符串
			*  @param[in]   str[string&] 输入的字符串，使用特定且相同的字符进行分割
			*  @param[in]   pattern[string&] 输入分割符
			*  @return      返回分割的结果
			*  @pre         -#分割符相同
			*  @remarks     可使用这个函数对“1，2，34，5，6”这样的字符串进行分割
			*  @see         参考内容
			*  @par			参考实例
			*  @code
			std::string src ="1,2.1,315,45,21.0,548.0";
			std::vector<std::stirng> result = split(src,",");//result[0]=1;result[1]=2.1
			@endcode
			*/
		std::vector<std::string> split(std::string &str, std::string &pattern);
		/**
			*  @date        2016/06/01 13:54
			*  @brief       将GBK编码转换成UTF-8编码
			*  @param[in]   strGBK[string&] 输入GBK编码格式的字符串
			*  @return      返回编码之后的字符串
			*/
		std::string GBKToUTF8(const std::string& strGBK);
		/**
		*  @date        2016/06/01 13:54
		*  @brief       将UTF-8编码转换成GBK编码
		*  @param[in]   strGBK[string&] 输入UTF-8编码格式的字符串
		*  @return      返回编码之后的字符串
		*/
		std::string UTF8ToGBK(const std::string& strUTF8);
		/**
			*  @date        2016/06/01 14:01
			*  @brief       查找字符串，并替换
			*  @param[in]   s1[string&]输入待替换的完整字符串
			*  @param[in]   s2[string&]输入要替换的原字符
			*  @param[in]   s3[string&]输入要替换的目标字符
			*  @return      void
			*  @remarks     对字符串进行查找并替换
			*/
		void ReplaceSrc(std::string&s1, const std::string&s2, const std::string&s3);
		/**
			*  @date        2016/06/01 14:15
			*  @brief       对明文字符串进行base64编码
			*  @param[in]   Data[char*]输入要编码的字符串
			*  @param[in]   BataByet[int]要编码字符串的长度
			*  @return      返回编码之后字符串
			*  @par			参考实例
			*  @code
			std::string src="DayBreak";
			std::string result=Base64Encode(src,src.size());//result="ABDCE_CES";
			@endcode
			*/
		std::string Base64Encode(const char* Data, int DataByte);
		/**
			*  @date        2016/06/01 14:22
			*  @brief       对base64的编码进行解码成明文
			*  @param[in]   Data[char*]输入要解码的字符串
			*  @param[in]   DataByte[int]要解码字符串的长度
			*  @param[out]  OutByte[int]解码之后字符串长度
			*  @return      返回解码之后字符串
			*  @par			参考实例
			*  @code
			std::string src="ABDCE_CES";
			std::string result=Base64Decode(src,src.size());//result="DayBreak";
			@endcode
			*/
		std::string Base64Decode(const char* Data, int DataByte, int& OutByte);
		/**
			*  @date        2016/06/01 14:28
			*  @brief       将url中的中文进行编码
			*  @param[in]   szToEncode[string&]要进行编码的字符串
			*  @return      返回编码之后字符串
			*/
		std::string UrlEncode(const std::string& szToEncode);
		/**
		*  @date        2016/06/01 14:28
		*  @brief       将url中的中文进行解码
		*  @param[in]   szToEncode[string&]要进行解码的字符串
		*  @return      返回解码之后字符串
		*/
		std::string UrlDecode(const std::string& szToDecode);
		/**
			*  @date        2016/06/01 14:31
			*  @brief       判断json格式正确与否
			*  @param[in]   src[string]要进行判断的json字符串
			*  @return      成功返回true，否则为false
			*/
		bool CheckFormatJson(std::string src);
		/**
		*  @date        2016/06/01 14:31
		*  @brief       将unicode字符串转换完成ascii字符串
		*  @param[in]   str[wstring]要进转码的字符串
		*  @return      返回转码之后字符串
		*/
		std::string U2A(const std::wstring& str);
		/**
		*  @date        2016/06/01 14:31
		*  @brief       将ascii字符串转换成unicode字符串
		*  @param[in]   str[string]要进行转换的字符串
		*  @return      返回转码之后字符串
		*/
		std::wstring A2U(const std::string& str);
		/**
		*  @date        2016/06/01 14:31
		*  @brief       将unicode转成utf-8
		*  @param[in]   wstrUnicode[wstring]要进行转码的字符串
		*  @return      返回转码之后的字符串
		*/
		std::string U2Utf(const std::wstring& wstrUnicode);
		/**
		*  @date        2016/06/01 14:31
		*  @brief       将utf-8转换成unicode
		*  @param[in]   str[string]要进行转码的字符串
		*  @return      返回转码之后的字符串
		*/
		std::wstring Utf2U(const std::string &str);
		/**
			*  @date        2016/06/01 14:38
			*  @brief       对宽字符串进行指定字符进行分割
			*  @param[in]   strSource[wstring]要拆分的原字符串
			*  @param[int]  strFlag[wstring]制定分割符
			*  @param[out]  paramList[vector<wstring>]拆分之后结果
			*  @return      成功返回true，否则为false
			*/
		bool SplitStringW(const std::wstring& strSource, const std::wstring& strFlag, std::vector<std::wstring>& paramList);
		/**
		*  @date        2016/06/01 14:38
		*  @brief       对字符串进行指定字符进行分割
		*  @param[in]   strSource[string]要拆分的原字符串
		*  @param[int]  strFlag[string]制定分割符
		*  @param[out]  paramList[vector<string>]拆分之后结果
		*  @return      成功返回true，否则为false
		*/
		bool SplitStringA(const std::string& strSource, const std::string& strFlag, std::vector<std::string>& paramList);
		/**
		*  @date        2016/06/01 14:38
		*  @brief       对宽字符串进行替换
		*  @param[in]   strContent[wstring]要替换的原字符串
		*  @param[int]  strTag[wstring]要替换的字符
		*  @param[int]  strReplace[wstring]替换成的字符
		*  @return      返回替换结果
		*/
		std::wstring StrReplaceW(const std::wstring& strContent, const std::wstring& strTag, const std::wstring& strReplace);
		/**
		*  @date        2016/06/01 14:38
		*  @brief       对字符串进行替换
		*  @param[in]   strContent[string]要替换的原字符串
		*  @param[int]  strTag[string]要替换的字符
		*  @param[int]  strReplace[string]替换成的字符
		*  @return      返回替换结果
		*/
		std::string StrReplaceA(const std::string& strContent, const std::string& strTag, const std::string& strReplace);
		/**
			*  @date        2016/06/01 14:44
			*  @brief       读取文件
			*  @param[in]   filPaht[string]文件路径
			*  @param[in]   format[string]读取模式
			*				- r 读取
			*				- w 可写
			*				- a 添加
			*				- t 文本模式(不能与 b 联用)
			*				- b 二进制模式(不能与 t 联用)
			*  @param[out]  message[string&]读取内容
			*  @return      0 是成功，其它失败
			*/
		int ReadFileDate(std::string filePaht, std::string &message, std::string format);
		/**
		*  @date        2016/06/01 14:44
		*  @brief       写文件
		*  @param[in]   filename[string]文件路径
		*  @param[in]   format[string]读取模式\n
		*				- r 读取
		*				- w 可写
		*				- a 添加
		*				- t 文本模式(不能与 b 联用)
		*				- b 二进制模式(不能与 t 联用)
		*  @param[in]	date[unsigned char*]写文件数据
		*  @param[in]   len[int]写文件数据大小
		*  @return      0 是成功，其它失败
		*/
		int WriteFileDate(std::string filename, unsigned char* date, int len, std::string format);
		/**
			*  @date        2016/06/01 14:59
			*  @brief       对程序传入的参数进行解析
			*  @param[in]   tmpPara[string] 待解析的参数列表
			*  @param[int]  item[char*]要解析那个参数的简称和全名 e.g i&input i对应着参数列表中的-i
			*  @return      返回解析结果
			*  @pre         - item可以使用多个\n
			*/
		std::map<std::string, std::vector<std::string> > ParsingArgsSrc(std::string tmpPara, char*item, ...);
		/**
			*  @date        2016/06/01 15:03
			*  @brief       对明文字符串进行密码加密
			*  @param[in]   szSource[string]要加密的明文字符串
			*  @param[in]   szPassWord[string]加密的密码
			*  @return      加密之的字符串
			*/
		std::string SrcEncrypt(std::string szSource, std::string szPassWord);
		/**
		*  @date        2016/06/01 15:03
		*  @brief       对加密字符串进行密码解密
		*  @param[in]   szSource[string]要解密的明文字符串
		*  @param[in]   szPassWord[string]解密的密码
		*  @return      解密之的字符串
		*/
		std::string SrcDecrypt(std::string szSource, std::string szPassWord);
		/**
		*  @date        2016/06/01 15:03
		*  @brief       校验文件（多个）的MD5、SHA1、SHA256、CRC32
		*  @param[in]   infile[vector<string>]校验文件列表
		*  @param[out]  outre[vector<Result>]校验结果
		*  @return      - 0为成功 - 其它为失败 在Result中的strError得知错误
		*  @see			gpl::ResultData
		*/
		int getFileVerify(std::vector<std::string> &infile, std::vector<Result> &outre);
	};

}


#endif // UTIL_H
