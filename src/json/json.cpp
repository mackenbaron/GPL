#include "rabbit.hpp"
#include "json.h"
using namespace rabbit;

class gpl::json::LibJson
{
public:
	LibJson();
	~LibJson();

};

gpl::json::LibJson::LibJson()
{

}

gpl::json::LibJson::~LibJson()
{

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

bool gpl::json::parseJson(std::string filename, int encoded)
{
	return true;
}

bool gpl::json::parseJson(char* jsonbuf, int encoded)
{
	return true;
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
	if (NULL == (fp = fopen(filename.c_str(), "r")))
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
