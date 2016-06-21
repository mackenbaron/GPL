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

bool gpl::json::parseJson(std::string filename)
{
	return true;
}

bool gpl::json::parseJson(char* jsonbuf)
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

void gpl::json::getItemDate(std::string &date, std::string par)
{

}

void gpl::json::getItemDate(bool &date, std::string par)
{

}

void gpl::json::getItemDate(double &date, std::string par)
{

}
