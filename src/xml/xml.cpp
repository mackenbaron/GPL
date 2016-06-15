#include "xml.h"

#ifndef   XML_CDATA   
#define XML_CDATA   "<![CDATA[]]>\0"
#endif

#ifdef __cplusplus
extern "C"
{
#endif
#include <libxml/xpath.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/debugXML.h>
#include <libxml/xmlmemory.h>
#include <libxml/parserInternals.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlerror.h>
#include <libxml/globals.h>
#ifdef __cplusplus
}
#endif

class gpl::xml::LibXml
{
public:
	LibXml();
	~LibXml();
	/**
	*去除字符串两边的空格,回车换行,TAB
	*@param str 需要处理的字符串
	*@return 处理后的字符串
	*/
	std::string allTrim(std::string &str);
	/**
	*将xmlChar* 转化成 string,并去除字符串两边的空格,回车换行,TAB
	*@param xmlchar xmlChar*类型的字符串
	*@param isClear 是否将xmlchar的缓冲清除
	*@return 转化后的字符串
	*/
	std::string getStringByXmlCharPtr(xmlChar* xmlchar, int isClear = 0);
	/**
	*dump一个节点到结果集
	*@param nodePtr 当前的节点指针
	*@param resultSet 返回的结果集,参见 XmlApi::getXPathResultSet(multimap<string,string>& resultSet) 方法的说明
	*@return 成功返回true,否则返回false;
	*/
	bool   getDumpNode(xmlNodePtr nodePtr, std::multimap<std::string, std::string>&resultSet);
	/**
	*dump一个属性到结果集
	*@param attrPtr 当前的属性指针
	*@param resultSet 返回的结果集,参见XmlApi::getXPathResultSet(multimap<string,string>& resultSet)方法的说明
	*@return 成功返回true,否则返回false;
	*/
	bool   getDumpAttribute(xmlAttrPtr attrPtr, std::multimap<std::string, std::string>&resultSet);

public:
	xmlDocPtr doc;

	xmlXPathContextPtr context;
	xmlXPathObjectPtr resource;
	bool isOnlyEntityName;
};

gpl::xml::LibXml::LibXml()
{
	doc = 0;
	context = 0;
	resource = 0;
	dbFileName.clear();
	pxmlDoc = NULL;
	tab_ipc = NULL;
	item_ipc = NULL;
}

