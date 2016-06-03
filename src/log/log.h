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

#define LOGINIT() gpl::Log::Instance()->initlog(); /**< 宏定义初始化log */
#define LOGINFO(...) gpl::Log::Instance()->writeLog(L_INFO, __VA_ARGS__);  /**< 宏定义INFO log */
#define LOGERROR(...) gpl::Log::Instance()->writeLog(L_WARNING, __VA_ARGS__); /**< 宏定义 ERROR log */
#define LOGWARNING(...) gpl::Log::Instance()->writeLog(L_ERROR,__VA_ARGS__);/**< 宏定义WARNINE log */
#define LOGFATAL(...) gpl::Log::Instance()->writeLog(L_FATAL,__VA_ARGS__);/**< 宏定义FATAL log */

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
	*  @author      DayBreakZhang(a365316465@gmail.com)
	*  @date        2016/06/03 10:28
	*  @class       Log
	*  @brief       日志封装类
	*  @attention   注意
	*  @bug			问题
	*  @warning     警告
					- 输入字符不得超过2048个字符
	*  @note        对日志的日常操作
					- 分级日志输出
					- 分级分文件输出
	*/
	class Log
	{
	public:
		/**
			*  @date        2016/06/03 10:34
			*  @brief       log操作类的构造函数，来执行一些初始化操作
			*/
		Log();
		/**
		*  @date        2016/06/03 10:34
		*  @brief       log操作类的析构函数，来执行一些销毁操作
		*/
		~Log();
		/**
			*  @date        2016/06/03 10:47
			*  @brief       初始化log
			*  @return      返回一数值
			- 0是成功
			- 非0 是失败
			*  @remarks     初始化化详情
			- 默认 设置级别高于 google::FATAL 的日志同时输出到屏幕
			- 定义DEBUG_MODE宏 设置级别高于 google::INFO 的日志同时输出到屏幕
			- 设置输出到屏幕的日志显示相应颜色
			- 按照等级区分log文件
			- 缓冲日志输出，立即输出
			- 最大日志大小为 100MB
			- 当磁盘被写满时，停止日志输出
			*  @see         参考内容
			*/
		int initlog();
		/**
			*  @date        2016/06/03 10:53
			*  @brief       写日志
			*  @param[in]   level[outputLogLevel] 输出日志类型
			*  @param[in]   format[const char *] 输出的格式化字符
			*  @return      void
			*  @pre         level分级
			- L_INFO 日常信息
			- L_WARNING 警告信息
			- L_ERROR 错误信息
			- L_FATAL 致命错误
			*  @pre			format格式
			- 使用printf 中的输出格式 e.g ("printf%s","hello")
			*  @remarks     可以分级写日志，写入到不同的文件里面。
			*  @see         gpl::logLevel
			*/
		void writeLog(outputLogLevel level, const char *format, ...);
		/**
			*  @date        2016/06/03 11:06
			*  @brief       初始化log静态对像
			*/
		static Log * Instance();
	private:
		static Log * m_pInstance;/**< 定义静态的LOG对像，做为全局的接口 */
		char pLogBuff[2048];/**< 定义log Buff */
	};
}