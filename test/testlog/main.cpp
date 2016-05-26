#pragma once

#include "stdafx.h"
void initlog()
{
	if ((_access(".\\log\\", 0)) == -1)
		system("md .\\log\\");

	google::InitGoogleLogging("");
	//FLAGS_servitysinglelog = true;// �������յȼ�����log�ļ�
	google::SetLogDestination(google::GLOG_FATAL, ".\\log\\log_fatal_"); // ���� google::FATAL �������־�洢·�����ļ���ǰ׺
	google::SetLogDestination(google::GLOG_ERROR, ".\\log\\log_error_"); //���� google::ERROR �������־�洢·�����ļ���ǰ׺
	google::SetLogDestination(google::GLOG_WARNING, ".\\log\\log_warning_"); //���� google::WARNING �������־�洢·�����ļ���ǰ׺
	google::SetLogDestination(google::GLOG_INFO, ".\\log\\log_info_"); //���� google::INFO �������־�洢·�����ļ���ǰ׺
	FLAGS_logbufsecs = 0; //������־�����Ĭ��Ϊ30�룬�˴���Ϊ�������
	FLAGS_max_log_size = 100; //�����־��СΪ 100MB
	FLAGS_stop_logging_if_full_disk = true; //�����̱�д��ʱ��ֹͣ��־���
}
int main(int argc, char *argv[])
{
	initlog();
	LOG(INFO) << "Hello glog";
	return 1;
}