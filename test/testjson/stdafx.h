#pragma once

#if defined WIN32 || defined _WIN32
#include <io.h>
#include <winsock2.h>
#include <Windows.h>
#undef ERROR
#include <shellapi.h>
#include <Shlwapi.h>
#include <conio.h>       
#include <direct.h> 
#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <queue>
#include <MMSystem.h>
#include <map>
#pragma comment(lib,"Shlwapi.lib")
#pragma comment(lib, "DbgHelp.lib")
#else
#include <stdio.h>  
#include <termios.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h> 
#endif 
#include "json.h";
using namespace gpl;