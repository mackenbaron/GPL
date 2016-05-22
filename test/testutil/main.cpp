#pragma once

#include "stdafx.h"
#include "util.h"

using namespace std;
using namespace gpl;

void teststringtoini(std::string d)
{
	util ui;
	int a = ui.StringToInt(d.c_str());
	printf("%d", a);
}
int main(int argc, char *argv[])
{
	teststringtoini("233");
	return 0;
}