#pragma once

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include "util.h"
#include "xml.h"
using namespace std;
using namespace gpl;
int main(int argc, char **argv)
{
// 	xml xmlapi;
// 	multimap<string, string> resultSet;
// 	map<string, string> props;
// 	if (xmlapi.openXPath("e:/proxyConfig.xml") == false)
// 	{
// 		cerr << "ERROR:open file:" << "e:/proxyConfig.xml" << endl;
// 		exit(-1);
// 	}
// 	if (xmlapi.getEntityValue("channels", props) == false)
// 		cerr << "ERROR: Entity " << "proxyConfig" << " does not exist!" << endl;
// 	if (xmlapi.setXPath("/channels/*") == false)
// 	{
// 		cerr << "ERROR:setXPath!" << endl;
// 		xmlapi.closeXPath();
// 		exit(0);
// 	}
// 	if (xmlapi.getXPathResultSet(resultSet) == false)
// 		cerr << "ERROR:can't get!" << endl;
// 	xmlapi.closeXPath();
	bool rv;
	xml xmlapi;

	rv = xmlapi.createXml();
	rv = xmlapi.addANode("t111");
	rv = xmlapi.addANode("t222");
	rv = xmlapi.addANode("t333");
	rv = xmlapi.addANode("t444");
	rv = xmlapi.addANode("t555");
	rv = xmlapi.addANode("t666");

	rv = xmlapi.addAItem("t111", "aaa", "000");
	rv = xmlapi.addAItem("t333", "vvv", "000");
	rv = xmlapi.addAItem("t222", "ddd", "000");
	rv = xmlapi.addAItem("t222", "xxx", "000");
	rv = xmlapi.addAItem("t444", "aaa", "000");
	rv = xmlapi.addAItem("t333", "sss", "000");
	rv = xmlapi.addAItem("t444", "rrr", "000");
	rv = xmlapi.addAItem("t555", "eee", "sss");
	rv = xmlapi.addAItem("t111", "yyy", "000");
	xmlapi.saveToFile("UTF-8", "a.xml",true);
	return 1;
}