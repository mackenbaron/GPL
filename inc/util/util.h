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
	*  @brief       ���õĺ����࣬��Щ�������Զ���ʹ��Ҳ���Խ��ʹ��
	*  @note        ������Ϊwchar �� char �������ͣ����û������˵������������Ҫ����ת�����������
	*
	*  @version
	*    - v1.0     2016/05/31 10:48    DayBreakZhang    0.1
	*  @todo	    -��������
	*					-#�޸��ڴ�й¶����
	*/
namespace gpl
{
	/** �����ļ�У����ķ��ؽṹ */
	typedef struct ResultData
	{
		bool bDone; /**< �����Ƿ�ɹ� */
		std::string strPath; /**< ·�� */
		__int64 ulSize; /**< ��С */
		std::string strMDate; /**< �޸����� */
		std::string strVersion;/**< �汾 */
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
	/**< �����ļ�У����ķ��ؽṹ */

	/**
		*  @author      DayBreakZhang(a365316465@gmail.com)
		*  @date        2016/05/31 11:01
		*  @class       util
		*  @brief       ���ú��������࣬���а������ַ�ת����ini�ļ���д���ַ��������滻���ַ����ָ����ȡ��url���ı�����룬��д�ļ���json��ʽ��֤���ļ�У�飬�ļ����ܽ���
		*  @attention   �������û��ָ��wchar�ĺ�����Ҫʹ��ת������������ת��
		*  @bug	        -�ѽ�������б�\n -#���ת�������ڴ�й¶����
		*  @warning     -�����б�\n -#��� ��������/���� �����õ��˺����ڲ�����ָ���ʹ�����֮��Ҫ�ͷ�
		*  @note		-�����б�\n -#������ܽ���\n -#�����ļ�У������
		*/
	class util
	{
	public:
		/**
			*  @date        2016/05/31 11:03
			*  @brief       ����ini�ļ�string����
			*  @param[in]   path[string] ini�ļ�·��������/���
			*  @param[in]   root[string] ini�ļ��Ľڵ����֣�e.g [Data]
			*  @param[in]	userkey[string] ini�ڵ�key�����֣� e.g DSN=
			*  @param[out]  uservalue[string &] ���ؽڵ�key��Ӧ�õ�ֵ e.g 192.168.0.1
			*  @param[in]	def[string] �ڵ�key��Ӧ��ֵΪ��ʱʹ��def�е�ֵ��ΪĬ��
			*  @return      void
			*  @pre         -#������Ҫת��\n -#�ļ�·��һдҪ���ҵ�
			*  @remarks     ʹ������������Զ�ȡstring���͵�key
			*  @see         �ο�����
			*  @par ����ʵ��
			*  @code
			std::string _tempDSN;
			readINIFileString(".\\config","Net","DSN",_tempDSN,"127.0.0.1");
			@endcode
			*/
		void readINIFileString(std::string path, std::string root, std::string userkey, std::string &uservalue, std::string def);
		/**
			*  @date        2016/05/31 13:41
			*  @brief       ��ȡini�ļ�int����
			*  @param[in]   path[string] ini�ļ�·��������/���
			*  @param[in]   root[string] ini�ļ��Ľڵ����֣�e.g [Data]
			*  @param[in]	userkey[string] ini�ڵ�key�����֣� e.g Port=
			*  @param[out]  uservalue[int &] ���ؽڵ�key��Ӧ�õ�ֵ e.g 8080
			*  @param[in]	def[int] �ڵ�key��Ӧ��ֵΪ��ʱʹ��def�е�ֵ��ΪĬ��
			*  @return      void
			*  @pre         -#������Ҫת��\n -#�ļ�·��һдҪ���ҵ�
			*  @remarks     ʹ������������Զ�ȡint���͵�key
			*  @see         �ο�����
			*  @par ����ʵ��
			*  @code
			int _tempDSN;
			readINIFileString(".\\config","Net","DSN",_tempDSN,8080);
			@endcode
			*/
		void readINIFileInt(std::string path, std::string root, std::string userkey, int &userValue, int def);
		/**
			*  @date        2016/05/31 13:49
			*  @brief       ��string�ַ���д��ini�ļ�
			*  @param[in]   path[string] ini�ļ�·��������/���
			*  @param[in]   root[string] ini�ļ��Ľڵ����֣�e.g [Data]
			*  @param[in]	userkey[string] ini�ڵ�key�����֣� e.g Port=
			*  @param[in]	value[string] ini�ڵ�key��ֵ�� e.g 8000
			*  @return      void
			*  @pre         -#������Ҫת��\n -#�ļ�·��һдҪ���ҵ�
			*  @remarks     ʹ������������Զ�ȡint���͵�key
			*  @see         �ο�����
			*  @par ����ʵ��
			*  @code
			std::string _tempDSN="192.168.0.25";
			writeINIFileString(".\\config","Net","DSN",_tempDSN);
			@endcode
			*/
		bool writeINIFileString(std::string path, std::string root, std::string userkey, std::string value);
		/**
			*  @date        2016/05/31 13:49
			*  @brief       ��int��ֵд��ini�ļ�
			*  @param[in]   path[string] ini�ļ�·��������/���
			*  @param[in]   root[string] ini�ļ��Ľڵ����֣�e.g [Data]
			*  @param[in]	userkey[string] ini�ڵ�key�����֣� e.g Port=
			*  @param[in]	value[int] ini�ڵ�key��ֵ�� e.g 8000
			*  @return      void
			*  @pre         -#������Ҫת��\n -#�ļ�·��һдҪ���ҵ�
			*  @remarks     ʹ������������Զ�ȡint���͵�key
			*  @see         �ο�����
			*  @par ����ʵ��
			*  @code
			int _tempDSN=8000;
			writeINIFileString(".\\config","Net","DSN",_tempDSN);
			@endcode
			*/
		bool writeINIFileInt(std::string path, std::string root, std::string userkey, int value);
		/**
			*  @date        2016/05/31 14:07
			*  @brief       �����ֽ�utf-8�ı���ת����˫�ֽ�Unicode�ı���
			*  @param[out]  pOut[wchar_t*] ��char*ת��wchar*�Ĵ�ŵ�ַ
			*  @param[in]   pTest[char*] ����һ��utf-8���ַ�
			*  @return      void
			*  @pre         -#����ĵ���char \n -#�����һ��������wchar
			*  @remarks     ʹ������������Խ� utf-8 char=>wcahr
			*  @see         �ο�����
			*/
		void UTF_8ToUnicode(wchar_t* pOut, char *pText);
		/**
			*  @date        2016/05/31 14:26
			*  @brief       ��˫�ֽ�unicode�ı���ת���ɵ��ֽ�utf-8�ı���
			*  @param[in]   pText[wchar_t*]����һ��unicode�����˫�ֽ�
			*  @param[out]  pOut[char*]���utf-8�ı��뵥�ֽ�
			*  @return      void
			*  @pre         -#����˫�ֽ�unicode�ַ�\n -#���һ�����ֽ�utf-8�ַ�
			*  @remarks     ʹ������������Խ�unicode wchar=>char utf-8
			*  @see         �ο�����
			*/
		void UnicodeToUTF_8(char* pOut, wchar_t* pText);  //Unicode ת����UTF-8
		void UnicodeToGB2312(char* pOut, wchar_t uData);  // ��Unicode ת���� GB2312
		void Gb2312ToUnicode(wchar_t* pOut, char *gbBuffer);// GB2312 ת���ɡ�Unicode
		void GB2312ToUTF_8(std::string& pOut, char *pText, int pLen);//GB2312 תΪ UTF-8
		void UTF_8ToGB2312(std::string &pOut, char *pText, int pLen);//UTF-8 תΪ GB2312
		std::string intTOStirng(const int n);//int to char
		std::string DoubleTOString(const double n);//double to char
		int StringToInt(const char* src); //char to int
		double StringTODouble(const char* src);// char to double
		std::vector<std::string> split(std::string &str, std::string &pattern);//ȡ�ָ���֮��Ķ���ַ�
		std::string GBKToUTF8(const std::string& strGBK); //gbk to utf8
		std::string UTF8ToGBK(const std::string& strUTF8);//utf8 to gbk
		void ReplaceSrc(std::string&s1, const std::string&s2, const std::string&s3);//��ѯ�滻�ַ���
		std::string Base64Encode(const unsigned char* Data, int DataByte);//����base64
		std::string Base64Decode(const char* Data, int DataByte, int& OutByte);//����base64
		std::string UrlEncode(const std::string& szToEncode);//����url ����
		std::string UrlDecode(const std::string& szToDecode);//����url ����
		bool CheckFormatJson(std::string src);//��֤json�Ƿ�Ϸ�
		std::string U2A(const std::wstring& str);//Unicode�ַ�תAscii�ַ�
		std::wstring A2U(const std::string& str);//Ascii�ַ�תUnicode
		std::string U2Utf(const std::wstring& wstrUnicode);//Unicodeתutf8 
		std::wstring Utf2U(const std::string &str);//utf8תUnicode 		 
		bool SplitStringW(const std::wstring& strSource, const std::wstring& strFlag, std::vector<std::wstring>& paramList);//�ָ��ַ���	
		bool SplitStringA(const std::string& strSource, const std::string& strFlag, std::vector<std::string>& paramList);//�ָ��ַ���
		std::wstring StrReplaceW(const std::wstring& strContent, const std::wstring& strTag, const std::wstring& strReplace);//�滻�ַ���  
		std::string StrReplaceA(const std::string& strContent, const std::string& strTag, const std::string& strReplace);//�滻�ַ��� 

		int ReadFileDate(std::string filePaht, std::string &message);//���ļ�
		int WriteFileDate(std::string filename, unsigned char* date, int len);//д�ļ�

		std::map<std::string, std::vector<std::string> > ParsingArgsSrc(std::string tmpPara, char*item, ...);//�����������
		std::string SrcEncrypt(std::string szSource, std::string szPassWord); // ���ܣ����ؼ��ܽ��
		std::string SrcDecrypt(std::string szSource, std::string szPassWord); // ���ܣ����ؽ��ܽ��
		int getFileVerify(std::vector<std::string> &infile, std::vector<Result> &outre);//����MD5��SHA1��SHA256��CRC32
	};

}


#endif // UTIL_H
