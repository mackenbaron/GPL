#pragma once
/**
	*  Copyright (c) 2016, DayBreak(https://github.com/DayBreakZhang)
	*  All rights reserved.
	*
	*  @file        json.h
	*  @author      DayBreakZhang(a365316465@gmail.com)
	*  @date        2016/06/17 15:30
	*
	*  @brief       c++����json��
	*  @note        ��json�Ĳ���������д��У�飬���л��Ȳ���
	*
	*  @version
	*    - v1.0    2016/06/17 15:30    DayBreakZhang    0.1
	*  @todo	    ��
	*/
namespace gpl
{
	/**
		*  @author      DayBreakZhang(a365316465@gmail.com)
		*  @date        2016/06/17 15:35
		*  @class       json
		*  @brief       ��josn�����ķ�װ
		*  @note		json�ĸ�ʽ���
		- json������ַ��
		- 1. http://www.json.org/json-zh.html json���
		- 2. https://www.reddit.com/  json��վ
		- 3. https://api.reddit.com/ json��������\n
		json��ʽ���
		*  @code
		JSON(JavaScript Object Notation) ��һ�������������ݽ�����ʽ�� �������Ķ��ͱ�д��ͬʱҲ���ڻ������������ɡ� ������JavaScript Programming Language, Standard ECMA-262 3rd Edition - December 1999��һ���Ӽ��� JSON������ȫ���������Ե��ı���ʽ������Ҳʹ����������C���Լ����ϰ�ߣ�����C, C++, C#, Java, JavaScript, Perl, Python�ȣ��� ��Щ����ʹJSON��Ϊ��������ݽ������ԡ�
		JSON���������ֽṹ��
		- ����/ֵ���Եļ��ϣ�A collection of name/value pairs������ͬ�������У��������Ϊ����object������¼��record�����ṹ��struct�����ֵ䣨dictionary������ϣ��hash table�����м��б�keyed list�������߹������� ��associative array����
		- ֵ�������б�An ordered list of values�����ڴ󲿷������У��������Ϊ���飨array����
		��Щ���ǳ��������ݽṹ����ʵ�ϴ󲿷��ִ���������Զ���ĳ����ʽ֧�����ǡ���ʹ��һ�����ݸ�ʽ��ͬ��������Щ�ṹ�ı������֮�佻����Ϊ���ܡ�
		*  @endcode
		json���õĸ�ʽ
		*  @code
		- ������һ������ġ�������/ֵ���ԡ����ϡ�һ�������ԡ�{���������ţ���ʼ����}���������ţ�������ÿ�������ơ����һ����:����ð�ţ�����������/ֵ�� �ԡ�֮��ʹ�á�,�������ţ��ָ���e.g{"hello":"word","hello1":"word1"}
		- ������ֵ��value�������򼯺ϡ�һ�������ԡ�[�����������ţ���ʼ����]�����������ţ�������ֵ֮��ʹ�á�,�������ţ��ָ��� e.g["a":1,"b":2]
		- ֵ��value��������˫�������������ַ�����string������ֵ(number)��true��false�� null������object���������飨array������Щ�ṹ����Ƕ�ס�
		- �ַ�����string������˫���Ű�Χ����������Unicode�ַ��ļ��ϣ�ʹ�÷�б��ת�塣һ���ַ���character����һ���������ַ�����character string����
		- �ַ�����string����C����Java���ַ����ǳ����ơ�
		- ��ֵ��number��Ҳ��C����Java����ֵ�ǳ����ơ���ȥδ��ʹ�õİ˽�����ʮ�����Ƹ�ʽ����ȥһЩ����ϸ�ڡ�
		- �հ׿��Լ��뵽�κη���֮��
		*  @endcode
		*  @attention   ע��
		*  @bug
		*  @warning     ����
		*/
	class json
	{
	public:
		/**
			*  @date        2016/06/17 15:51
			*  @brief       ���캯��
			*/
		json();
		/**
		*  @date        2016/06/17 15:51
		*  @brief       ��������
		*/
		virtual ~json();
		/**
			*  @date        2016/06/21 18:01
			*  @brief       ����json
			*  @param[in]   filename[string]json�ļ�·��
			*  @param[in]   encoded[int]���뷽ʽ - 1ΪUnicode���� - 0Ϊutf-8���루Ĭ�ϣ�
			*  @return      �ɹ�����true������Ϊfalse
			*  @pre         ����
			*  @remarks     ����
			*  @see         �ο�����
			*  @test        ����
			*/
		bool parseJson(std::string filename,int encoded);
		/**
		*  @date        2016/06/21 18:01
		*  @brief       ����json
		*  @param[in]   jsonbuf[char*]json�ڴ�
		*  @param[in]   encoded[int]���뷽ʽ - 1ΪUnicode���� - 0Ϊutf-8���루Ĭ�ϣ�
		*  @return      �ɹ�����true������Ϊfalse
		*  @pre         ����
		*  @remarks     ����
		*  @see         �ο�����
		*  @test        ����
		*/
		bool parseJson(char* jsonbuf, int encoded);
		/**
			*  @date        2016/06/21 18:02
			*  @brief       ��ȡjson�������Ĵ�С
			*  @param[in]   par[string]Ҫ�������ݴ�root��ʼ��·��
			*  @return      ���������С
			*  @pre         ����
			*  @remarks     ����
			*  @see         �ο�����
			*  @test        ����
			*/
		int getArraySize(std::string par);
		/**
			*  @date        2016/06/21 18:04
			*  @brief       ����ָ��·�����������
			*  @param[in]   par[string]Ҫ�������ݴ�root��ʼ��·��
			*  @param[out]  date[int]����int������
			*  @return      void
			*  @pre         ����
			*  @remarks     ����
			*  @see         �ο�����
			*  @test        ����
			*/
		void getItemDate(int& date, std::string par);
		/**
		*  @date        2016/06/21 18:04
		*  @brief       ����ָ��·�����������
		*  @param[in]   par[string]Ҫ�������ݴ�root��ʼ��·��
		*  @param[out]  date[string]����string������
		*  @return      void
		*  @pre         ����
		*  @remarks     ����
		*  @see         �ο�����
		*  @test        ����
		*/
		void getItemDate(std::string &date, std::string par);
		/**
		*  @date        2016/06/21 18:04
		*  @brief       ����ָ��·�����������
		*  @param[in]   par[string]Ҫ�������ݴ�root��ʼ��·��
		*  @param[out]  date[bool]����bool������
		*  @return      void
		*  @pre         ����
		*  @remarks     ����
		*  @see         �ο�����
		*  @test        ����
		*/
		void getItemDate(bool &date, std::string par);
		/**
		*  @date        2016/06/21 18:04
		*  @brief       ����ָ��·�����������
		*  @param[in]   par[string]Ҫ�������ݴ�root��ʼ��·��
		*  @param[out]  date[double]����double������
		*  @return      void
		*  @pre         ����
		*  @remarks     ����
		*  @see         �ο�����
		*  @test        ����
		*/
		void getItemDate(double &date, std::string par);
	private:
		/**
		*  @date        2016/06/21 18:04
		*  @brief       ��ȡ�ļ�����
		*  @param[in]   filename[string]�ļ�·��
		*  @return      �ļ����ݣ�Ϊ�ַ����ͣ�����ת���)
		*  @pre         ����
		*  @remarks     ����
		*  @see         �ο�����
		*  @test        ����
		*/
		std::string readFile(std::string filename);
	private:
		class LibJson;
		LibJson* m_json;
	};

}
