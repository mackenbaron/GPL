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
#include "glog\raw_logging.h"

using namespace google;

gpl::Log * gpl::Log::m_pInstance = NULL;
gpl::Log::Log()
{
	memset(pLogBuff, 0, 2048);
}

gpl::Log::~Log()
{
	//  here, cannot free the object.  
	if (NULL != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
	delete []pLogBuff;
	google::ShutdownGoogleLogging();
}

int gpl::Log::initlog()
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
	google::SetLogDestination(google::GLOG_FATAL, "./log/log_fatal_"); // ���� google::FATAL �������־�洢·�����ļ���ǰ׺
	google::SetLogDestination(google::GLOG_ERROR, "./log/log_error_"); //���� google::ERROR �������־�洢·�����ļ���ǰ׺
	google::SetLogDestination(google::GLOG_WARNING, "./log/log_warning_"); //���� google::WARNING �������־�洢·�����ļ���ǰ׺
	google::SetLogDestination(google::GLOG_INFO, "./log/log_info_"); //���� google::INFO �������־�洢·�����ļ���ǰ׺
	FLAGS_logbufsecs = 0; //������־�����Ĭ��Ϊ30�룬�˴���Ϊ�������
	FLAGS_max_log_size = 100; //�����־��СΪ 100MB
	FLAGS_stop_logging_if_full_disk = true; //�����̱�д��ʱ��ֹͣ��־���
	//google::SetLogFilenameExtension("91_"); //�����ļ�����չ����ƽ̨����������Ҫ���ֵ���Ϣ
	//google::InstallFailureSignalHandler(); //��׽ core dumped (linux)
	//google::InstallFailureWriter(&Log); //Ĭ�ϲ�׽ SIGSEGV �ź���Ϣ���������� stderr (linux)

	return 0;
}

void gpl::Log::writeLog(outputLogLevel level, const char *format, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vsprintf(pLogBuff, format, arg_ptr);
	switch (level)
	{
	case 1:
		LOG(INFO) << pLogBuff;
		break;
	case 2:
		LOG(WARNING) << pLogBuff;
		break;
	case 3:
		LOG(ERROR) << pLogBuff;
		break;
	case 4:
		LOG(FATAL) << pLogBuff;
		break;
	default:
		break;
	}
	va_end(arg_ptr);
	memset(pLogBuff, 0, 2048);
}

gpl::Log * gpl::Log::Instance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new Log();
	}
	return m_pInstance;
}