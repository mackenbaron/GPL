#pragma once

#include "stdafx.h"
#include <iostream>
int main(int argc, char *argv[])
{
	json js;

 	bool s = js.parseJson("e:\\test.json");	

// 	int size = js.getArraySize("/data/children");
 	std::string url = "";
 	js.getItemDate(url, "/data/children[1]/data/selftext");
// 	std::cout << "url" << url.c_str() << std::endl;
}