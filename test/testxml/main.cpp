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
	xmlapi.createXml();
}
int main(int argc, char **argv)
{	
	createxml();
	return 1;
}