#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include "rabbit.hpp"
#include "json.h"
#include "util.h"
#include "Tokenizer.h"

using namespace rabbit;
using namespace xpath;
using namespace std;

class gpl::json::LibJson
{
public:
	LibJson();
	~LibJson();
	bool rabbitParseJson(std::string src);//解析json
	int returnArraySize(std::string xp);//返回数组大小
	std::string getStringDate(std::string xp);//获取json指定的值
	bool getBoolDate(std::string xp);//获取json指定的值
	int getInitDate(std::string xp);//获取json指定的值
	double getDoubleDate(std::string xp);//获取json指定的值

	void createJsonType(int t){ mjsontype = t; }//设置json的类型

	bool createUnNameObject(std::string xp);//创建无名的对像
	bool createNameObject(std::string xp, char* on);//创建有名字的对像
	bool createNameArray(std::string xp, char* an);//创建有名字的数组

	bool createJsonItem(std::string xp, char*n, std::string v);

	std::string getJsonSrc();
private:
	vector<pair<TokenType, string> > getxpath(std::string input);//解析xpath
	bool setObjectPost(std::string xp);//根据xpath结果设置临时object
private:
	int mjsontype;//创建类型
	std::string mjsonsrc;
	document rootdoc;//解析

	object setpost;//临时

	object createJsonObject;//创建
	array createJsonArray;//创建
};

gpl::json::LibJson::LibJson()
	:mjsonsrc("")
	, mjsontype(0)
{
	createJsonObject.clear();
	createJsonArray.clear();
}

gpl::json::LibJson::~LibJson()
{
	createJsonObject.clear();
	createJsonArray.clear();
}

