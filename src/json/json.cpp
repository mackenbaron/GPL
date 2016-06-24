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
	bool rabbitParseJson(std::string src);
	int returnArraySize(std::string xp);
private:
	vector<pair<TokenType, string> > getxpath(std::string input);
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
	vector<pair<TokenType, string> > xpathsrc = getxpath(xp);
	object _tempitem = rootdoc;
	try
	{		
		for (int i = 0; i < xpathsrc.size(); i++)
		{
			TokenType t = xpathsrc[i].first;			
			if (t == T_Slash)
			{
				i++;
				std::string v = xpathsrc[i].second;
				_tempitem = _tempitem["" + v + ""];
			}			
		}
		arraysize = _tempitem.size();
	}
	catch (...)
	{
		arraysize = -1;
	}
	
	return arraysize;
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
