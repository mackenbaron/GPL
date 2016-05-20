#pragma once

#if defined WIN32 || defined _WIN32
#include <io.h>
#include <winsock2.h>
#include <Windows.h>
#include <shellapi.h>
#include <Shlwapi.h>
#include <conio.h>        // For _kbhit() on Windows
#include <direct.h>        // For mkdir(path) on Windows
#include "time.h"
#include <stdio.h>
#include <stdlib.h> 
#include <queue>
#include <MMSystem.h>
#include <map>
#define snprintf sprintf_s    // Visual Studio on Windows comes with sprintf_s() instead of snprintf()
#pragma comment(lib,"Shlwapi.lib")
#pragma comment(lib, "DbgHelp.lib")
#else
#include <stdio.h>        // For getchar() on Linux
#include <termios.h>    // For kbhit() on Linux
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>    // For mkdir(path, options) on Linux
#endif 
#include <string>