bool gpl::json::LibJson::rabbitParseJson(std::string src)
{
	try
	{
		rootdoc.parse(src);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

vector<pair<TokenType, string> > gpl::json::LibJson::getxpath(std::string input)
{
	vector<pair<TokenType, string> > received;

	const char* input_data = input.data();
	const char* input_end = input_data + input.size();
	TokenType token_type;
	const char* token_data;
	size_t token_size;
	while ((token_type = ScanToken(input_data, input_end - input_data, &token_data, &token_size)) != T_None) {
		received.push_back({ token_type, string(token_data, token_data + token_size) });
		input_data = token_data + token_size;
	}
	return received;
}

int gpl::json::LibJson::returnArraySize(std::string xp)
{
	int arraysize = 0;
	if (setObjectPost(xp))
		arraysize = setpost.size();	
	return arraysize;
}

bool gpl::json::LibJson::setObjectPost(std::string xp)
{
	
	vector<pair<TokenType, string> > xpathsrc = getxpath(xp);
	try
	{
		if (mjsontype == 0)
		{
			setpost = rootdoc;
		}
		else if (mjsontype ==1)
		{
			setpost = createJsonObject;
		}
		else if (mjsontype == 2)
		{
			setpost = createJsonArray;
		}

		for (int i = 0; i < xpathsrc.size(); i++)
		{
			TokenType t = xpathsrc[i].first;
			switch (t)
			{
			case T_Number:
				setpost = setpost.at(atoi(xpathsrc[i].second.c_str()));
				break;
			case T_NameTest:
				setpost = setpost["" + xpathsrc[i].second + ""];
				break;
			default:
				break;
			}
		}
	}
	catch (...)
	{
		return false;
	}
	return true;
}

std::string gpl::json::LibJson::getStringDate(std::string xp)
{
	if (setObjectPost(xp))
		if ((!setpost.is_null()) && (setpost.is_string()))
			return setpost.as_string();
		else
			return "NULL";
	else
		return "";
}

bool gpl::json::LibJson::getBoolDate(std::string xp)
{
	if (setObjectPost(xp))
		if ((!setpost.is_null())&&(setpost.is_bool()))
			return setpost.as_bool();
		else
			return false;
	else
		return false;
}

int gpl::json::LibJson::getInitDate(std::string xp)
{
	if (setObjectPost(xp))
		if ((!setpost.is_null()) && (setpost.is_int()))
			return setpost.as_int();
		else
			return 0;
	else
		return 0;
}

double gpl::json::LibJson::getDoubleDate(std::string xp)
{
	if (setObjectPost(xp))
		if ((!setpost.is_null()) && (setpost.is_double()))
			return setpost.as_double();
		else
			return 0;
	else
		return 0;
}

bool gpl::json::LibJson::createUnNameObject(std::string xp)
{
	try
	{
		if (setObjectPost(xp))
		{
			object item;
			setpost.push_back(item);
		}
		else
		{
			return false;
		}
	}
	catch (...)
	{
		return false;
	}
	return true;
	
}

bool gpl::json::LibJson::createNameObject(std::string xp, char* on)
{
	try
	{
		if (setObjectPost(xp))
		{
			object item;
			setpost.insert(on,item);
		}
		else
		{
			return false;
		}
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool gpl::json::LibJson::createNameArray(std::string xp, char* an)
{
	try
	{
		if (setObjectPost(xp))
		{
			array item;
			setpost.insert(an, item);
		}
		else
		{
			return false;
		}
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool gpl::json::LibJson::createJsonItem(std::string xp, char* n, std::string v)
{
	try
	{
		if (setObjectPost(xp))
		{
			if (n != NULL)
			{
				setpost.insert(n, 123);
			}
			else{ return false; }
		}
		else
		{
			return false;
		}
	}
	catch (...)
	{
		return false;
	}
	return true;
}

std::string gpl::json::LibJson::getJsonSrc()
{
	if (mjsontype == 1)
	{
		if (!createJsonObject.is_null())
			return createJsonObject.str();
		else
			return "";
	}
	else if (mjsontype == 2)
	{
		if (!createJsonArray.is_null())
		{
			std::string src = createJsonArray.str();
			return createJsonArray.str();
		}
		else
			return "";
	}
}

gpl::json::json()
{
	m_json = new LibJson();
}

gpl::json::~json()
{
	if (m_json != 0)
	{
		delete m_json;
		m_json = 0;
	}
}

bool gpl::json::parseJson(std::string filename, int encoded /*= 0*/)
{
	util u;
	std::string _tempsrc = "";
	if ((filename.empty() == true))
		return false;
	if (filename[0] == '{' || filename[0] == '[')
		_tempsrc = filename;
	else
		_tempsrc = readFile(filename);

	if (_tempsrc.empty() == true)
		return false;
	if (encoded == 0)
	{
		std::wstring src = u.Utf2U(_tempsrc);
		_tempsrc = u.U2A(src);
		_tempsrc = _tempsrc.substr(1, _tempsrc.size());
	}
	return m_json->rabbitParseJson(_tempsrc);
}

int gpl::json::getArraySize(std::string par)
{
	return m_json->returnArraySize(par);
}

void gpl::json::getItemDate(int& date, std::string par)
{
	date = m_json->getInitDate(par);
}

std::string gpl::json::readFile(std::string filename)
{
	std::string src = "";
	FILE *fp;
	if (NULL == (fp = fopen(filename.c_str(), "rb")))
	{
		src = "{\"Error\":\"Open json file Error\"}";
		return src;
	}

	char ch;
	while (EOF != (ch = fgetc(fp)))
	{
		src.push_back(ch);
	}
	fclose(fp);

	return src;
}

void gpl::json::getItemDate(std::string &date, std::string par)
{
	date = m_json->getStringDate(par);
}

void gpl::json::getItemDate(bool &date, std::string par)
{
	date = m_json->getBoolDate(par);
}

void gpl::json::getItemDate(double &date, std::string par)
{
	date = m_json->getDoubleDate(par);
}

void gpl::json::createJosn(int type)
{
	m_json->createJsonType(type);
}

bool gpl::json::addUnNameObject(std::string par)
{
	return m_json->createUnNameObject(par);
}

bool gpl::json::addNameObject(std::string par, char* on)
{
	return m_json->createNameObject(par, on);
}

bool gpl::json::addNameArray(std::string par, char* an)
{
	return m_json->createNameObject(par, an);
}

bool gpl::json::addItem(std::string par, char* n, char* v)
{
	return m_json->createJsonItem(par, n, v);
}

bool gpl::json::jsonToString(std::string jsonsrc)
{
	std::string src = m_json->getJsonSrc();
	jsonsrc = src;
	return true;
}

bool gpl::json::jsonToFile(std::string filename)
{
	return true;
}
