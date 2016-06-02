#include "log.h"
#include <stdarg.h>
#include <stdio.h>
#include <tchar.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <Windows.h>
#undef ERROR
#include <shellapi.h>
#include <Shlwapi.h>
#include <conio.h>        // For _kbhit() on Windows
#include <direct.h>        // For mkdir(path) on Windows
#include "time.h"
#include <stdio.h>
#include <stdlib.h> 
#include <queue>
#include <MMSystem.h>
#include <DbgHelp.h>  
#include <eh.h>
#define snprintf sprintf_s    // Visual Studio on Windows comes with sprintf_s() instead of snprintf()
#pragma comment(lib,"Shlwapi.lib")
#pragma comment(lib, "DbgHelp.lib")
#include <string>
using namespace std;
#include "glog\logging.h"

using namespace google;
void gpl::initLog()
{
	if ((_access(".\\log\\", 0)) == -1)
		system("md .\\log\\");

	google::InitGoogleLogging("");
#ifdef DEBUG_MODE
	google::SetStderrLogging(google::GLOG_INFO); //设置级别高于 google::INFO 的日志同时输出到屏幕
#else
	google::SetStderrLogging(google::GLOG_FATAL);//设置级别高于 google::FATAL 的日志同时输出到屏幕
#endif
	FLAGS_colorlogtostderr = true; //设置输出到屏幕的日志显示相应颜色
	FLAGS_servitysinglelog = true;// 用来按照等级区分log文件
	google::SetLogDestination(google::GLOG_FATAL, ".\\log\\log_fatal_"); // 设置 google::FATAL 级别的日志存储路径和文件名前缀
	google::SetLogDestination(google::GLOG_ERROR, ".\\log\\log_error_"); //设置 google::ERROR 级别的日志存储路径和文件名前缀
	google::SetLogDestination(google::GLOG_WARNING, ".\\log\\log_warning_"); //设置 google::WARNING 级别的日志存储路径和文件名前缀
	google::SetLogDestination(google::GLOG_INFO, ".\\log\\log_info_"); //设置 google::INFO 级别的日志存储路径和文件名前缀
	//google::SetLogFilenameExtension(".txt");
	FLAGS_logbufsecs = 0; //缓冲日志输出，默认为30秒，此处改为立即输出
	FLAGS_max_log_size = 100; //最大日志大小为 100MB
	FLAGS_stop_logging_if_full_disk = true; //当磁盘被写满时，停止日志输出
}

void gpl::writeLog(outputLogLevel level, char* message, ...)
{
	char pLogBuff[2048] = {'\0'};
	va_list arg_ptr;
	va_start(arg_ptr, message);
	vsprintf(pLogBuff, message, arg_ptr);
	switch (level)
	{
	case 1:
		DLOG(INFO) << pLogBuff;
		break;
	case 2:
		DLOG(WARNING) << pLogBuff;
		break;
	case 3:
		DLOG(ERROR) << pLogBuff;
		break;
	case 4:
		DLOG(FATAL) << pLogBuff;
		break;
	default:
		break;
	}
	va_end(arg_ptr);
}

void gpl::shutdownLog()
{
	google::ShutdownGoogleLogging();
}

