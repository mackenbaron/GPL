#pragma once

#include "stdafx.h"
#include <iostream>

void createJson()
{
	json js;
	std::string src = "";
	bool s = false;
	js.createJosn(1);//����json 1Ϊ{} 2Ϊ[]
	js.addNameObject("/", "root");//�ڸ��´���root�ڵ�
	js.addItem("/root", "src", "zhang");//�ڸ���root�ڵ㣬����src
	s = js.addItem("/root", "int", 123);
	s = js.addItem("/root", "double", 1.0);
	s = js.addItem("/root", "bool", true);

	s = js.addNameArray("/root", "Name");//�ڸ���root�ڵ㴴��Name����
	s = js.jsonToString(src);
	s = js.addUnNameObject("/root/Name");//��Name�����д���һ������
	s = js.addItem("/root/Name/[0]", "name", "����");//��Name����[0]��һ�������д�����ֵ��
	s = js.addItem("/root/Name/[0]", "age", 12);
	s = js.addItem("/root/Name/[0]", "address", "�ӱ�����");
	s = js.addNameObject("/root/Name/[0]", "Url");
	s = js.addItem("/root/Name/[0]/Url", "pic", "e:/1.jpg");
	s = js.addItem("/root/Name/[0]/Url", "url", "www.baidu.com");

	s = js.addUnNameObject("/root/Name");//��Name����[1]��һ�������д�����ֵ��
	s = js.addItem("/root/Name/[1]", "name", "�Ŷ�");
	s = js.addItem("/root/Name/[1]", "age", 21);
	s = js.addItem("/root/Name/[1]", "address", "����");
	s = js.addNameObject("/root/Name/[1]", "Url");
	s = js.addItem("/root/Name/[1]/Url", "pic", "e:/2.jpg");
	s = js.addItem("/root/Name/[1]/Url", "url", "www.baidu.com");

	s = js.addItem("/root", "int", 789);//���������ֶ�
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