gpl::xml::LibXml::~LibXml()
{
	if (pxmlDoc)
		xmlFreeDoc(pxmlDoc);
}
/**
*去除字符串两边的空格,回车换行,TAB
*@param str 需要处理的字符串
*@return 处理后的字符串
*/
std::string gpl::xml::LibXml::allTrim(std::string &str)
{
	std::string sTmp = str;
	int i;

	if (sTmp.empty() == true)
		return sTmp;

	for (i = 0; i < (int)sTmp.length(); i++)
	{
		if (sTmp[i] == ' ' || sTmp[i] == '\n' || sTmp[i] == '\t' || sTmp[i] == '\r')
			sTmp.erase(i, 1);
		else
			break;
	}
	for (i = sTmp.length() - 1; i >= 0; i--)
	{
		if (sTmp[i] == ' ' || sTmp[i] == '\n' || sTmp[i] == '\t' || sTmp[i] == '\r')
			sTmp.erase(i, 1);
		else
			break;
	}

	return sTmp;
}
/**
*将xmlChar* 转化成 string,并去除字符串两边的空格,回车换行,TAB
*@param xmlchar xmlChar*类型的字符串
*@return 转化后的字符串
*/
std::string gpl::xml::LibXml::getStringByXmlCharPtr(xmlChar* xmlchar, int isClear /*= 0*/)
{
	if (xmlchar == (xmlChar*)NULL)
		return std::string("");

	xmlChar* xmlname;
	std::string str;
	xmlname = (xmlChar*)xmlStrdup(xmlchar);
	str = (char*)xmlname;
	str = allTrim(str);
	xmlFree(xmlname);
	if (isClear)
	{
		xmlFree(xmlchar);
		xmlchar = NULL;
	}
	return str;
}
/**
*dump一个节点到结果集
*@param nodePtr 当前的节点指针
*@param resultSet 返回的结果集,参见XmlApi::getXPathResultSet(multimap<string,string>& resultSet)方法的说明
*@return 成功返回true,否则返回false;
*/
bool gpl::xml::LibXml::getDumpNode(xmlNodePtr nodePtr, std::multimap<std::string, std::string>&resultSet)
{
	if (nodePtr == NULL)
		return false;

	std::string name, value;
	switch (nodePtr->type)
	{
	case XML_ELEMENT_NODE:
		name = getStringByXmlCharPtr((xmlChar *)nodePtr->name);
		value = getStringByXmlCharPtr(xmlNodeListGetString(doc, nodePtr->xmlChildrenNode, 1), 1);
		resultSet.insert(std::multimap<std::string, std::string>::value_type(name, value));
		break;
	case XML_TEXT_NODE:
	case XML_CDATA_SECTION_NODE:
		name = getStringByXmlCharPtr((xmlChar *)nodePtr->name);
		value = "";
		if (nodePtr->content != NULL)
		{
			if (isOnlyEntityName)
				value = getStringByXmlCharPtr(nodePtr->content);
			else
			{
				xmlChar *buffer;
				buffer = xmlEncodeEntitiesReentrant(doc, nodePtr->content);
				if (buffer != NULL)
				{
					value = getStringByXmlCharPtr(buffer, 1);
				}
			}
		}
		resultSet.insert(std::multimap<std::string, std::string>::value_type(name, value));
		break;
	case XML_PI_NODE:
	case XML_COMMENT_NODE:
		name = getStringByXmlCharPtr((xmlChar *)nodePtr->name);
		if (nodePtr->content != NULL)
		{
			value = getStringByXmlCharPtr(nodePtr->content);
		}
		resultSet.insert(std::multimap<std::string, std::string>::value_type(name, value));
		break;
	case XML_DOCUMENT_NODE:
	case XML_HTML_DOCUMENT_NODE:
		resultSet.insert(std::multimap<std::string, std::string>::value_type(std::string("document or html_document"), std::string("/")));
		break;
	case XML_ATTRIBUTE_NODE:
		return getDumpAttribute(reinterpret_cast<xmlAttrPtr>(nodePtr), resultSet);
	case XML_ENTITY_REF_NODE:
		name = getStringByXmlCharPtr((xmlChar *)nodePtr->name);
		value = "";
		if (nodePtr->content != NULL)
		{
			if (isOnlyEntityName)
			{
				//value = getStringByXmlCharPtr(nodePtr->content);
				xmlEntityPtr ent = xmlGetDocEntity(doc, nodePtr->name);
				if (ent != NULL)
				{
					xmlChar *buffer;

					/* an entity content can be any "well balanced chunk",
					* i.e. the result of the content [43] production:
					* http://www.w3.org/TR/REC-xml#NT-content.
					* So it can contain text, CDATA section or nested
					* entity reference nodes (among others).
					* -> we recursive  call xmlNodeListGetString()
					* which handles these types */
					buffer = xmlNodeListGetString(doc, ent->children, 1);
					if (buffer != NULL)
					{
						value = getStringByXmlCharPtr(buffer, 1);
					}
				}
				else
				{
					value = getStringByXmlCharPtr(nodePtr->content);
				}
				}
			else
			{
				value = "&" + getStringByXmlCharPtr((xmlChar*)nodePtr->name) + ";";
			}
			}
		resultSet.insert(std::multimap<std::string, std::string>::value_type(name, value));
		break;
	default:
		;
		}
	return true;
	}
