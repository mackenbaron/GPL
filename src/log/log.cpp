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
	google::SetStderrLogging(google::GLOG_INFO); //���ü������ google::INFO ����־ͬʱ�������Ļ
#else
	google::SetStderrLogging(google::GLOG_FATAL);//���ü������ google::FATAL ����־ͬʱ�������Ļ
#endif
	FLAGS_colorlogtostderr = true; //�����������Ļ����־��ʾ��Ӧ��ɫ
	FLAGS_servitysinglelog = true;// �������յȼ�����log�ļ�
	google::SetLogDestination(google::GLOG_FATAL, ".\\log\\log_fatal_"); // ���� google::FATAL �������־�洢·�����ļ���ǰ׺
	google::SetLogDestination(google::GLOG_ERROR, ".\\log\\log_error_"); //���� google::ERROR �������־�洢·�����ļ���ǰ׺
	google::SetLogDestination(google::GLOG_WARNING, ".\\log\\log_warning_"); //���� google::WARNING �������־�洢·�����ļ���ǰ׺
	google::SetLogDestination(google::GLOG_INFO, ".\\log\\log_info_"); //���� google::INFO �������־�洢·�����ļ���ǰ׺
	//google::SetLogFilenameExtension(".txt");
	FLAGS_logbufsecs = 0; //������־�����Ĭ��Ϊ30�룬�˴���Ϊ�������
	FLAGS_max_log_size = 100; //�����־��СΪ 100MB
	FLAGS_stop_logging_if_full_disk = true; //�����̱�д��ʱ��ֹͣ��־���
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

