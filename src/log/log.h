#pragma once
/**
	*  Copyright (c) 2016, DayBreak(https://github.com/DayBreakZhang)
	*  All rights reserved.
	*
	*  @file        log.h
	*  @author      DayBreakZhang(a365316465@gmail.com)
	*  @date        2016/06/02 10:48
	*
	*  @brief       写log文件、分析log文件、log文件的一些操作
	*  @note        使用goole的glog开源项目为基础
	*
	*  @version
	*    - v1.0    2016/06/02 10:48    DayBreakZhang    0.1
	*  @todo	    无
	*/

#define LOGINIT() gpl::initLog(); /**< 宏定义初始化log */
#define LOGDOWN() gpl::shutdownLog();/**< 宏定义结束log */
#define LOGINFO(...) gpl::writeLog(L_INFO, __VA_ARGS__);  /**< 宏定义INFO log */
#define LOGERROR(...) gpl::writeLog(L_WARNING, __VA_ARGS__); /**< 宏定义 ERROR log */
#define LOGWARNING(...) gpl::writeLog(L_ERROR,__VA_ARGS__);/**< 宏定义WARNINE log */
#define LOGFATAL(...) gpl::writeLog(L_FATAL,__VA_ARGS__);/**< 宏定义FATAL log */

namespace gpl
{
	/** 设置日志级别 */

	typedef enum logLevel
	{
		L_INFO = 1, /**< 日常信息 */
		L_WARNING = 2, /**< 警告信息 */
		L_ERROR = 3,/**< 错误信息 */
		L_FATAL = 4 /**< 致命信息 */
	}outputLogLevel;
	/**< 设置日志级别 */

	/**
		*  @date        2016/06/02 10:57
		*  @brief       初始化log一些选项
		*  @return      void
		*  @pre         出示化时一些特性
		- 当前目录创建log目录，如果不存在的话创建，存在的话略过
		- 设置级别高于 google::FATAL 的日志同时输出到屏幕
		- 定义 DEBUG_MODE 宏时设置级别高于 google::INFO 的日志同时输出到屏幕
		- 设置输出到屏幕的日志显示相应颜色
		- 按照等级区分log文件
		- 最大日志大小为 100MB
		- 当磁盘被写满时，停止日志输出
		*  @remarks     在程序开始初始化日志
		*/
	void initLog();
	/** 
    *  @date        2016/06/02 14:27 
    *  @brief       关闭log日志 
	*/
	void shutdownLog();
/** 
    *  @date        2016/06/02 14:31 
    *  @brief       写log 
    *  @param[in]   level[outputLogLevel] 写日志级别
    *  @param[in]   message[char*] 写日志信息，可以使用多个
    *  @return      void       
    */  
	void writeLog(outputLogLevel level,char* message, ...);
}