/**
*dump一个属性到结果集
*@param attrPtr 当前的属性指针
*@param resultSet 返回的结果集,参见XmlApi::getXPathResultSet(multimap<string,string>& resultSet)方法的说明
*@return 成功返回true,否则返回false;
*/
bool gpl::xml::LibXml::getDumpAttribute(xmlAttrPtr attrPtr, std::multimap<std::string, std::string>&resultSet)
{
	if (attrPtr == NULL)
		return false;
	std::string name, value;
	xmlAttrPtr tmpAttrPtr = attrPtr;

	if (tmpAttrPtr != NULL)
	{
		name = getStringByXmlCharPtr((xmlChar *)tmpAttrPtr->name);
		if (tmpAttrPtr->children == NULL)
			value = "";
		else
			value = getStringByXmlCharPtr(xmlNodeListGetString(doc, tmpAttrPtr->children, 1), 1);
		resultSet.insert(std::multimap<std::string, std::string>::value_type(name, value));
	}
	return true;
}

#ifndef NULL
#define NULL 0
#endif
///构造函数
gpl::xml::xml()
{
	m_xml = new LibXml;
	m_fileName = "";
}
///析构函数
gpl::xml::~xml()
{
	closeXPath();
	if (m_xml != 0)
	{
		delete m_xml;
		m_xml = 0;
	}
}
/**
*打开并解析xml文档
*@param fileName
*@return true:打开成功;false:打开失败;
*/
bool gpl::xml::openXPath(const std::string& fileName, int blank /*= 1*/)
{
	return openXPath(fileName.c_str(), blank);
}

bool gpl::xml::openXPath(const char* fileName, int blank /*= 1*/)
{
	if (m_xml->doc != NULL)
		closeXPath();
	xmlLoadExtDtdDefaultValue |= XML_DETECT_IDS;
	xmlLoadExtDtdDefaultValue |= XML_COMPLETE_ATTRS;
	xmlSubstituteEntitiesDefaultValue = 1;
	xmlKeepBlanksDefault(blank);
	if (xmlAddEncodingAlias("ISO-8859-1", "GBK") < 0 ||
		xmlAddEncodingAlias("ISO-8859-1", "GB2312") < 0)
		return false;
	m_xml->doc = xmlParseFile(fileName);
	if (m_xml->doc == NULL)
		return false;

	m_xml->context = xmlXPathNewContext(m_xml->doc);
	m_xml->context->node = xmlDocGetRootElement(m_xml->doc);
	if (m_xml->context->node == NULL)
	{
		xmlFreeDoc(m_xml->doc);
		return false;
	}
	m_xml->resource = NULL;
	m_fileName = fileName;
	m_xml->isOnlyEntityName = false;

	return true;
}

bool gpl::xml::openBufferXPath(const char* buffer, int size /*= -1*/, int blank /*= 1*/)
{
	int len = strlen(buffer);
	if (size == 0 || len < size)
		return false;
	if (size == -1)
	{
		size = len;
	}
	///////////////////////////////////////////////////////  
	if (m_xml->doc != NULL)
		closeXPath();
	xmlLoadExtDtdDefaultValue |= XML_DETECT_IDS;
	xmlLoadExtDtdDefaultValue |= XML_COMPLETE_ATTRS;
	xmlSubstituteEntitiesDefaultValue = 1;
	if (xmlAddEncodingAlias("ISO-8859-2", "GBK") < 0 ||
		xmlAddEncodingAlias("ISO-8859-2", "GB2312") < 0)
		return false;
	xmlKeepBlanksDefault(blank);
	m_xml->doc = xmlParseMemory(buffer, size);
	if (m_xml->doc == NULL)
		return false;

	m_xml->context = xmlXPathNewContext(m_xml->doc);
	m_xml->context->node = xmlDocGetRootElement(m_xml->doc);
	if (m_xml->context->node == NULL)
	{
		xmlFreeDoc(m_xml->doc);
		return false;
	}
	m_xml->resource = NULL;
	m_fileName = "";
	m_xml->isOnlyEntityName = false;

	///////////////////////////////////////////////////////  
	return true;
}
/**
*关闭并释放xml文档
*/
void gpl::xml::closeXPath()
{
	if (m_xml->resource != NULL)
	{
		xmlXPathFreeObject(m_xml->resource);
		m_xml->resource = NULL;
	}
	if (m_xml->context != NULL)
	{
		xmlXPathFreeContext(m_xml->context);
		m_xml->context = NULL;
	}
	xmlCleanupEncodingAliases();
	if (m_xml->doc != NULL)
		xmlFreeDoc(m_xml->doc);
	xmlCleanupParser();
	m_xml->doc = 0;
}
/**
*设置XPATH
*@param xpath XPATH的内容
*@return 设置成功返回true,否则返回false;
*/
bool gpl::xml::setXPath(const char* xpath)
{
	xmlXPathCompExprPtr comp;

	comp = xmlXPathCompile(BAD_CAST xpath);
	if (comp == NULL)
		return false;

	if (m_xml->resource != NULL)
	{
		xmlXPathFreeObject(m_xml->resource);
		m_xml->resource = NULL;
	}

	//XPATH解析树输出
	//xmlXPathDebugDumpCompExpr(stdout, comp, 0);
	m_xml->resource = xmlXPathCompiledEval(comp, m_xml->context);

	//XPATH返回结果输出
	//xmlXPathDebugDumpObject(stdout, m_xml->resource, 0);
	xmlXPathFreeCompExpr(comp);
	if (m_xml->resource == NULL)
		return false;

	//该XPATH下无节点数则返回失败
	if (m_xml->resource->nodesetval == NULL || m_xml->resource->nodesetval->nodeNr == 0)
		return false;

	return true;
}

