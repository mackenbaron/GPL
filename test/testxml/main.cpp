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

	rv = xmlapi.createXml("Root","UTF-8", "a.xml");
	rv = xmlapi.addANode("a");
	rv = xmlapi.addAItem("a", "aaa", "000");
	rv = xmlapi.addAItem("a", "vvv", "000");
	rv = xmlapi.addANode("a");
	rv = xmlapi.addAItem("a", "ddd", "000");
	rv = xmlapi.addAItem("a", "xxx", "000");
	rv = xmlapi.addANode("a");
	rv = xmlapi.addAItem("a", "aaa", "000");
	rv = xmlapi.addAItem("a", "sss", "000");
	rv = xmlapi.addANode("a");
	rv = xmlapi.addAItem("a", "rrr", "000");
	rv = xmlapi.addAItem("a", "eee", "sss");
	rv = xmlapi.addANode("a");
	rv = xmlapi.addAItem("a", "yyy", "000");
	rv = xmlapi.addANode("a");
	
	
	xmlapi.saveToFile("UTF-8", "a.xml",true);
	return 1;
}