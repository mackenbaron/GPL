#pragma  once
/** 
    *  Copyright (c) 2016, DayBreak(https://github.com/DayBreakZhang) 
    *  All rights reserved. 
    * 
    *  @file        DB.h 
    *  @author      DayBreakZhang(a365316465@gmail.com) 
    *  @date        2016/07/14 15:10 
    * 
    *  @brief       对数据库的的封装 
    *  @note        使用工厂模式对各各数据库进行实例化 
    * 
    *  @version 
    *    - v1.0    2016/07/14 15:10    DayBreakZhang    0.1 
    *  @todo	    
    */  
#import "C:\Program Files\Common Files\System\ado\msado15.dll" rename("EOF", "EndOfFile")
namespace gpl
{
	//定义数据库类型
	typedef enum _a
	{
		DB_Invail = 0,/**< 无效类型 */
		//关系型数据库
		DB_REL_MySQL = 1,/**< MYsql类型 */
		DB_REL_Oracle = 2,/**< Oracle类型 */
		DB_REL_ODBC = 3,/**< ODBC类型 */
		DB_REL_SQLITE = 4,/**< SQLITE类型 */

		//非关系型数据库
		DB_NREL_REDIS = 100,/**< Redis类型 */
	}DBType;

	//定义log类型
	typedef enum _b
	{
		DB_LOG_Normal,		/**< 普通日志 */
		DB_LOG_Exception,	/**< 异常日志 */
		DB_LOG_SQL			/**<SQL语句日志，主要调试时使用 */
	}DBLogType;
	//定义log回调函数
	typedef std::function<void(DBLogType, const char*)> DBLogFun;

	//定义查询结果集
#ifndef DBTable
	typedef std::map<std::string, std::string> DBMap;
	/** @brief 查询结果 */
	typedef std::vector<DBMap> DBTable; /**<  查询结果 */
#endif
/** 
    *  @author      DayBreakZhang(a365316465@gmail.com)
    *  @date        2016/07/14 16:56 
    *  @class       DB 
    *  @brief       数据库操作类 
    *  @attention   注意
    *  @bug	    问题
    *  @warning     警告
    *  @note         
    */ 
	class DB
	{
	public:
		/** 
			*  @date        2016/07/14 17:13 
			*  @brief       构造函数 
			*  @param[in]   logpath[string] log路径
			*  @param[in]   type[DBType] 链接数据库类型 @see gpl::DBType
			*  @param[in]   isUsingLock[false] 使用线程锁
			*  @return      void 
			*  @pre         段落
			*  @remarks     评论 
			*  @see         参考内容
			*  @test        测试       
			*/  
		DB(std::string logpath = "", DBType type = DB_Invail,bool isUsingLock = false);
		/**
		*  @date        2016/07/14 17:13
		*  @brief       析构函数
		*  @param[in]   logpath[string] log路径
		*  @param[in]   type[DBType] 链接数据库类型 @see gpl::DBType
		*  @param[in]   isUsingLock[false] 使用线程锁
		*  @return      void
		*  @pre         段落
		*  @remarks     评论
		*  @see         参考内容
		*  @test        测试
		*/
		virtual ~DB();
		/**
		*  @date        2016/07/14 17:13
		*  @brief       打开链接数据库
		*  @param[in]   conn[const char*] 链接字符串
		*  @return      成功 true 失败false 错误信息写日志
		conn 字符串详解
		@code
		MySql "host=127.0.0.1;port=3306;dbname=test;user=root;pwd=root;charset=gbk;"
		@endcode
		*  @remarks     评论
		*  @see         参考内容
		*  @test        测试
		*/
		bool Open(const char* conn);
		/**
		*  @date        2016/07/14 17:13
		*  @brief       关闭链接数据库
		*  @return      void
		*  @pre         段落
		*  @remarks     评论
		*  @see         参考内容
		*  @test        测试
		*/
		void Close(void);
		/**
		*  @date        2016/07/14 17:13
		*  @brief       数据库是否已经打开
		*  @return      打开 true 关闭 false
		*  @pre         段落
		*  @remarks     评论
		*  @see         参考内容
		*  @test        测试
		*/
		bool IsOpen();
		/**
		*  @date        2016/07/14 17:13
		*  @brief       执行入库 更新 删除
		*  @param[in]   sql[const char*]执行语句，当是关系型数据库是为sql语句，当是非关系型数据库是为操作语句
		*  @param[in]   ...[const char*]输入多个字符串
		*  @return     成功 true 失败false 错误信息写日志
		*  @pre         段落
		*  @remarks     评论
		*  @see         参考内容
		*  @test        测试
		*/
		bool ExecuteNoQuery(const char* sql, ...);
		/**
		*  @date        2016/07/14 17:13
		*  @brief       执行查询并返回第一个字段的值
		*  @param[in]   sql[const char*]执行语句，当是关系型数据库是为sql语句，当是非关系型数据库是为操作语句
		*  @param[in]   ...[const char*]输入多个字符串
		*  @return     成功 true 失败false 错误信息写日志
		*  @pre         段落
		*  @remarks     评论
		*  @see         参考内容
		*  @test        测试
		*/
		std::string ExecuteScalar(const char* sql, ...);

		/**
		*  @date        2016/07/14 17:13
		*  @brief       执行查询并返回结果集 
		*  @param[in]   sql[const char*]执行语句，当是关系型数据库是为sql语句，当是非关系型数据库是为操作语句
		*  @param[in]   ...[const char*]输入多个字符串
		*  @return		返回结果集的智能指针 @see gpl::DBTable
		*  @pre         段落
		*  @remarks     评论
		*  @see         参考内容
		*  @test        测试
		*/

		std::shared_ptr<DBTable> ExecuteQuery(const char* sql, ...);
		/**
		*  @date        2016/07/14 17:13
		*  @brief       执行查询并以回调的方式返回结果
		*  @param[in]	fun[std::function<void(const char*, const char*)>&] 结果集回调函数
		*  @param[in]   sql[const char*]执行语句，当是关系型数据库是为sql语句，当是非关系型数据库是为操作语句
		*  @param[in]   ...[const char*]输入多个字符串
		*  @return		void
		*  @pre         段落
		*  @remarks     评论
		*  @see         参考内容
		*  @test        测试
		*/
		void ExecuteQuery(const std::function<void(const char*, const char*)>& fun, const char* sql, ...);

		/**
		*  @date        2016/07/14 17:13
		*  @brief       执行事务
		*  @param[in]	fun[std::function<void()>&] 事务函数
		*  @return		void
		*  @pre         段落
		*  @remarks     评论
		*  @see         参考内容
		*  @test        测试
		*/
		void OnTransaction(const std::function<void()>& fun);
	private:
		class dbimpl;
		dbimpl *m_db;
	};
}