bool gpl::xml::getXPathResultSet(std::multimap<std::string, std::string>& resultSet)
{
	resultSet.clear();
	//added by shandy 20041208
	if (m_xml->resource == NULL)
		return true;

	std::vector<std::string> strVector;
	std::string str, name;
	int i;
	xmlNodeSetPtr tmpPtr = 0;

	//cout<<"resource->type:"<<m_xml->resource->type<<endl;
	switch (m_xml->resource->type)
	{
	case XPATH_UNDEFINED://Object is uninitialized
		return false;
		break;
	case XPATH_NODESET://Object is a Node Set
		tmpPtr = m_xml->resource->nodesetval;
		if (tmpPtr == NULL)
			break;
		for (i = 0; i < tmpPtr->nodeNr; i++)
			m_xml->getDumpNode(tmpPtr->nodeTab[i], resultSet);
		break;
	case XPATH_XSLT_TREE://Object is an XSLT value tree
		return false;
		break;
	case XPATH_BOOLEAN://Object is a Boolean
		str = m_xml->getStringByXmlCharPtr(xmlXPathCastBooleanToString(m_xml->resource->boolval), 1);
		resultSet.insert(std::multimap<std::string, std::string>::value_type(std::string("boolean"), str));
		break;
	case XPATH_NUMBER://Object is a number
		str = m_xml->getStringByXmlCharPtr(xmlXPathCastNumberToString(m_xml->resource->floatval), 1);
		resultSet.insert(std::multimap<std::string, std::string>::value_type(std::string("number"), str));
		break;
	case XPATH_STRING://Object is a string
		if (m_xml->resource->stringval != NULL)
		{
			std::string str = m_xml->getStringByXmlCharPtr(m_xml->resource->stringval);
			resultSet.insert(std::multimap<std::string, std::string>::value_type(std::string("string"), str));
		}
		break;
	case XPATH_POINT://Object is a point
		//fprintf(output, " : index %d in node", m_xml->resource->index);
		m_xml->getDumpNode((xmlNodePtr)m_xml->resource->user, resultSet);
		break;
	case XPATH_RANGE:
		if ((m_xml->resource->user2 == NULL) ||
			((m_xml->resource->user2 == m_xml->resource->user) && (m_xml->resource->index == m_xml->resource->index2)))
		{
			//Object is a collapsed range 
			//if (m_xml->resource->index >= 0)
			//    fprintf(output, "index %d in ", m_xml->resource->index);
			//fprintf(output, "node\n");
			m_xml->getDumpNode((xmlNodePtr)m_xml->resource->user, resultSet);
		}
		else
		{
			//Object is a range from 
			//if (m_xml->resource->index >= 0)
			//    fprintf(output, "index %d in ", m_xml->resource->index);
			m_xml->getDumpNode((xmlNodePtr)m_xml->resource->user, resultSet);
			// to 
			//if (m_xml->resource->index2 >= 0)
			//    fprintf(output, "index %d in ", m_xml->resource->index2);
			m_xml->getDumpNode((xmlNodePtr)m_xml->resource->user2, resultSet);
		}
		break;
	case XPATH_LOCATIONSET://Object is a Location Set
		return false;
		break;
	case XPATH_USERS://Object is user defined
		return false;
		break;
	}
	return true;
}

