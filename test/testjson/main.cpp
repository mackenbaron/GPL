#pragma once

#include "stdafx.h"
#include <iostream>

void createJson()
{
	json js;
	std::string src = "";
	bool s = false;
	js.createJosn(1);//创建json 1为{} 2为[]
	js.addNameObject("/", "root");//在根下创建root节点
	js.addItem("/root", "src", "zhang");//在根下root节点，创建src
	s = js.addItem("/root", "int", 123);
	s = js.addItem("/root", "double", 1.0);
	s = js.addItem("/root", "bool", true);

	s = js.addNameArray("/root", "Name");//在根下root节点创建Name数组
	s = js.jsonToString(src);
	s = js.addUnNameObject("/root/Name");//在Name数组中创建一个对像
	s = js.addItem("/root/Name/[0]", "name", "张三");//在Name数组[0]第一个对像中创建键值对
	s = js.addItem("/root/Name/[0]", "age", 12);
	s = js.addItem("/root/Name/[0]", "address", "河北保定");
	s = js.addNameObject("/root/Name/[0]", "Url");
	s = js.addItem("/root/Name/[0]/Url", "pic", "e:/1.jpg");
	s = js.addItem("/root/Name/[0]/Url", "url", "www.baidu.com");

	s = js.addUnNameObject("/root/Name");//在Name数组[1]第一个对像中创建键值对
	s = js.addItem("/root/Name/[1]", "name", "张二");
	s = js.addItem("/root/Name/[1]", "age", 21);
	s = js.addItem("/root/Name/[1]", "address", "保定");
	s = js.addNameObject("/root/Name/[1]", "Url");
	s = js.addItem("/root/Name/[1]/Url", "pic", "e:/2.jpg");
	s = js.addItem("/root/Name/[1]/Url", "url", "www.baidu.com");

	s = js.addItem("/root", "int", 789);//更新以有字段
	s = js.addItem("/root", "double", 1125.0);
	s = js.addItem("/root", "bool", false);


	s = js.jsonToString(src);
	js.jsonToFile("e:\\a.json");

}
void parseJson()
{
	json js;
	std::string src = "";

	bool s = js.parseJson("e:\\test.json");	
	 
	int size = js.getArraySize("/data/children");
	std::string url = "";
	js.getItemDate(url, "/data/children[0]/data/selftext");
	std::cout << "url" << url.c_str() << std::endl;

}
int main(int argc, char *argv[])
{
	createJson();
}