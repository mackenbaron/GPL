#pragma once

#include "stdafx.h"

int main(int argc, char *argv[])
{
	json js;

	bool s = js.parseJson("e:\\a.json");
	int size = js.getArraySize("/data/children");
}