bool gpl::xml::getXPathResultSet(const char* xpath, std::multimap<std::string, std::string>& resultSet)
{
	if (setXPath(xpath) == false)
		return false;
	return getXPathResultSet(resultSet);
}

bool gpl::xml::getEntityValue(const std::string& entName, std::map<std::string, std::string>& props)
{
	xmlEntityPtr ent;
	if (m_xml->doc == 0)
		return false;

	std::string str;

	//debug output
	//xmlDebugDumpEntities(stdout,m_xml->doc);
	//end debug
	ent = xmlGetDocEntity(m_xml->doc, (const xmlChar*)entName.c_str());
	if (ent != NULL)
	{
		props.clear();
#ifdef WIN32
		this->ltoa((long)ent->etype, str);
#else
		char buff[100];
		str = ltoa((long)ent->etype, buff, 100);
#endif
		props.insert(std::map<std::string, std::string>::value_type(std::string("ETYPE"), str));

		str = m_xml->getStringByXmlCharPtr((xmlChar*)ent->ExternalID);
		props.insert(std::map<std::string, std::string>::value_type(std::string("ID"), str));

		str = m_xml->getStringByXmlCharPtr((xmlChar*)ent->SystemID);
		props.insert(std::map<std::string, std::string>::value_type(std::string("SYSTEM"), str));

		str = m_xml->getStringByXmlCharPtr((xmlChar*)ent->orig);
		props.insert(std::map<std::string, std::string>::value_type(std::string("ORIG"), str));

		str = m_xml->getStringByXmlCharPtr((xmlChar*)ent->content);
		props.insert(std::map<std::string, std::string>::value_type(std::string("CONTENT"), str));
	}
	else
		return false;
	return true;
}

bool gpl::xml::insertNodeByXPath(const char* nodeName, const char* nodeValue, int length /*= -1*/)
{
	if (m_xml->resource == NULL)
		return false;
	int len = strlen(nodeValue);
	if (length == 0 || len < length)
		return false;
	if (length == -1)
	{
		length = len;
	}
	//cout<<"resource->type:"<<m_xml->resource->type<<endl;
	switch (m_xml->resource->type)
	{
	case XPATH_NODESET://Object is a Node Set
		if (m_xml->resource->nodesetval == NULL)
			return false;
		xmlNodePtr cur, newNode;
		//取得第一个节点
		if ((cur = (*(m_xml->resource->nodesetval->nodeTab))) == NULL)
			return false;
		if (strlen(nodeName) == 0)
		{
			if (cur->children == NULL)
			{
				cur->children = xmlNewText((const xmlChar*)nodeValue);
				cur->last = cur->children;
				if (cur->last == NULL)
					return false;
			}
			else
				if (xmlTextConcat(cur->children, (const xmlChar *)nodeValue, length) < 0)
					return false;
		}
		else
		{
			if (strcmp(nodeName, XML_CDATA) == 0)
			{
				if ((newNode = xmlNewCDataBlock(m_xml->doc, (const xmlChar*)nodeValue, length)) == NULL)
					return false;
			}
			else
			{
				xmlNsPtr* ns = xmlGetNsList(m_xml->doc, cur);
				if ((newNode = xmlNewNode((ns == NULL ? NULL : (*ns)), (const xmlChar *)nodeName)) == NULL)
					return false;
				xmlNodeSetContent(newNode, (const xmlChar*)nodeValue);

			}
			//从最后的字节点位置进行追加
			if ((xmlAddChild(cur, newNode)) == NULL)
				return false;
		}
		break;
	case XPATH_XSLT_TREE://Object is an XSLT value tree
	case XPATH_BOOLEAN://Object is a Boolean
	case XPATH_NUMBER://Object is a number
	case XPATH_STRING://Object is a string
	case XPATH_POINT://Object is a point
	case XPATH_RANGE://是一个范围
	case XPATH_LOCATIONSET://Object is a Location Set
	case XPATH_USERS://Object is user defined
	case XPATH_UNDEFINED://Object is uninitialized
		return false;
		break;
	}
	return true;
}

