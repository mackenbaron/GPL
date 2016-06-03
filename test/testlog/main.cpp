#pragma once

#include "stdafx.h"

int main(int argc, char *argv[])
{
	LOGINIT();
 	LOGINFO("First Number: %d.", 1);
 	LOGERROR("Second Number: %d.", 2);
 	std::string src = "ÖÐ¹ú";
 	LOGINFO("First Number: %s.", src.c_str());
	LOGINFO("First Number: %d.", 1);
	LOGERROR("Second Number: %d.", 2);
	LOGINFO("First Number: %s.", src.c_str());
	LOGTINFO("First Number: %d.", 1);
	system("pause");
	return 1;
}