#include  <io.h>
#include  <stdio.h>
#include  <stdlib.h>
#include <vector>
#include <map>
#include "rabbit.hpp"
#include "json.h"
#include "util.h"

using namespace rabbit;

class gpl::json::LibJson
{
public:
	LibJson();
	~LibJson();
	bool rabbitParseJson(std::string src);
private:
	std::string mjsonsrc;
	document rootdoc;

};

gpl::json::LibJson::LibJson()
	:mjsonsrc("")
{

}

gpl::json::LibJson::~LibJson()
{

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
	return 1;
}

void gpl::json::getItemDate(int& date, std::string par)
{

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

}

void gpl::json::getItemDate(bool &date, std::string par)
{

}

void gpl::json::getItemDate(double &date, std::string par)
{

}
