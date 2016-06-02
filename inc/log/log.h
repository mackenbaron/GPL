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

#define LOGINIT() gpl::initLog(); /**< �궨���ʼ��log */
#define LOGDOWN() gpl::shutdownLog();/**< �궨�����log */
#define LOGINFO(...) gpl::writeLog(L_INFO, __VA_ARGS__);  /**< �궨��INFO log */
#define LOGERROR(...) gpl::writeLog(L_WARNING, __VA_ARGS__); /**< �궨�� ERROR log */
#define LOGWARNING(...) gpl::writeLog(L_ERROR,__VA_ARGS__);/**< �궨��WARNINE log */
#define LOGFATAL(...) gpl::writeLog(L_FATAL,__VA_ARGS__);/**< �궨��FATAL log */

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
		*  @date        2016/06/02 10:57
		*  @brief       ��ʼ��logһЩѡ��
		*  @return      void
		*  @pre         ��ʾ��ʱһЩ����
		- ��ǰĿ¼����logĿ¼����������ڵĻ����������ڵĻ��Թ�
		- ���ü������ google::FATAL ����־ͬʱ�������Ļ
		- ���� DEBUG_MODE ��ʱ���ü������ google::INFO ����־ͬʱ�������Ļ
		- �����������Ļ����־��ʾ��Ӧ��ɫ
		- ���յȼ�����log�ļ�
		- �����־��СΪ 100MB
		- �����̱�д��ʱ��ֹͣ��־���
		*  @remarks     �ڳ���ʼ��ʼ����־
		*/
	void initLog();
	/** 
    *  @date        2016/06/02 14:27 
    *  @brief       �ر�log��־ 
	*/
	void shutdownLog();
/** 
    *  @date        2016/06/02 14:31 
    *  @brief       дlog 
    *  @param[in]   level[outputLogLevel] д��־����
    *  @param[in]   message[char*] д��־��Ϣ������ʹ�ö��
    *  @return      void       
    */  
	void writeLog(outputLogLevel level,char* message, ...);
}