bool gpl::xml::insertNodeByXPath(const char* xpath, const char* nodeName, const char* nodeValue, int length /*= -1*/)
{
	if (setXPath(xpath) == false)
		return false;
	return insertNodeByXPath(nodeName, nodeValue, length);
}

bool gpl::xml::insertPropertyByXPath(const char* propName, const char* propValue, int length /*= -1*/)
{
	if (m_xml->resource == NULL)
		return false;

	//cout<<"resource->type:"<<m_xml->resource->type<<endl;
	switch (m_xml->resource->type)
	{
	case XPATH_NODESET://Object is a Node Set
		if (m_xml->resource->nodesetval == NULL)
			return false;
		xmlNodePtr cur;
		//取得第一个节点
		if ((cur = (*(m_xml->resource->nodesetval->nodeTab))) == NULL)
			return false;
		if (strlen(propName) == 0)//属性名称不能为空
			return false;
		//已经存在的，返回失败
		if (xmlHasProp(cur, (const xmlChar*)propName) != NULL)
			return false;
		if (xmlSetProp(cur, (const xmlChar *)propName, (const xmlChar *)propValue) == NULL)
			return false;
		break;
	case XPATH_XSLT_TREE://Object is an XSLT value tree
	case XPATH_BOOLEAN://Object is a Boolean
	case XPATH_NUMBER://Object is a number
	case XPATH_STRING://Object is a string
	case XPATH_POINT://Object is a point
	case XPATH_RANGE://是一个范围
	case XPATH_LOCATIONSET://Object is a Location Set
	case XPATH_USERS://Object is user defined
	case XPATH_UNDEFINED://Object is uninitialized
		return false;
		break;
	}
	return true;
}

bool gpl::xml::insertPropertyByXPath(const char* xpath, const char* propName, const char* propValue, int length /*= -1*/)
{
	if (setXPath(xpath) == false)
		return false;
	return insertPropertyByXPath(propName, propValue, length);
}

bool gpl::xml::updateNodeByXPath(const char* nodeName, const char* nodeValue, int length /*= -1*/)
{
	if (m_xml->resource == NULL)
		return false;

	//cout<<"resource->type:"<<m_xml->resource->type<<endl;
	switch (m_xml->resource->type)
	{
	case XPATH_NODESET://Object is a Node Set
		if (m_xml->resource->nodesetval == NULL)
			return false;
		xmlNodePtr cur;
		//取得第一个节点
		if ((cur = (*(m_xml->resource->nodesetval->nodeTab))) == NULL)
			return false;
		//更新节点的内容
		//第一个节点为NULL,或非文本节点,则添加一个文本节点
		if (cur->type == XML_DOCUMENT_FRAG_NODE ||
			cur->type == XML_ELEMENT_NODE)
		{
			//更新节点名称
			if (strlen(nodeName) > 0)
			{
				xmlNodeSetName(cur, (const xmlChar*)nodeName);
			}
			if (cur->children == NULL)//为空时插入一个节点
			{
				insertNodeByXPath("", nodeValue);
			}
			else
			{
				xmlFree(cur->children->content);
				cur->children->content = xmlStrdup((const xmlChar*)nodeValue);
			}
		}
		//第一个节点为文本节点,则覆盖内容
		else if (cur->type == XML_TEXT_NODE ||
			cur->type == XML_CDATA_SECTION_NODE ||
			cur->type == XML_ENTITY_REF_NODE ||
			cur->type == XML_ENTITY_NODE ||
			cur->type == XML_PI_NODE ||
			cur->type == XML_COMMENT_NODE ||
			cur->type == XML_NOTATION_NODE)
		{
			xmlFree(cur->content);
			cur->content = xmlStrdup((const xmlChar*)nodeValue);
		}
		else
			return false;
		break;
	case XPATH_XSLT_TREE://Object is an XSLT value tree
	case XPATH_BOOLEAN://Object is a Boolean
	case XPATH_NUMBER://Object is a number
	case XPATH_STRING://Object is a string
	case XPATH_POINT://Object is a point
	case XPATH_RANGE://是一个范围
	case XPATH_LOCATIONSET://Object is a Location Set
	case XPATH_USERS://Object is user defined
	case XPATH_UNDEFINED://Object is uninitialized
		return false;
		break;
	}
	return true;
}

