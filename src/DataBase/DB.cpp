#include <memory>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "DB.h"


class gpl::DB::dbimpl
{
public:
	dbimpl(std::string logfile = "", DBType type = DB_Invail, bool isUsingLock = false);
	virtual ~dbimpl();

};

gpl::DB::dbimpl::dbimpl(std::string logfile /*= ""*/, DBType type /*= DB_Invail*/, bool isUsingLock /*= false*/)
{

}

gpl::DB::dbimpl::~dbimpl()
{

}

gpl::DB::DB(std::string logfile /*= ""*/, DBType type /*= DB_Invail*/, bool isUsingLock /*= false*/)
{
	m_db = new dbimpl(logfile,type,isUsingLock);
}

gpl::DB::~DB()
{

}
