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
void testpar()
{
	util ui;
	std::map<std::string, std::vector<std::string> > result = ui.ParsingArgsSrc("-i 123 -v 456 -a 789","i%InputFile","v%OutFileVideo","a%OutFileAudio");
}
void testEncrypt()
{
	util ui;
	std::string src = ui.SrcEncrypt("zhangchangsheng", "1");
	std::string src1 = ui.SrcDecrypt(src, "1");
}
void testgetFileVerify()
{
	util ui;
	std::vector<std::string> file;
	file.push_back("E:\\mp4\\a\\123.mp4");
	file.push_back("E:\\mp4\\a\\10175_1.jpg");
	std::vector<Result> r;
	int a = ui.getFileVerify(file,r);
}
int main(int argc, char *argv[])
{
	//teststringtoini("233");
	//testpar();
	//testEncrypt();
	testgetFileVerify();
	return 0;
}