bool gpl::xml::updateNodeByXPath(const char* xpath, const char* nodeName, const char* nodeValue, int length /*= -1*/)
{
	if (setXPath(xpath) == false)
		return false;
	return updateNodeByXPath(nodeName, nodeValue, length);
}

bool gpl::xml::updatePropertyByXPath(const char* propName, const char* propValue, int length /*= -1*/)
{
	if (m_xml->resource == NULL)
		return false;
	if (strlen(propName) == 0)
		return false;
	//cout<<"resource->type:"<<m_xml->resource->type<<endl;
	switch (m_xml->resource->type)
	{
	case XPATH_NODESET://Object is a Node Set
		if (m_xml->resource->nodesetval == NULL)
			return false;
		xmlNodePtr cur;
		//取得第一个节点
		if ((cur = (*(m_xml->resource->nodesetval->nodeTab))) == NULL)
			return false;
		//更新节点的属性内容
		if (xmlHasProp(cur, (const xmlChar*)propName) == NULL)
			return false;
		if (xmlSetProp(cur, (const xmlChar*)propName, (const xmlChar*)propValue) == NULL)
			return false;
		break;
	case XPATH_XSLT_TREE://Object is an XSLT value tree
	case XPATH_BOOLEAN://Object is a Boolean
	case XPATH_NUMBER://Object is a number
	case XPATH_STRING://Object is a string
	case XPATH_POINT://Object is a point
	case XPATH_RANGE://是一个范围
	case XPATH_LOCATIONSET://Object is a Location Set
	case XPATH_USERS://Object is user defined
	case XPATH_UNDEFINED://Object is uninitialized
		return false;
		break;
	}
	return true;
}

bool gpl::xml::updatePropertyByXPath(const char* xpath, const char* propName, const char* propValue, int length /*= -1*/)
{
	if (setXPath(xpath) == false)
		return false;
	return updatePropertyByXPath(propName, propValue, length);
}

bool gpl::xml::eraseNodeByXPath()
{
	if (m_xml->resource == NULL)
		return false;

	//cout<<"resource->type:"<<m_xml->resource->type<<endl;
	switch (m_xml->resource->type)
	{
	case XPATH_NODESET://Object is a Node Set
		if (m_xml->resource->nodesetval == NULL)
			return false;
		xmlNodePtr cur;
		//取得第一个节点
		if ((cur = (*(m_xml->resource->nodesetval->nodeTab))) == NULL)
			return true;
		xmlUnlinkNode(cur);
		xmlFreeNode(cur);
		cur = NULL;
		break;
	case XPATH_XSLT_TREE://Object is an XSLT value tree
	case XPATH_BOOLEAN://Object is a Boolean
	case XPATH_NUMBER://Object is a number
	case XPATH_STRING://Object is a string
	case XPATH_POINT://Object is a point
	case XPATH_RANGE://是一个范围
	case XPATH_LOCATIONSET://Object is a Location Set
	case XPATH_USERS://Object is user defined
	case XPATH_UNDEFINED://Object is uninitialized
		return false;
		break;
	}
	return true;
}

bool gpl::xml::eraseNodeByXPath(const char* xpath)
{
	if (setXPath(xpath) == false)
		return false;
	return eraseNodeByXPath();
}

