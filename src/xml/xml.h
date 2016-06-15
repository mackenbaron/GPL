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
	*  @brief       对libxml2进行二次封装，方便操作
	*  @note        封装支持xml的读写，以及对xpath的支持，中文的支持
	*
	*  @version
	*    - v1.0    2016/06/14 10:13    DayBreakZhang    0.1
	*  @todo	    无
	*/

namespace gpl
{
	/**
		*  @author      DayBreakZhang(a365316465@gmail.com)
		*  @date        2016/06/14 10:53
		*  @class       xml XML文档处理类
		*  @brief       XML文档处理类
		*  @par	        XPATH简述
		*  @code
		XPATH结构：/step/step/...
		其中step的结构为：axis::node-test[prediates]
		axis：关键字，有且仅有一个，它表示结果节点与上下文节点的关系，有如下的值：
		ancestor,ancestor-or-self,attribute,child,descendant,descendant-or-self,following,
		following-sibling,namespace,parent,preceding,preceding-sibling,self
		可以省略，默认值为child
		"attribute::"可以简写为"@"
		node-test：节点测试，有且仅有一个，它表示结果节点的类型或名称：
		当axis=attribute时为属性名称；
		当axis=namespace时为命名空间名称；
		当axis=其他时为元素名称或常规测试：text(),comment()
		text()     为测试打印其文本节点值
		comment()  为测试打印其注释节点值
		prediates：谓词，零到多个，它可以是用于限制结果的任意表达式
		*  @endcode
		*  @par	        XPATH例子
		*  @code
		@*
		选择当前节点的所有属性
		para[1] 等效于 para[position()=1]
		选择当前节点下的第1个节点名称为para的元素
		para[last()] 等效于 para[position()=last()]
		选择当前节点下的最后一个节点名称为para的元素
		/doc/chapter[5]/section[2]
		选择第5个名称为chapter的节点下的第2个名称为section的节点
		para[@type="warning"]
		选择当前节点下含有属性type的内容为warning的节点，并且节点名称为para
		para[@type="warning"][5]
		选择当前节点下含有属性type的内容为warning的节点，并且是第5个名称为para的节点
		chapter[title]
		选择当前节点下含有title节点且名称为chapter的所有的节点
		employee[@secretary and @assistant]
		选择当前节点下含有secretary属性和assistant属性且名称为employee的所有节点

		说明如下：
		/EXAMPLE/chapter/image[1]/attribute::*
		/EXAMPLE/chapter/image[1]/@*
		返回所有image[1]节点中属性:
		{"href","linus.gif"}
		{"width","230"}

		/EXAMPLE/chapter/image[1]/attribute::href
		/EXAMPLE/chapter/image[1]/@href
		只返回image[1]节点中属性名称为href的属性内容:
		{"href","linus.gif"}

		/child::EXAMPLE/child::chapter[1]/child::title[2]/child::text()
		/EXAMPLE/chapter[1]/title[2]/text()
		返回title[2]的文本节点:
		{"text","The Linux adventure2"}

		/child::EXAMPLE/child::chapter[1]/child::title
		/EXAMPLE/chapter[1]/title
		返回/EXAMPLE/chapter下所有名称为title的节点:
		{"title","The Linux adventure1"}
		{"title","The Linux adventure2"}

		/EXAMPLE/chapter/image[2]/child::comment()
		/EXAMPLE/chapter/image[2]/comment()
		返回/EXAMPLE/chapter/image[2]下所有的注释节点:
		{"comment","comment1 fffffffffffffffff"}
		{"comment","comment2 asadfdfdfdf"}

		/EXAMPLE/indb/dbname
		返回内容:
		{"dbname","gprs"}

		/EXAMPLE/indb/dbpassword
		返回内容:
		{"dbpassword","gprs123"}
		*  @endcode

		*  @par	        xml实例
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
		*  @attention   注意
		*  @bug	    问题
		*  @warning     警告
		*  @note	无
		*/
	class xml{
	public:
		/**
			*  @date        2016/06/14 13:28
			*  @brief       构造函数
			*/
		xml();
		/**
			*  @date        2016/06/14 13:28
			*  @brief       析构函数
			*/
		virtual ~xml();
	public:
		/**
		*  @date        2016/06/14 13:47
		*  @brief       打开并解析xml文档
		*  @param[in]   fileName[string]解析xml文档路径
		*  @param[int]	blank[int] 模式
		- 1:保留空格;
		- 0:去掉空格
		*  @return		返回结果
		- true:打开成功;
		- false:打开失败;
		*/
		bool openXPath(const std::string& fileName, int blank = 1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       打开并解析xml文档
		*  @param[in]   fileName[char*]解析xml文档路径
		*  @param[int]	blank[int]
		- 1:保留空格;
		- 0:去掉空格
		*  @return		返回结果
		- true:打开成功;
		- false:打开失败;
		*/
		bool openXPath(const char* fileName, int blank = 1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       打开并解析缓冲中的xml文档
		*  @param[in]   buffer[char*]内存是buffer
		*  @param[in]	size[int]buffer大小
		*  @param[int]	blank[int]
		- 1:保留空格;
		- 0:去掉空格
		*  @return		返回结果
		- true:打开成功;
		- false:打开失败;
		*/
		bool openBufferXPath(const char* buffer, int size = -1, int blank = 1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       关闭并释放xml文档
		*/
		void closeXPath();
		/**
		*  @date        2016/06/14 13:47
		*  @brief       设置XPATH
		*  @param[in]   xpath[char*]XPATH的内容
		*  @return		返回结果
		- true:设置成功;
		- false:设置失败;
		*/
		bool setXPath(const char* xpath);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       返回当前XPATH所查询的结果集
		*  @param[out]  resultSet[multimap<string, string>]XPATH所查询的结果集
		- 第一个string为节点名称,属性名称,text,comment中的一种
		- 第二个string为节点名称对应的文本节点内容,属性名对应的属性内容,注释内容中的一种
		*  @return		返回结果
		- true:成功;
		- false:失败;
		*/
		bool getXPathResultSet(std::multimap<std::string, std::string>& resultSet);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       返回当前XPATH所查询的结果集
		*  @param[in]	xpath[char*]XPATH的内容
		*  @param[out]  resultSet[multimap<string, string>]XPATH所查询的结果集
		- 第一个string为节点名称,属性名称,text,comment中的一种
		- 第二个string为节点名称对应的文本节点内容,属性名对应的属性内容,注释内容中的一种
		*  @return		返回结果
		- true:成功;
		- false:失败;
		*/
		bool getXPathResultSet(const char* xpath, std::multimap<std::string, std::string>& resultSet);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       读取指定的实体相关属性
		*  @param[in]	entName[string]要查询的实体名
		*  @param[out]  props[map<string, string>]entName对应的实体属性,包括：
		- ETYPE:  实体的类型
		- ID:     PUBLIC的外部标识
		- SYSTEM: PUBLIC,SYSTEM实体的url路径
		- ORIG:   实体引用没有被替换的内容
		- CONTENT:没有解析时的内容或数据
		*  @return		返回结果
		- true:成功;
		- false:失败;
		*/
		bool getEntityValue(const std::string& entName, std::map<std::string, std::string>& props);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       在当前XPATH下面插入一个子节点.
		- 若该XPATH下有多个相同的节点名称,并且没有指定位置,那么将默认插入第一个位置的下面,并且子节点在所有子节点的最后面,否则就插入指定的位置下面
		@code
		当前的XPATH是"/EXAMPLE/head"
		insertNodeByXPath("subhead","hello");
		<?xml version="1.0" ><EXAMPLE><head></head></EXAMPLE>
		结果就是:
		<?xml version="1.0" ><EXAMPLE><head><subhead>hello</subhead></head></EXAMPLE>
		@endcode
		- 若该节点名称为空则插入一个文本节点(即nodeValue),若已经存在文本节点,则会追加到第一个文本节点上,然后返回true;
		- 若该节点名称为"<![CDATA[]]>"则插入一个CDATA段的字符节点(即nodeValue),若已经存在CDATA段,则会追加到第一个文本节点上,然后返回true;
		*  @param[in]	nodeName[char*]节点名称
		*  @param[in]	nodeValue[char*]节点的值
		*  @param[in]	length[int]nodeValue的长度
		*  @return		若该节点名称非空则插入一个节点(即nodeName),若已经存在该节点,则返回false,否则返回true;
		*/
		bool insertNodeByXPath(const char* nodeName, const char* nodeValue, int length = -1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       在指定的XPATH下面插入一个子节点.
		- 若该XPATH下有多个相同的节点名称,并且没有指定位置,那么将默认插入第一个位置的下面,并且子节点在所有子节点的最后面,否则就插入指定的位置下面
		@code
		insertNodeByXPath("/EXAMPLE/head","subhead","hello")
		<?xml version="1.0" ><EXAMPLE><head></head></EXAMPLE>
		结果就是:
		<?xml version="1.0" ><EXAMPLE><head><subhead>hello</subhead></head></EXAMPLE>
		@endcode
		- 若该节点名称为空则插入一个文本节点(即nodeValue),若已经存在文本节点,则会追加到第一个文本节点上,然后返回true;
		- 若该节点名称为"<![CDATA[]]>"则插入一个CDATA段的字符节点(即nodeValue),若已经存在CDATA段,则会追加到第一个文本节点上,然后返回true;
		*  @param[in]	xpath[char*]XPATH的内容
		*  @param[in]	nodeName[char*]节点名称
		*  @param[in]	nodeValue[char*]节点的值
		*  @param[in]   length[int]nodeValue的长度
		*  @return		若该节点名称非空则插入一个节点(即nodeName),若已经存在该节点,则返回false,否则返回true;
		*/
		bool insertNodeByXPath(const char* xpath, const char* nodeName, const char* nodeValue, int length = -1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       在当前XPATH下面插入一个节点的属性.
		@code
		当前的XPATH是"/EXAMPLE/head"
		insertPropertyByXPath("subhead","hello");
		<?xml version="1.0" ><EXAMPLE><head></head></EXAMPLE>
		结果就是:
		<?xml version="1.0" ><EXAMPLE><head subhead="hello"></head></EXAMPLE>
		@endcode
		*  @param[in]	propName[char*]属性名称
		*  @param[in]	propValue[char*]属性的值
		*  @param[in]   length[int]propValue的长度
		*  @return		若该属性名称已经存在,则返回false,否则处理成功返回true;
		*/
		bool insertPropertyByXPath(const char* propName, const char* propValue, int length = -1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       在指定的XPATH下面插入一个节点的属性.
		@code
		insertPropertyByXPath("/EXAMPLE/head","subhead","hello");
		<?xml version="1.0" ><EXAMPLE><head></head></EXAMPLE>
		结果就是:
		<?xml version="1.0" ><EXAMPLE><head subhead="hello"></head></EXAMPLE>
		@endcode
		*  @param[in]	xpath[char*]XPATH的内容
		*  @param[in]	propName[char*]属性名称
		*  @param[in]	propValue[char*]属性值
		*  @param[in]   length[int]propValue的长度
		*  @return		若该属性名称已经存在,则返回false,否则处理成功返回true;
		*/
		bool insertPropertyByXPath(const char* xpath, const char* propName, const char* propValue, int length = -1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       在当前XPATH下面更新一个节点.
		- 若该XPATH下有多个相同的节点名称,并且没有指定位置,那么将默认更新第一个位置的节点,否则就插入指定的节点
		@code
		当前的XPATH是"/EXAMPLE/head"
		updateNodeByXPath("head","hello");
		<?xml version="1.0" ><EXAMPLE><head>hhhhh</head></EXAMPLE>
		结果就是:
		<?xml version="1.0" ><EXAMPLE><head>hello</head></EXAMPLE>
		@endcode
		*  @param[in]	nodeName[char*]节点名称.为空时保留原来的节点名称,否则使用nodeName覆盖旧名称
		*  @param[in]	nodeValue[char*]节点的值
		*  @param[in]   length[int]nodeValue的长度
		*  @return		- 更新节点成功返回true,否则返回false;
		- 若该节点名称不存在,则返回false;
		*/
		bool updateNodeByXPath(const char* nodeName, const char* nodeValue, int length = -1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       在指定的XPATH下面更新一个节点.
		- 若该XPATH下有多个相同的节点名称,并且没有指定位置,那么将默认更新第一个位置的节点,否则就插入指定的节点
		@code
		updateNodeByXPath("/EXAMPLE/head","head","hello");
		<?xml version="1.0" ><EXAMPLE><head>hhhhh</head></EXAMPLE>
		结果就是:
		<?xml version="1.0" ><EXAMPLE><head>hello</head></EXAMPLE>
		@endcode
		*  @param[in]	xpath[char*]XPATH的内容
		*  @param[in]	nodeName[char*]节点名称.为空时保留原来的节点名称,否则使用nodeName覆盖旧名称
		*  @param[in]	nodeValue[char*]节点的值.
		*  @param[in]   length[int]nodeValue的长度
		*  @return		- 更新节点成功返回true,否则返回false;
		*		        - 若该节点名称不存在,则返回false;
		*/
		bool updateNodeByXPath(const char* xpath, const char* nodeName, const char* nodeValue, int length = -1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       在当前XPATH下面更新一个节点的属性.
		@code
		当前的XPATH是"/EXAMPLE/head"
		updatePropertyByXPath("subhead","hello");
		<?xml version="1.0" ><EXAMPLE><head subhead="hhhhh"></head></EXAMPLE>
		结果就是:
		<?xml version="1.0" ><EXAMPLE><head subhead="hello"></head></EXAMPLE>
		@endcode
		*  @param[in]	propName[char*]属性名称
		*  @param[in]	propValue[char*]属性的值
		*  @param[in]   length[int]propValue的长度
		*  @return		更新成功返回true;否则返回false;若该属性名称不存在,则返回false;
		*/
		bool updatePropertyByXPath(const char* propName, const char* propValue, int length = -1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       在指定的XPATH下面更新一个节点的属性.
		@code
		updatePropertyByXPath("/EXAMPLE/head","subhead","hello");
		<?xml version="1.0" ><EXAMPLE><head subhead="hhhhh"></head></EXAMPLE>
		结果就是:
		<?xml version="1.0" ><EXAMPLE><head subhead="hello"></head></EXAMPLE>
		@endcode
		*  @param[in]	xpath[char*]XPATH的内容
		*  @param[in]	propName[char*]属性名称
		*  @param[in]	propValue[char*]属性的值
		*  @param[in]   length[int] propValue的长度
		*  @return		更新成功返回true;否则返回false;若该属性名称不存在,则返回false;
		*/
		bool updatePropertyByXPath(const char* xpath, const char* propName, const char* propValue, int length = -1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       在当前XPATH下面删除最后一个节点树.
		- 若该XPATH下有多个相同的节点名称,并且没有指定位置,那么将默认删除第一个位置的节点树,否则就插入指定的节点树
		@code
		当前的XPATH是"/EXAMPLE/head"
		eraseNodeByXPath();
		<?xml version="1.0" ><EXAMPLE><head></head></EXAMPLE>
		结果就是:
		<?xml version="1.0" ><EXAMPLE></EXAMPLE>
		@endcode
		*  @return		删除成功返回true,否则返回false;若该节点树不存在,返回false!
		*/
		bool eraseNodeByXPath();
		/**
		*  @date        2016/06/14 13:47
		*  @brief       在指定的XPATH下面删除最后一个节点树.
		- 若该XPATH下有多个相同的节点名称,并且没有指定位置,那么将默认删除第一个位置的节点树,否则就插入指定的节点树
		@code
		eraseNodeByXPath("/EXAMPLE/head");
		<?xml version="1.0" ><EXAMPLE><head></head></EXAMPLE>
		结果就是:
		<?xml version="1.0" ><EXAMPLE></EXAMPLE>
		@endcode
		*  @param[in]	xpath[char*]XPATH的内容
		*  @return		删除成功返回true,否则返回false;若该节点树不存在,返回false!
		*/
		bool eraseNodeByXPath(const char* xpath);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       在当前XPATH下面删除一个节点的属性
		@code
		当前的XPATH是"/EXAMPLE/head"
		erasePropertyByXPath("subhead");
		<?xml version="1.0" ><EXAMPLE><head subhead="head"></head></EXAMPLE>
		结果就是:
		<?xml version="1.0" ><EXAMPLE><head></head></EXAMPLE>
		@endcode
		*  @param[in]	propName[char*]属性名称
		*  @return		删除成功返回true,否则返回false;若该属性不存在,返回false!
		*/
		bool erasePropertyByXPath(const char* propName);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       在指定的XPATH下面删除一个节点的属性.
		@code
		erasePropertyByXPath("/EXAMPLE/head","subhead");
		<?xml version="1.0" ><EXAMPLE><head subhead="head"></head></EXAMPLE>
		结果就是:
		<?xml version="1.0" ><EXAMPLE><head></head></EXAMPLE>
		@endcode
		*  @param[in]	xpath[char*]XPATH的内容
		*  @param[in]	propName[char*]属性名称
		*  @return		删除成功返回true,否则返回false;若该属性不存在,返回false!
		*/
		bool erasePropertyByXPath(const char* xpath, const char* propName);

		/**
		*  @date        2016/06/14 13:47
		*  @brief       保存xml数据到文件中
		*  @param[in]	fname[char*]文件名或url,为空时将保存到原来的文件中
		*  @param[in]	encoding[char*]使用的字符编码,默认为空
		*  @param[in]	format[int]0:不进行格式输出;1:格式输出,默认为1
		*  @return		成功返回true,否则false;
		*/
		bool saveXmlToFileXPath(const char* fname = "", const char* encoding = "", int format = 1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       保存xml数据输出到buff内存中
		*  @param[in]	buffStr[string]输出的缓冲
		*  @param[in]	encoding[char*]使用的字符编码,默认为空
		*  @param[in]	format[int]0:不进行格式输出;1:格式输出,默认为1
		*  @return		成功返回true,否则false;
		*/
		bool saveXmlToBufferXPath(std::string& buffStr, const char* encoding = "", int format = 1);
		/**
		*  @date        2016/06/14 13:47
		*  @brief       将xml文件导出到指定的文件流
		*  @param[in]	f[FILE*]文件指针,可以是stdin,stdout,stderr
		*  @return		成功返回true,否则false;
		*/
		bool dumpXPath(FILE* f = stdout);
		/**
		* 设置在读取数据时仅仅读取实体名字的标记.
		*@param b true:仅仅读取实体名字;false:读取实体扩展后的内容
		*@return 成功返回true,否则false;
		*/
		//void setOnlyGetEntityNameFlag(bool b);
		/**
			*  @date        2016/06/15 13:28
			*  @brief       创建xml
			*  @param[in]   filname[string]创建xml的名字,如果这里为空，那么在saveToFile里面一定要写名字
			*  @param[in]   encod[string]创建xml的编码格式，默认utf-8
			*  @return      成功返回true，否则为false
			*  @pre         创建一个xml DOC的一个指针
			*  @remarks     评论
			*  @see         gpl::xml::saveToFile
			*  @test        测试
			*/
		bool createXml(std::string encod = "UTF-8", std::string filename = "");
		/**
			*  @date        2016/06/15 13:41
			*  @brief       添加一个节点
			*  @param[in]   node[string]节点名字
			*  @return      成功返回true，否则为false
			*  @pre         添加一个以node为名字的节点
			*  @remarks     评论
			*  @see         参考内容
			*  @test        测试
			*/
		bool addANode(std::string node);
		/**
			*  @date        2016/06/15 13:43
			*  @brief       为节点添加一个子节点
			*  @param[in]   node[string]一个以存在的节点名字，如果这个节点不存在返回false
			*  @param[in]   item[string]添加的子节点，如果这个子节点存在返回false
			*  @param[in]   content[string]子节点内存
			*  @return      成功返回true，否则为false
			*  @pre         段落
			*  @remarks     评论
			*  @see         参考内容
			*  @test        测试
			*/
		bool addAItem(std::string node, std::string item, std::string content);
		/**
			*  @date        2016/06/15 14:24
			*  @brief       保存xml到文件
			*  @param[in]   encod[string]保存xml的编码
			*  @param[in]   filename[string]保存xml的文件名字，在createXml中声明了这里可以为空
			*  @param[in]   blankpad[bool]是否进行格式化输出
			*  @return      成功返回true，否则为false
			*  @pre         段落
			*  @remarks     评论
			*  @see         参考内容
			*  @test        测试
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