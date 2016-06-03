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
	/**
	*  @author      DayBreakZhang(a365316465@gmail.com)
	*  @date        2016/05/31 11:01
	*  @class       ResultData
	*  @brief       У���ļ����ؽ���Ľṹ��
	*/
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
		*  @par	        utf-8,GB2312,unicode����
		*  @code
		UTF-8��Unicode TransformationFormat-8bit������BOM����ͨ������BOM�������Խ���������ַ���һ�ֶ��ֽڱ��룬����Ӣ��ʹ��8λ����һ���ֽڣ�������ʹ��24Ϊ�������ֽڣ������롣UTF-8����ȫ�������й�����Ҫ�õ����ַ����ǹ��ʱ��룬ͨ����ǿ��UTF-8��������ֿ����ڸ���֧��UTF8�ַ��������������ʾ���磬�����UTF8���룬��������˵�Ӣ��IE��Ҳ����ʾ���ģ�������������IE����������֧�ְ���
		GBK�ǹ��ұ�׼GB2312���������ݺ����GB2312�ı�׼��GBK�����ֱ�������˫�ֽ�����ʾ�ģ��������С�Ӣ���ַ���ʹ��˫�ֽ�����ʾ��Ϊ���������ģ��������λ���趨��1��GBK����ȫ�������ַ����ǹ��ұ��룬ͨ���Ա�UTF8�����UTF8ռ�õ����ݿ��GBD��
		GBK��GB2312����UTF8֮�䶼����ͨ��Unicode��������໥ת��
		GBK��GB2312����Unicode����UTF8
		UTF8����Unicode����GBK��GB2312
		*  @endcode
		*  @par			Base64����
		*  @code
		Base64��һ����64���ַ�����ʾ������������ݵķ�����
		�ü��±���exe��jpg��pdf��Щ�ļ�ʱ�����Ƕ��ῴ��һ������룬��Ϊ�������ļ������ܶ��޷���ʾ�ʹ�ӡ���ַ������ԣ����Ҫ�ü��±��������ı���������ܴ�����������ݣ�����Ҫһ�������Ƶ��ַ�����ת��������Base64��һ������Ķ����Ʊ��뷽��.
		Base64��һ����������Ƶ��ı��ַ����ı��뷽������������URL��Cookie����ҳ�д����������������ݡ�
		*  @endcode
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
			*  @brief       ��˫�ֽ�unicode�ı���ת���ɵ��ֽ�utf-8�ı���(�����ַ�����/���)
			*  @param[in]   pText[wchar_t*]����һ��unicode�����˫�ֽ�
			*  @param[out]  pOut[char*]���utf-8�ı��뵥�ֽ�
			*  @return      void
			*  @pre         -#����˫�ֽ�unicode�ַ�\n -#���һ�����ֽ�utf-8�ַ�
			*  @remarks     ʹ������������Խ�unicode wchar=>char utf-8
			*  @see         �ο�����
			*/
		void UnicodeToUTF_8(char* pOut, wchar_t* pText);
		/**
			*  @date        2016/06/01 10:13
			*  @brief       ��unicode����ת����GB2312�ı���(�����ַ�����/���)
			*  @param[in]   uDate[wchr_t*] ����Unicode��������
			*  @param[out]  pOut[char*] ���GB2312��������
			*  @return      void
			*  @pre         -#����˫�ֽ�unicode�ַ�\n -#���һ�����ֽ�GB2312�ַ�
			*  @remarks     ʹ������������Խ�unicode�ַ�ת����GB2312
			*  @see         �ο�����
			*/
		void UnicodeToGB2312(char* pOut, wchar_t uData);
		/**
			*  @date        2016/06/01 10:17
			*  @brief       ��GB2312����ת����Unicode����(�����ַ�����/���)
			*  @param[in]	gbBuffer[char*] ����GB2312�����ַ�
			*  @param[out]  pOut[wchar_t*] ���Unicode�����ַ�
			*  @return      void
			*  @pre          -#���һ�����ֽ�GB2312�ַ�\n -#����˫�ֽ�unicode�ַ�
			*  @remarks     ʹ������������Խ�GB2312�ַ�ת����unicode
			*  @see         �ο�����
			*/
		void Gb2312ToUnicode(wchar_t* pOut, char *gbBuffer);
		/**
			*  @date        2016/06/01 10:41
			*  @brief       ��GB2312����ת����utf-8���루����ַ�����/�����
			*  @param[in]    pText[char*] ����GB2312���ַ���ָ�루std::string src.c_src()��
			*  @param[in]    pLen[int]����pText�ַ����ĳ��ȣ�std::string src.size()��
			*  @param[out]   pOut[string&] ���ת��֮����ַ�
			*  @return      void
			*  @pre         -#�������ַ�ָ��\n -#���̣�GB2312->Unicode->Utf-8
			*  @remarks      ʹ������������Խ�GB2312����ת����utf-8����
			*  @see         �ο�����
			*/
		void GB2312ToUTF_8(std::string& pOut, char *pText, int pLen);
		/**
			*  @date        2016/06/01 10:50
			*  @brief       ��utf-8����ת����GB2312���루����ַ�����/�����
			*  @param[in]   pText[char*]����utf-8�����ʽ�ַ���
			*  @param[in]   pLen[int]����pText���ַ�������
			*  @param[out]  pOut[string&]���ת��֮����ַ���
			*  @return      void
			*  @pre         -#�������ַ�ָ��\n -#���̣�UTF-8->Unicode->GB2312
			*  @remarks     ʹ������������Խ�UTF-8����ת����GB2312����
			*  @see         �ο�����
			*/
		void UTF_8ToGB2312(std::string &pOut, char *pText, int pLen);
		/**
			*  @date        2016/06/01 11:38
			*  @brief       ��intת�ɵ�string
			*  @param[in]   n[int] ����Ҫת����int����
			*  @return      ����ת��֮����ַ���
			*/
		std::string intTOStirng(const int n);
		/**
		*  @date        2016/06/01 11:38
		*  @brief       ��doubleת�ɵ�string
		*  @param[in]   n[double] ����Ҫת����double����
		*  @return      ����ת��֮����ַ���
		*/
		std::string DoubleTOString(const double n);
		/**
		*  @date        2016/06/01 11:38
		*  @brief       ��stringת�ɵ�����
		*  @param[in]   src[char*] ����Ҫת�����ַ���
		*  @return      ����ת��֮�������
		*/
		int StringToInt(const char* src);
		/**
		*  @date        2016/06/01 11:38
		*  @brief       ��stringת�ɵ�����
		*  @param[in]   src[char*] ����Ҫת�����ַ���
		*  @return      ����ת��֮�������
		*/
		double StringTODouble(const char* src);
		/**
			*  @date        2016/06/01 13:48
			*  @brief       �Էָ�����з��ַ���
			*  @param[in]   str[string&] ������ַ�����ʹ���ض�����ͬ���ַ����зָ�
			*  @param[in]   pattern[string&] ����ָ��
			*  @return      ���طָ�Ľ��
			*  @pre         -#�ָ����ͬ
			*  @remarks     ��ʹ����������ԡ�1��2��34��5��6���������ַ������зָ�
			*  @see         �ο�����
			*  @par			�ο�ʵ��
			*  @code
			std::string src ="1,2.1,315,45,21.0,548.0";
			std::vector<std::stirng> result = split(src,",");//result[0]=1;result[1]=2.1
			@endcode
			*/
		std::vector<std::string> split(std::string &str, std::string &pattern);
		/**
			*  @date        2016/06/01 13:54
			*  @brief       ��GBK����ת����UTF-8����
			*  @param[in]   strGBK[string&] ����GBK�����ʽ���ַ���
			*  @return      ���ر���֮����ַ���
			*/
		std::string GBKToUTF8(const std::string& strGBK);
		/**
		*  @date        2016/06/01 13:54
		*  @brief       ��UTF-8����ת����GBK����
		*  @param[in]   strGBK[string&] ����UTF-8�����ʽ���ַ���
		*  @return      ���ر���֮����ַ���
		*/
		std::string UTF8ToGBK(const std::string& strUTF8);
		/**
			*  @date        2016/06/01 14:01
			*  @brief       �����ַ��������滻
			*  @param[in]   s1[string&]������滻�������ַ���
			*  @param[in]   s2[string&]����Ҫ�滻��ԭ�ַ�
			*  @param[in]   s3[string&]����Ҫ�滻��Ŀ���ַ�
			*  @return      void
			*  @remarks     ���ַ������в��Ҳ��滻
			*/
		void ReplaceSrc(std::string&s1, const std::string&s2, const std::string&s3);
		/**
			*  @date        2016/06/01 14:15
			*  @brief       �������ַ�������base64����
			*  @param[in]   Data[char*]����Ҫ������ַ���
			*  @param[in]   BataByet[int]Ҫ�����ַ����ĳ���
			*  @return      ���ر���֮���ַ���
			*  @par			�ο�ʵ��
			*  @code
			std::string src="DayBreak";
			std::string result=Base64Encode(src,src.size());//result="ABDCE_CES";
			@endcode
			*/
		std::string Base64Encode(const char* Data, int DataByte);
		/**
			*  @date        2016/06/01 14:22
			*  @brief       ��base64�ı�����н��������
			*  @param[in]   Data[char*]����Ҫ������ַ���
			*  @param[in]   DataByte[int]Ҫ�����ַ����ĳ���
			*  @param[out]  OutByte[int]����֮���ַ�������
			*  @return      ���ؽ���֮���ַ���
			*  @par			�ο�ʵ��
			*  @code
			std::string src="ABDCE_CES";
			std::string result=Base64Decode(src,src.size());//result="DayBreak";
			@endcode
			*/
		std::string Base64Decode(const char* Data, int DataByte, int& OutByte);
		/**
			*  @date        2016/06/01 14:28
			*  @brief       ��url�е����Ľ��б���
			*  @param[in]   szToEncode[string&]Ҫ���б�����ַ���
			*  @return      ���ر���֮���ַ���
			*/
		std::string UrlEncode(const std::string& szToEncode);
		/**
		*  @date        2016/06/01 14:28
		*  @brief       ��url�е����Ľ��н���
		*  @param[in]   szToEncode[string&]Ҫ���н�����ַ���
		*  @return      ���ؽ���֮���ַ���
		*/
		std::string UrlDecode(const std::string& szToDecode);
		/**
			*  @date        2016/06/01 14:31
			*  @brief       �ж�json��ʽ��ȷ���
			*  @param[in]   src[string]Ҫ�����жϵ�json�ַ���
			*  @return      �ɹ�����true������Ϊfalse
			*/
		bool CheckFormatJson(std::string src);
		/**
		*  @date        2016/06/01 14:31
		*  @brief       ��unicode�ַ���ת�����ascii�ַ���
		*  @param[in]   str[wstring]Ҫ��ת����ַ���
		*  @return      ����ת��֮���ַ���
		*/
		std::string U2A(const std::wstring& str);
		/**
		*  @date        2016/06/01 14:31
		*  @brief       ��ascii�ַ���ת����unicode�ַ���
		*  @param[in]   str[string]Ҫ����ת�����ַ���
		*  @return      ����ת��֮���ַ���
		*/
		std::wstring A2U(const std::string& str);
		/**
		*  @date        2016/06/01 14:31
		*  @brief       ��unicodeת��utf-8
		*  @param[in]   wstrUnicode[wstring]Ҫ����ת����ַ���
		*  @return      ����ת��֮����ַ���
		*/
		std::string U2Utf(const std::wstring& wstrUnicode);
		/**
		*  @date        2016/06/01 14:31
		*  @brief       ��utf-8ת����unicode
		*  @param[in]   str[string]Ҫ����ת����ַ���
		*  @return      ����ת��֮����ַ���
		*/
		std::wstring Utf2U(const std::string &str);
		/**
			*  @date        2016/06/01 14:38
			*  @brief       �Կ��ַ�������ָ���ַ����зָ�
			*  @param[in]   strSource[wstring]Ҫ��ֵ�ԭ�ַ���
			*  @param[int]  strFlag[wstring]�ƶ��ָ��
			*  @param[out]  paramList[vector<wstring>]���֮����
			*  @return      �ɹ�����true������Ϊfalse
			*/
		bool SplitStringW(const std::wstring& strSource, const std::wstring& strFlag, std::vector<std::wstring>& paramList);
		/**
		*  @date        2016/06/01 14:38
		*  @brief       ���ַ�������ָ���ַ����зָ�
		*  @param[in]   strSource[string]Ҫ��ֵ�ԭ�ַ���
		*  @param[int]  strFlag[string]�ƶ��ָ��
		*  @param[out]  paramList[vector<string>]���֮����
		*  @return      �ɹ�����true������Ϊfalse
		*/
		bool SplitStringA(const std::string& strSource, const std::string& strFlag, std::vector<std::string>& paramList);
		/**
		*  @date        2016/06/01 14:38
		*  @brief       �Կ��ַ��������滻
		*  @param[in]   strContent[wstring]Ҫ�滻��ԭ�ַ���
		*  @param[int]  strTag[wstring]Ҫ�滻���ַ�
		*  @param[int]  strReplace[wstring]�滻�ɵ��ַ�
		*  @return      �����滻���
		*/
		std::wstring StrReplaceW(const std::wstring& strContent, const std::wstring& strTag, const std::wstring& strReplace);
		/**
		*  @date        2016/06/01 14:38
		*  @brief       ���ַ��������滻
		*  @param[in]   strContent[string]Ҫ�滻��ԭ�ַ���
		*  @param[int]  strTag[string]Ҫ�滻���ַ�
		*  @param[int]  strReplace[string]�滻�ɵ��ַ�
		*  @return      �����滻���
		*/
		std::string StrReplaceA(const std::string& strContent, const std::string& strTag, const std::string& strReplace);
		/**
			*  @date        2016/06/01 14:44
			*  @brief       ��ȡ�ļ�
			*  @param[in]   filPaht[string]�ļ�·��
			*  @param[in]   format[string]��ȡģʽ
			*				- r ��ȡ
			*				- w ��д
			*				- a ���
			*				- t �ı�ģʽ(������ b ����)
			*				- b ������ģʽ(������ t ����)
			*  @param[out]  message[string&]��ȡ����
			*  @return      0 �ǳɹ�������ʧ��
			*/
		int ReadFileDate(std::string filePaht, std::string &message, std::string format);
		/**
		*  @date        2016/06/01 14:44
		*  @brief       д�ļ�
		*  @param[in]   filename[string]�ļ�·��
		*  @param[in]   format[string]��ȡģʽ\n
		*				- r ��ȡ
		*				- w ��д
		*				- a ���
		*				- t �ı�ģʽ(������ b ����)
		*				- b ������ģʽ(������ t ����)
		*  @param[in]	date[unsigned char*]д�ļ�����
		*  @param[in]   len[int]д�ļ����ݴ�С
		*  @return      0 �ǳɹ�������ʧ��
		*/
		int WriteFileDate(std::string filename, unsigned char* date, int len, std::string format);
		/**
			*  @date        2016/06/01 14:59
			*  @brief       �Գ�����Ĳ������н���
			*  @param[in]   tmpPara[string] �������Ĳ����б�
			*  @param[int]  item[char*]Ҫ�����Ǹ������ļ�ƺ�ȫ�� e.g i&input i��Ӧ�Ų����б��е�-i
			*  @return      ���ؽ������
			*  @pre         - item����ʹ�ö��\n
			*/
		std::map<std::string, std::vector<std::string> > ParsingArgsSrc(std::string tmpPara, char*item, ...);
		/**
			*  @date        2016/06/01 15:03
			*  @brief       �������ַ��������������
			*  @param[in]   szSource[string]Ҫ���ܵ������ַ���
			*  @param[in]   szPassWord[string]���ܵ�����
			*  @return      ����֮���ַ���
			*/
		std::string SrcEncrypt(std::string szSource, std::string szPassWord);
		/**
		*  @date        2016/06/01 15:03
		*  @brief       �Լ����ַ��������������
		*  @param[in]   szSource[string]Ҫ���ܵ������ַ���
		*  @param[in]   szPassWord[string]���ܵ�����
		*  @return      ����֮���ַ���
		*/
		std::string SrcDecrypt(std::string szSource, std::string szPassWord);
		/**
		*  @date        2016/06/01 15:03
		*  @brief       У���ļ����������MD5��SHA1��SHA256��CRC32
		*  @param[in]   infile[vector<string>]У���ļ��б�
		*  @param[out]  outre[vector<Result>]У����
		*  @return      - 0Ϊ�ɹ� - ����Ϊʧ�� ��Result�е�strError��֪����
		*  @see			gpl::ResultData
		*/
		int getFileVerify(std::vector<std::string> &infile, std::vector<Result> &outre);
	};

}


#endif // UTIL_H
