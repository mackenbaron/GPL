#pragma once

#include "stdafx.h"
#include <iostream>
int main(int argc, char *argv[])
{
	json js;

//  	bool s = js.parseJson("e:\\test.json");	
// 
//  	int size = js.getArraySize("/data/children");
//  	std::string url = "";
//  	js.getItemDate(url, "/data/children[0]/data/selftext");
//  	std::cout << "url" << url.c_str() << std::endl;
	bool s = false;
	js.createJosn(2);
	s =js.addUnNameObject("/");
	s =js.addItem("[0]", "zhang", "zhang");

	std::string src = "";
	s =js.jsonToString(src);
}