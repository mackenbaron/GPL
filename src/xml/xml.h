#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>


/**
	*  Copyright (c) 2016, DayBreak(https://github.com/DayBreakZhang)
	*  All rights reserved.
	*
	*  @file        xml.h
	*  @author      DayBreakZhang(a365316465@gmail.com)
	*  @date        2016/06/14 10:13
	*
	*  @brief       ��libxml2���ж��η�װ���������
	*  @note        ��װ֧��xml�Ķ�д���Լ���xpath��֧�֣����ĵ�֧��
	*
	*  @version
	*    - v1.0    2016/06/14 10:13    DayBreakZhang    0.1
	*  @todo	    ��
	*/

namespace gpl
{
	/**
		*  @author      DayBreakZhang(a365316465@gmail.com)
		*  @date        2016/06/14 10:53
		*  @class       xml XML�ĵ�������
		*  @brief       XML�ĵ�������
		*  @par	        XPATH����
		*  @code
		XPATH�ṹ��/step/step/...
		����step�ĽṹΪ��axis::node-test[prediates]
		axis���ؼ��֣����ҽ���һ��������ʾ����ڵ��������Ľڵ�Ĺ�ϵ�������µ�ֵ��
		ancestor,ancestor-or-self,attribute,child,descendant,descendant-or-self,following,
		following-sibling,namespace,parent,preceding,preceding-sibling,self
		����ʡ�ԣ�Ĭ��ֵΪchild
		"attribute::"���Լ�дΪ"@"
		node-test���ڵ���ԣ����ҽ���һ��������ʾ����ڵ�����ͻ����ƣ�
		��axis=attributeʱΪ�������ƣ�
		��axis=namespaceʱΪ�����ռ����ƣ�
		��axis=����ʱΪԪ�����ƻ򳣹���ԣ�text(),comment()
		text()     Ϊ���Դ�ӡ���ı��ڵ�ֵ
		comment()  Ϊ���Դ�ӡ��ע�ͽڵ�ֵ
		prediates��ν�ʣ��㵽��������������������ƽ����������ʽ
		*  @endcode
		*  @par	        XPATH����
		*  @code
		@*
		ѡ��ǰ�ڵ����������
		para[1] ��Ч�� para[position()=1]
		ѡ��ǰ�ڵ��µĵ�1���ڵ�����Ϊpara��Ԫ��
		para[last()] ��Ч�� para[position()=last()]
		ѡ��ǰ�ڵ��µ����һ���ڵ�����Ϊpara��Ԫ��
		/doc/chapter[5]/section[2]
		ѡ���5������Ϊchapter�Ľڵ��µĵ�2������Ϊsection�Ľڵ�
		para[@type="warning"]
		ѡ��ǰ�ڵ��º�������type������Ϊwarning�Ľڵ㣬���ҽڵ�����Ϊpara
		para[@type="warning"][5]
		ѡ��ǰ�ڵ��º�������type������Ϊwarning�Ľڵ㣬�����ǵ�5������Ϊpara�Ľڵ�
		chapter[title]
		ѡ��ǰ�ڵ��º���title�ڵ�������Ϊchapter�����еĽڵ�
		employee[@secretary and @assistant]
		ѡ��ǰ�ڵ��º���secretary���Ժ�assistant����������Ϊemployee�����нڵ�

		˵�����£�
		/EXAMPLE/chapter/image[1]/attribute::*
		/EXAMPLE/chapter/image[1]/@*
		��������image[1]�ڵ�������:
		{"href","linus.gif"}
		{"width","230"}

		/EXAMPLE/chapter/image[1]/attribute::href
		/EXAMPLE/chapter/image[1]/@href
		ֻ����image[1]�ڵ�����������Ϊhref����������:
		{"href","linus.gif"}

		/child::EXAMPLE/child::chapter[1]/child::title[2]/child::text()
		/EXAMPLE/chapter[1]/title[2]/text()
		����title[2]���ı��ڵ�:
		{"text","The Linux adventure2"}

		/child::EXAMPLE/child::chapter[1]/child::title
		/EXAMPLE/chapter[1]/title
		����/EXAMPLE/chapter����������Ϊtitle�Ľڵ�:
		{"title","The Linux adventure1"}
		{"title","The Linux adventure2"}

		/EXAMPLE/chapter/image[2]/child::comment()
		/EXAMPLE/chapter/image[2]/comment()
		����/EXAMPLE/chapter/image[2]�����е�ע�ͽڵ�:
		{"comment","comment1 fffffffffffffffff"}
		{"comment","comment2 asadfdfdfdf"}

		/EXAMPLE/indb/dbname
		��������:
		{"dbname","gprs"}

		/EXAMPLE/indb/dbpassword
		��������:
		{"dbpassword","gprs123"}
		*  @endcode

		*  @par	        xmlʵ��
		*  @code
		string xpath,fname,entName,tmpStr;
		Xml xmlApi;
		multimap<string,string> resultSet;
		map<string,string> props;

		if(xml.open(fname)==false)
		{
		cerr<<"ERROR:open file:"<<fname<<endl;
		exit(-1);
		}
		if(xml.getEntityValue(entName,props)==false)
		cerr<<"ERROR: Entity "<<entName<<" does not exist!"<<endl;
		if(xml.setXPath(xpath.c_str())==false)
		{
		cerr<<"ERROR:setXPath!"<<endl;
		xml.close();
		exit(0);
		}
		if(xml.getXPathResultSet(resultSet)==false)
		cerr<<"ERROR:can't get!"<<endl;
		xml.close();
		*  @endcode
		*  @attention   ע��
		*  @bug	    ����
		*  @warning     ����
		*  @note	��
		*/
	class xml{
	public:
		/**
			*  @date        2016/06/14 13:28
			*  @brief       ���캯��
			*/
		xml();
		/**
			*  @date        2016/06/14 13:28
			*  @brief       ��������
			*/
		virtual ~xml();
	public:
		/**
		*  @date        2016/06/14 13:47
		*  @brief       �򿪲�����xml�ĵ�
		*  @param[in]   fileName[string]����xml�ĵ�·��
		*  @param[int]	blank[int] ģʽ
		- 1:�����ո�;
		- 0:ȥ���ո�
		*  @return		���ؽ��
		- true:�򿪳ɹ�;
		- false:��ʧ��;
		*/
		bool openXPath(const std::string& fileName, int blank = 1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       �򿪲�����xml�ĵ�
		*  @param[in]   fileName[char*]����xml�ĵ�·��
		*  @param[int]	blank[int]
		- 1:�����ո�;
		- 0:ȥ���ո�
		*  @return		���ؽ��
		- true:�򿪳ɹ�;
		- false:��ʧ��;
		*/
		bool openXPath(const char* fileName, int blank = 1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       �򿪲����������е�xml�ĵ�
		*  @param[in]   buffer[char*]�ڴ���buffer
		*  @param[in]	size[int]buffer��С
		*  @param[int]	blank[int]
		- 1:�����ո�;
		- 0:ȥ���ո�
		*  @return		���ؽ��
		- true:�򿪳ɹ�;
		- false:��ʧ��;
		*/
		bool openBufferXPath(const char* buffer, int size = -1, int blank = 1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       �رղ��ͷ�xml�ĵ�
		*/
		void closeXPath();
		/**
		*  @date        2016/06/14 13:47
		*  @brief       ����XPATH
		*  @param[in]   xpath[char*]XPATH������
		*  @return		���ؽ��
		- true:���óɹ�;
		- false:����ʧ��;
		*/
		bool setXPath(const char* xpath);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       ���ص�ǰXPATH����ѯ�Ľ����
		*  @param[out]  resultSet[multimap<string, string>]XPATH����ѯ�Ľ����
		- ��һ��stringΪ�ڵ�����,��������,text,comment�е�һ��
		- �ڶ���stringΪ�ڵ����ƶ�Ӧ���ı��ڵ�����,��������Ӧ����������,ע�������е�һ��
		*  @return		���ؽ��
		- true:�ɹ�;
		- false:ʧ��;
		*/
		bool getXPathResultSet(std::multimap<std::string, std::string>& resultSet);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       ���ص�ǰXPATH����ѯ�Ľ����
		*  @param[in]	xpath[char*]XPATH������
		*  @param[out]  resultSet[multimap<string, string>]XPATH����ѯ�Ľ����
		- ��һ��stringΪ�ڵ�����,��������,text,comment�е�һ��
		- �ڶ���stringΪ�ڵ����ƶ�Ӧ���ı��ڵ�����,��������Ӧ����������,ע�������е�һ��
		*  @return		���ؽ��
		- true:�ɹ�;
		- false:ʧ��;
		*/
		bool getXPathResultSet(const char* xpath, std::multimap<std::string, std::string>& resultSet);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       ��ȡָ����ʵ���������
		*  @param[in]	entName[string]Ҫ��ѯ��ʵ����
		*  @param[out]  props[map<string, string>]entName��Ӧ��ʵ������,������
		- ETYPE:  ʵ�������
		- ID:     PUBLIC���ⲿ��ʶ
		- SYSTEM: PUBLIC,SYSTEMʵ���url·��
		- ORIG:   ʵ������û�б��滻������
		- CONTENT:û�н���ʱ�����ݻ�����
		*  @return		���ؽ��
		- true:�ɹ�;
		- false:ʧ��;
		*/
		bool getEntityValue(const std::string& entName, std::map<std::string, std::string>& props);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       �ڵ�ǰXPATH�������һ���ӽڵ�.
		- ����XPATH���ж����ͬ�Ľڵ�����,����û��ָ��λ��,��ô��Ĭ�ϲ����һ��λ�õ�����,�����ӽڵ��������ӽڵ�������,����Ͳ���ָ����λ������
		@code
		��ǰ��XPATH��"/EXAMPLE/head"
		insertNodeByXPath("subhead","hello");
		<?xml version="1.0" ><EXAMPLE><head></head></EXAMPLE>
		�������:
		<?xml version="1.0" ><EXAMPLE><head><subhead>hello</subhead></head></EXAMPLE>
		@endcode
		- ���ýڵ�����Ϊ�������һ���ı��ڵ�(��nodeValue),���Ѿ������ı��ڵ�,���׷�ӵ���һ���ı��ڵ���,Ȼ�󷵻�true;
		- ���ýڵ�����Ϊ"<![CDATA[]]>"�����һ��CDATA�ε��ַ��ڵ�(��nodeValue),���Ѿ�����CDATA��,���׷�ӵ���һ���ı��ڵ���,Ȼ�󷵻�true;
		*  @param[in]	nodeName[char*]�ڵ�����
		*  @param[in]	nodeValue[char*]�ڵ��ֵ
		*  @param[in]	length[int]nodeValue�ĳ���
		*  @return		���ýڵ����Ʒǿ������һ���ڵ�(��nodeName),���Ѿ����ڸýڵ�,�򷵻�false,���򷵻�true;
		*/
		bool insertNodeByXPath(const char* nodeName, const char* nodeValue, int length = -1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       ��ָ����XPATH�������һ���ӽڵ�.
		- ����XPATH���ж����ͬ�Ľڵ�����,����û��ָ��λ��,��ô��Ĭ�ϲ����һ��λ�õ�����,�����ӽڵ��������ӽڵ�������,����Ͳ���ָ����λ������
		@code
		insertNodeByXPath("/EXAMPLE/head","subhead","hello")
		<?xml version="1.0" ><EXAMPLE><head></head></EXAMPLE>
		�������:
		<?xml version="1.0" ><EXAMPLE><head><subhead>hello</subhead></head></EXAMPLE>
		@endcode
		- ���ýڵ�����Ϊ�������һ���ı��ڵ�(��nodeValue),���Ѿ������ı��ڵ�,���׷�ӵ���һ���ı��ڵ���,Ȼ�󷵻�true;
		- ���ýڵ�����Ϊ"<![CDATA[]]>"�����һ��CDATA�ε��ַ��ڵ�(��nodeValue),���Ѿ�����CDATA��,���׷�ӵ���һ���ı��ڵ���,Ȼ�󷵻�true;
		*  @param[in]	xpath[char*]XPATH������
		*  @param[in]	nodeName[char*]�ڵ�����
		*  @param[in]	nodeValue[char*]�ڵ��ֵ
		*  @param[in]   length[int]nodeValue�ĳ���
		*  @return		���ýڵ����Ʒǿ������һ���ڵ�(��nodeName),���Ѿ����ڸýڵ�,�򷵻�false,���򷵻�true;
		*/
		bool insertNodeByXPath(const char* xpath, const char* nodeName, const char* nodeValue, int length = -1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       �ڵ�ǰXPATH�������һ���ڵ������.
		@code
		��ǰ��XPATH��"/EXAMPLE/head"
		insertPropertyByXPath("subhead","hello");
		<?xml version="1.0" ><EXAMPLE><head></head></EXAMPLE>
		�������:
		<?xml version="1.0" ><EXAMPLE><head subhead="hello"></head></EXAMPLE>
		@endcode
		*  @param[in]	propName[char*]��������
		*  @param[in]	propValue[char*]���Ե�ֵ
		*  @param[in]   length[int]propValue�ĳ���
		*  @return		�������������Ѿ�����,�򷵻�false,������ɹ�����true;
		*/
		bool insertPropertyByXPath(const char* propName, const char* propValue, int length = -1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       ��ָ����XPATH�������һ���ڵ������.
		@code
		insertPropertyByXPath("/EXAMPLE/head","subhead","hello");
		<?xml version="1.0" ><EXAMPLE><head></head></EXAMPLE>
		�������:
		<?xml version="1.0" ><EXAMPLE><head subhead="hello"></head></EXAMPLE>
		@endcode
		*  @param[in]	xpath[char*]XPATH������
		*  @param[in]	propName[char*]��������
		*  @param[in]	propValue[char*]����ֵ
		*  @param[in]   length[int]propValue�ĳ���
		*  @return		�������������Ѿ�����,�򷵻�false,������ɹ�����true;
		*/
		bool insertPropertyByXPath(const char* xpath, const char* propName, const char* propValue, int length = -1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       �ڵ�ǰXPATH�������һ���ڵ�.
		- ����XPATH���ж����ͬ�Ľڵ�����,����û��ָ��λ��,��ô��Ĭ�ϸ��µ�һ��λ�õĽڵ�,����Ͳ���ָ���Ľڵ�
		@code
		��ǰ��XPATH��"/EXAMPLE/head"
		updateNodeByXPath("head","hello");
		<?xml version="1.0" ><EXAMPLE><head>hhhhh</head></EXAMPLE>
		�������:
		<?xml version="1.0" ><EXAMPLE><head>hello</head></EXAMPLE>
		@endcode
		*  @param[in]	nodeName[char*]�ڵ�����.Ϊ��ʱ����ԭ���Ľڵ�����,����ʹ��nodeName���Ǿ�����
		*  @param[in]	nodeValue[char*]�ڵ��ֵ
		*  @param[in]   length[int]nodeValue�ĳ���
		*  @return		- ���½ڵ�ɹ�����true,���򷵻�false;
		- ���ýڵ����Ʋ�����,�򷵻�false;
		*/
		bool updateNodeByXPath(const char* nodeName, const char* nodeValue, int length = -1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       ��ָ����XPATH�������һ���ڵ�.
		- ����XPATH���ж����ͬ�Ľڵ�����,����û��ָ��λ��,��ô��Ĭ�ϸ��µ�һ��λ�õĽڵ�,����Ͳ���ָ���Ľڵ�
		@code
		updateNodeByXPath("/EXAMPLE/head","head","hello");
		<?xml version="1.0" ><EXAMPLE><head>hhhhh</head></EXAMPLE>
		�������:
		<?xml version="1.0" ><EXAMPLE><head>hello</head></EXAMPLE>
		@endcode
		*  @param[in]	xpath[char*]XPATH������
		*  @param[in]	nodeName[char*]�ڵ�����.Ϊ��ʱ����ԭ���Ľڵ�����,����ʹ��nodeName���Ǿ�����
		*  @param[in]	nodeValue[char*]�ڵ��ֵ.
		*  @param[in]   length[int]nodeValue�ĳ���
		*  @return		- ���½ڵ�ɹ�����true,���򷵻�false;
		*		        - ���ýڵ����Ʋ�����,�򷵻�false;
		*/
		bool updateNodeByXPath(const char* xpath, const char* nodeName, const char* nodeValue, int length = -1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       �ڵ�ǰXPATH�������һ���ڵ������.
		@code
		��ǰ��XPATH��"/EXAMPLE/head"
		updatePropertyByXPath("subhead","hello");
		<?xml version="1.0" ><EXAMPLE><head subhead="hhhhh"></head></EXAMPLE>
		�������:
		<?xml version="1.0" ><EXAMPLE><head subhead="hello"></head></EXAMPLE>
		@endcode
		*  @param[in]	propName[char*]��������
		*  @param[in]	propValue[char*]���Ե�ֵ
		*  @param[in]   length[int]propValue�ĳ���
		*  @return		���³ɹ�����true;���򷵻�false;�����������Ʋ�����,�򷵻�false;
		*/
		bool updatePropertyByXPath(const char* propName, const char* propValue, int length = -1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       ��ָ����XPATH�������һ���ڵ������.
		@code
		updatePropertyByXPath("/EXAMPLE/head","subhead","hello");
		<?xml version="1.0" ><EXAMPLE><head subhead="hhhhh"></head></EXAMPLE>
		�������:
		<?xml version="1.0" ><EXAMPLE><head subhead="hello"></head></EXAMPLE>
		@endcode
		*  @param[in]	xpath[char*]XPATH������
		*  @param[in]	propName[char*]��������
		*  @param[in]	propValue[char*]���Ե�ֵ
		*  @param[in]   length[int] propValue�ĳ���
		*  @return		���³ɹ�����true;���򷵻�false;�����������Ʋ�����,�򷵻�false;
		*/
		bool updatePropertyByXPath(const char* xpath, const char* propName, const char* propValue, int length = -1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       �ڵ�ǰXPATH����ɾ�����һ���ڵ���.
		- ����XPATH���ж����ͬ�Ľڵ�����,����û��ָ��λ��,��ô��Ĭ��ɾ����һ��λ�õĽڵ���,����Ͳ���ָ���Ľڵ���
		@code
		��ǰ��XPATH��"/EXAMPLE/head"
		eraseNodeByXPath();
		<?xml version="1.0" ><EXAMPLE><head></head></EXAMPLE>
		�������:
		<?xml version="1.0" ><EXAMPLE></EXAMPLE>
		@endcode
		*  @return		ɾ���ɹ�����true,���򷵻�false;���ýڵ���������,����false!
		*/
		bool eraseNodeByXPath();
		/**
		*  @date        2016/06/14 13:47
		*  @brief       ��ָ����XPATH����ɾ�����һ���ڵ���.
		- ����XPATH���ж����ͬ�Ľڵ�����,����û��ָ��λ��,��ô��Ĭ��ɾ����һ��λ�õĽڵ���,����Ͳ���ָ���Ľڵ���
		@code
		eraseNodeByXPath("/EXAMPLE/head");
		<?xml version="1.0" ><EXAMPLE><head></head></EXAMPLE>
		�������:
		<?xml version="1.0" ><EXAMPLE></EXAMPLE>
		@endcode
		*  @param[in]	xpath[char*]XPATH������
		*  @return		ɾ���ɹ�����true,���򷵻�false;���ýڵ���������,����false!
		*/
		bool eraseNodeByXPath(const char* xpath);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       �ڵ�ǰXPATH����ɾ��һ���ڵ������
		@code
		��ǰ��XPATH��"/EXAMPLE/head"
		erasePropertyByXPath("subhead");
		<?xml version="1.0" ><EXAMPLE><head subhead="head"></head></EXAMPLE>
		�������:
		<?xml version="1.0" ><EXAMPLE><head></head></EXAMPLE>
		@endcode
		*  @param[in]	propName[char*]��������
		*  @return		ɾ���ɹ�����true,���򷵻�false;�������Բ�����,����false!
		*/
		bool erasePropertyByXPath(const char* propName);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       ��ָ����XPATH����ɾ��һ���ڵ������.
		@code
		erasePropertyByXPath("/EXAMPLE/head","subhead");
		<?xml version="1.0" ><EXAMPLE><head subhead="head"></head></EXAMPLE>
		�������:
		<?xml version="1.0" ><EXAMPLE><head></head></EXAMPLE>
		@endcode
		*  @param[in]	xpath[char*]XPATH������
		*  @param[in]	propName[char*]��������
		*  @return		ɾ���ɹ�����true,���򷵻�false;�������Բ�����,����false!
		*/
		bool erasePropertyByXPath(const char* xpath, const char* propName);

		/**
		*  @date        2016/06/14 13:47
		*  @brief       ����xml���ݵ��ļ���
		*  @param[in]	fname[char*]�ļ�����url,Ϊ��ʱ�����浽ԭ�����ļ���
		*  @param[in]	encoding[char*]ʹ�õ��ַ�����,Ĭ��Ϊ��
		*  @param[in]	format[int]0:�����и�ʽ���;1:��ʽ���,Ĭ��Ϊ1
		*  @return		�ɹ�����true,����false;
		*/
		bool saveXmlToFileXPath(const char* fname = "", const char* encoding = "", int format = 1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       ����xml���������buff�ڴ���
		*  @param[in]	buffStr[string]����Ļ���
		*  @param[in]	encoding[char*]ʹ�õ��ַ�����,Ĭ��Ϊ��
		*  @param[in]	format[int]0:�����и�ʽ���;1:��ʽ���,Ĭ��Ϊ1
		*  @return		�ɹ�����true,����false;
		*/
		bool saveXmlToBufferXPath(std::string& buffStr, const char* encoding = "", int format = 1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       ��xml�ļ�������ָ�����ļ���
		*  @param[in]	f[FILE*]�ļ�ָ��,������stdin,stdout,stderr
		*  @return		�ɹ�����true,����false;
		*/
		bool dumpXPath(FILE* f = stdout);
		/**
		* �����ڶ�ȡ����ʱ������ȡʵ�����ֵı��.
		*@param b true:������ȡʵ������;false:��ȡʵ����չ�������
		*@return �ɹ�����true,����false;
		*/
		//void setOnlyGetEntityNameFlag(bool b);
		/**
			*  @date        2016/06/15 13:28
			*  @brief       ����xml
			*  @param[in]   filname[string]����xml������,�������Ϊ�գ���ô��saveToFile����һ��Ҫд����
			*  @param[in]   encod[string]����xml�ı����ʽ��Ĭ��utf-8
			*  @return      �ɹ�����true������Ϊfalse
			*  @pre         ����һ��xml DOC��һ��ָ��
			*  @remarks     ����
			*  @see         gpl::xml::saveToFile
			*  @test        ����
			*/
		bool createXml(std::string encod = "UTF-8", std::string filename = "");
		/**
			*  @date        2016/06/15 13:41
			*  @brief       ���һ���ڵ�
			*  @param[in]   node[string]�ڵ�����
			*  @return      �ɹ�����true������Ϊfalse
			*  @pre         ���һ����nodeΪ���ֵĽڵ�
			*  @remarks     ����
			*  @see         �ο�����
			*  @test        ����
			*/
		bool addANode(std::string node);
		/**
			*  @date        2016/06/15 13:43
			*  @brief       Ϊ�ڵ����һ���ӽڵ�
			*  @param[in]   node[string]һ���Դ��ڵĽڵ����֣��������ڵ㲻���ڷ���false
			*  @param[in]   item[string]��ӵ��ӽڵ㣬�������ӽڵ���ڷ���false
			*  @param[in]   content[string]�ӽڵ��ڴ�
			*  @return      �ɹ�����true������Ϊfalse
			*  @pre         ����
			*  @remarks     ����
			*  @see         �ο�����
			*  @test        ����
			*/
		bool addAItem(std::string node, std::string item, std::string content);
		/**
			*  @date        2016/06/15 14:24
			*  @brief       ����xml���ļ�
			*  @param[in]   encod[string]����xml�ı���
			*  @param[in]   filename[string]����xml���ļ����֣���createXml���������������Ϊ��
			*  @param[in]   blankpad[bool]�Ƿ���и�ʽ�����
			*  @return      �ɹ�����true������Ϊfalse
			*  @pre         ����
			*  @remarks     ����
			*  @see         �ο�����
			*  @test        ����
			*/
		bool saveToFile(std::string encod = "UTF-8", std::string filename = "", bool blankpad = true);
	protected:
		class LibXml;
		LibXml* m_xml;
	private:
		void ltoa(const long& l, std::string& str);
		std::string m_fileName;
	};
}