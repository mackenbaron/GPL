#pragma once

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include "util.h"
#include "xml.h"
using namespace std;
using namespace gpl;

void parseXml()
{
	xml xmlapi;
	multimap<string, string> resultSet;
	map<string, string> props;
	if (xmlapi.openXPath("e:/proxyConfig.xml") == false)
	{
	 	cerr << "ERROR:open file:" << "e:/proxyConfig.xml" << endl;
	 	exit(-1);
	}
	if (xmlapi.getEntityValue("channels", props) == false)
	 	cerr << "ERROR: Entity " << "proxyConfig" << " does not exist!" << endl;
	if (xmlapi.setXPath("/channels/*") == false)
	{
	 	cerr << "ERROR:setXPath!" << endl;
	 	xmlapi.closeXPath();
	 	exit(0);
	}
	if (xmlapi.getXPathResultSet(resultSet) == false)
	 	cerr << "ERROR:can't get!" << endl;
	xmlapi.closeXPath();
}
void createxml()
{
	xml xmlapi;
	xmlapi.createXml("root");

	xmlapi.addElement("/root","people");
	xmlapi.addElement("/root/people[1]", "name", "����");
	xmlapi.addElement("/root/people[1]", "age", "12");
	xmlapi.addElement("/root/people[1]", "gender", "��");
	xmlapi.addElement("/root/people[1]", "address", "��������");

	xmlapi.addElement("/root", "people");
	xmlapi.addAttribute("/root/people[2]", "name", "����");
	xmlapi.addAttribute("/root/people[2]", "age", "78");
	xmlapi.addAttribute("/root/people[2]", "gender", "Ů");
	xmlapi.addAttribute("/root/people[2]", "address", "���");

	std::string src = "";
	xmlapi.saveXmlToBuffer(src);
}
int main(int argc, char **argv)
{	
	createxml();
	return 1;
}