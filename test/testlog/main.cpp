#pragma once

#include "stdafx.h"

int main(int argc, char *argv[])
{
	LOGINIT();
	LOGINFO("First Number: %d.",1);
	LOGERROR("Second Number: %d.",2);
	std::string src= "ÖÐ¹ú";
	LOGINFO("First Number: %s.", src.c_str());
	LOGDOWN();
	return 1;
}