bool gpl::xml::erasePropertyByXPath(const char* propName)
{
	if (m_xml->resource == NULL)
		return false;
	if (strlen(propName) == 0)
		return true;
	//cout<<"resource->type:"<<m_xml->resource->type<<endl;
	switch (m_xml->resource->type)
	{
	case XPATH_NODESET://Object is a Node Set
		if (m_xml->resource->nodesetval == NULL)
			return false;
		xmlNodePtr cur;
		//取得第一个节点
		if ((cur = (*(m_xml->resource->nodesetval->nodeTab))) == NULL)
			return false;
		xmlUnsetProp(cur, (const xmlChar*)propName);
		break;
	case XPATH_XSLT_TREE://Object is an XSLT value tree
	case XPATH_BOOLEAN://Object is a Boolean
	case XPATH_NUMBER://Object is a number
	case XPATH_STRING://Object is a string
	case XPATH_POINT://Object is a point
	case XPATH_RANGE://是一个范围
	case XPATH_LOCATIONSET://Object is a Location Set
	case XPATH_USERS://Object is user defined
	case XPATH_UNDEFINED://Object is uninitialized
		return false;
		break;
	}
	return true;
}

bool gpl::xml::erasePropertyByXPath(const char* xpath, const char* propName)
{
	if (setXPath(xpath) == false)
		return false;
	return erasePropertyByXPath(propName);
}

bool gpl::xml::saveXmlToFileXPath(const char* fname /*= ""*/, const char* encoding /*= ""*/, int format /*= 1*/)
{
	//xmlKeepBlanksDefault(0);
	const char* fPtr = ((strlen(fname) == 0) ? m_fileName.c_str() : fname);
	if (strlen(fPtr) == 0)
		return false;
	if (strlen(encoding) == 0)
	{
		if (xmlSaveFormatFile(fPtr, m_xml->doc, format) < 0)
			return false;
	}
	else
	{
		if (xmlSaveFormatFileEnc(fPtr, m_xml->doc, encoding, format) < 0)
			return false;
	}
	return true;
}

bool gpl::xml::saveXmlToBufferXPath(std::string& buffStr, const char* encoding /*= ""*/, int format /*= 1*/)
{
	//xmlKeepBlanksDefault(0);
	xmlChar* xmlBufferPtr = NULL;
	int xmlBufferSize = 0;
	buffStr = "";
	if (strlen(encoding) == 0)
	{
		xmlDocDumpFormatMemory(m_xml->doc, &xmlBufferPtr, &xmlBufferSize, format);
	}
	else
	{
		xmlDocDumpFormatMemoryEnc(m_xml->doc, &xmlBufferPtr, &xmlBufferSize, encoding, format);
	}
	if (xmlBufferSize == 0)
	{
		xmlFree(xmlBufferPtr);
		return true;
	}
	buffStr = m_xml->getStringByXmlCharPtr(xmlBufferPtr, 1);
	return true;
}

bool gpl::xml::dumpXPath(FILE* f /*= stdout*/)
{
	if (xmlDocDump(f, m_xml->doc) < 0)
		return false;

	return true;
}

void gpl::xml::ltoa(const long& l, std::string& str)
{
	char buff[10];
	memset(buff, 0, sizeof(buff));
	sprintf(buff, "%d\0", l);
	str = buff;
	return;
}

bool gpl::xml::createXml(std::string rootnode,std::string encod/* = "UTF-8"*/, std::string filename /*= ""*/)
{
	return true;
}

bool gpl::xml::addANode(std::string node)
{
	return true;
}

bool gpl::xml::addAItem(std::string node, std::string item, std::string content)
{
	return true;
}

bool gpl::xml::saveToFile(std::string encod /*= "UTF-8"*/, std::string filename /*= ""*/, bool blankpad /*= true*/)
{
	return true;
}

bool gpl::xml::addattribute(std::string node, std::string attriname, std::string attrivalue)
{
	return true;
}

/*void XmlApi::setOnlyGetEntityNameFlag(bool b)
{
m_xml->isOnlyEntityName=b;
return;
}
*/
