#pragma once
/**
	*  Copyright (c) 2016, DayBreak(https://github.com/DayBreakZhang)
	*  All rights reserved.
	*
	*  @file        log.h
	*  @author      DayBreakZhang(a365316465@gmail.com)
	*  @date        2016/06/02 10:48
	*
	*  @brief       дlog�ļ�������log�ļ���log�ļ���һЩ����
	*  @note        ʹ��goole��glog��Դ��ĿΪ����
	*
	*  @version
	*    - v1.0    2016/06/02 10:48    DayBreakZhang    0.1
	*  @todo	    ��
	*/

#define LOGINIT() gpl::Log::Instance()->initlog(); /**< �궨���ʼ��log */
#define LOGINFO(...) gpl::Log::Instance()->writeLog(L_INFO, __VA_ARGS__);  /**< �궨��INFO log */
#define LOGERROR(...) gpl::Log::Instance()->writeLog(L_WARNING, __VA_ARGS__); /**< �궨�� ERROR log */
#define LOGWARNING(...) gpl::Log::Instance()->writeLog(L_ERROR,__VA_ARGS__);/**< �궨��WARNINE log */
#define LOGFATAL(...) gpl::Log::Instance()->writeLog(L_FATAL,__VA_ARGS__);/**< �궨��FATAL log */

#define LOGTINFO(...) gpl::Log::Instance()->writeThreadLog(L_INFO, __VA_ARGS__);/**< �궨���̰߳�ȫINFO log */
#define LOGTERROR(...) gpl::Log::Instance()->writeThreadLog(L_ERROR, __VA_ARGS__);/**< �궨���̰߳�ȫERROR log */
#define LOGTWARNING(...) gpl::Log::Instance()->writeThreadLog(L_WARNING, __VA_ARGS__);/**< �궨���̰߳�ȫWARNING log */
#define LOGTFATAL(...) gpl::Log::Instance()->writeThreadLog(L_FATAL, __VA_ARGS__); /**< �궨���̰߳�ȫ log */
namespace gpl
{
	/** ������־���� */

	typedef enum logLevel
	{
		L_INFO = 1, /**< �ճ���Ϣ */
		L_WARNING = 2, /**< ������Ϣ */
		L_ERROR = 3,/**< ������Ϣ */
		L_FATAL = 4 /**< ������Ϣ */
	}outputLogLevel;
	/**< ������־���� */

	/**
	*  @author      DayBreakZhang(a365316465@gmail.com)
	*  @date        2016/06/03 10:28
	*  @class       Log
	*  @brief       ��־��װ��
	*  @attention   ע��
	*  @bug			����
	*  @warning     ����
					- �����ַ����ó���2048���ַ�
	*  @note        ����־���ճ�����
					- �ּ���־���
					- �ּ����ļ����
	*/
	class Log
	{
	public:
		/**
			*  @date        2016/06/03 10:34
			*  @brief       log������Ĺ��캯������ִ��һЩ��ʼ������
			*/
		Log();
		/**
		*  @date        2016/06/03 10:34
		*  @brief       log�������������������ִ��һЩ���ٲ���
		*/
		~Log();
		/**
			*  @date        2016/06/03 10:47
			*  @brief       ��ʼ��log
			*  @return      ����һ��ֵ
			- 0�ǳɹ�
			- ��0 ��ʧ��
			*  @remarks     ��ʼ��������
			- Ĭ�� ���ü������ google::FATAL ����־ͬʱ�������Ļ
			- ����DEBUG_MODE�� ���ü������ google::INFO ����־ͬʱ�������Ļ
			- �����������Ļ����־��ʾ��Ӧ��ɫ
			- ���յȼ�����log�ļ�
			- ������־������������
			- �����־��СΪ 100MB
			- �����̱�д��ʱ��ֹͣ��־���
			*  @see         �ο�����
			*/
		int initlog();
		/**
			*  @date        2016/06/03 10:53
			*  @brief       д��־
			*  @param[in]   level[outputLogLevel] �����־����
			*  @param[in]   format[const char *] ����ĸ�ʽ���ַ�
			*  @return      void
			*  @pre         level�ּ�
			- L_INFO �ճ���Ϣ
			- L_WARNING ������Ϣ
			- L_ERROR ������Ϣ
			- L_FATAL ��������
			*  @pre			format��ʽ
			- ʹ��printf �е������ʽ e.g ("printf%s","hello")
			*  @remarks     ���Էּ�д��־��д�뵽��ͬ���ļ����档
			*  @see         gpl::logLevel
			*/
		void writeLog(outputLogLevel level, const char *format, ...);
		/**
		*  @date        2016/06/03 10:53
		*  @brief       д�̰߳�ȫ��־
		*  @param[in]   level[outputLogLevel] �����־����
		*  @param[in]   format[const char *] ����ĸ�ʽ���ַ�
		*  @return      void
		*  @pre         level�ּ�
		- L_INFO �ճ���Ϣ
		- L_WARNING ������Ϣ
		- L_ERROR ������Ϣ
		- L_FATAL ��������
		*  @pre			format��ʽ
		- ʹ��printf �е������ʽ e.g ("printf%s","hello")
		*  @remarks     ���Էּ�д��־��д�뵽��ͬ���ļ����档
		*  @see         gpl::logLevel
		*/
		void writeThreadLog(outputLogLevel level, const char *format, ...);
		/**
			*  @date        2016/06/03 11:06
			*  @brief       ��ʼ��log��̬����
			*/
		static Log * Instance();
	private:
		static Log * m_pInstance;/**< ���徲̬��LOG������Ϊȫ�ֵĽӿ� */
		char pLogBuff[2048];/**< ����log Buff */
	};
}