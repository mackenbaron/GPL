#pragma  once
/** 
    *  Copyright (c) 2016, DayBreak(https://github.com/DayBreakZhang) 
    *  All rights reserved. 
    * 
    *  @file        DB.h 
    *  @author      DayBreakZhang(a365316465@gmail.com) 
    *  @date        2016/07/14 15:10 
    * 
    *  @brief       �����ݿ�ĵķ�װ 
    *  @note        ʹ�ù���ģʽ�Ը������ݿ����ʵ���� 
    * 
    *  @version 
    *    - v1.0    2016/07/14 15:10    DayBreakZhang    0.1 
    *  @todo	    
    */  
#import "C:\Program Files\Common Files\System\ado\msado15.dll" rename("EOF", "EndOfFile")
namespace gpl
{
	//�������ݿ�����
	typedef enum _a
	{
		DB_Invail = 0,/**< ��Ч���� */
		//��ϵ�����ݿ�
		DB_REL_MySQL = 1,/**< MYsql���� */
		DB_REL_Oracle = 2,/**< Oracle���� */
		DB_REL_ODBC = 3,/**< ODBC���� */
		DB_REL_SQLITE = 4,/**< SQLITE���� */

		//�ǹ�ϵ�����ݿ�
		DB_NREL_REDIS = 100,/**< Redis���� */
	}DBType;

	//����log����
	typedef enum _b
	{
		DB_LOG_Normal,		/**< ��ͨ��־ */
		DB_LOG_Exception,	/**< �쳣��־ */
		DB_LOG_SQL			/**<SQL�����־����Ҫ����ʱʹ�� */
	}DBLogType;
	//����log�ص�����
	typedef std::function<void(DBLogType, const char*)> DBLogFun;

	//�����ѯ�����
#ifndef DBTable
	typedef std::map<std::string, std::string> DBMap;
	/** @brief ��ѯ��� */
	typedef std::vector<DBMap> DBTable; /**<  ��ѯ��� */
#endif
/** 
    *  @author      DayBreakZhang(a365316465@gmail.com)
    *  @date        2016/07/14 16:56 
    *  @class       DB 
    *  @brief       ���ݿ������ 
    *  @attention   ע��
    *  @bug	    ����
    *  @warning     ����
    *  @note         
    */ 
	class DB
	{
	public:
		/** 
			*  @date        2016/07/14 17:13 
			*  @brief       ���캯�� 
			*  @param[in]   logpath[string] log·��
			*  @param[in]   type[DBType] �������ݿ����� @see gpl::DBType
			*  @param[in]   isUsingLock[false] ʹ���߳���
			*  @return      void 
			*  @pre         ����
			*  @remarks     ���� 
			*  @see         �ο�����
			*  @test        ����       
			*/  
		DB(std::string logpath = "", DBType type = DB_Invail,bool isUsingLock = false);
		/**
		*  @date        2016/07/14 17:13
		*  @brief       ��������
		*  @param[in]   logpath[string] log·��
		*  @param[in]   type[DBType] �������ݿ����� @see gpl::DBType
		*  @param[in]   isUsingLock[false] ʹ���߳���
		*  @return      void
		*  @pre         ����
		*  @remarks     ����
		*  @see         �ο�����
		*  @test        ����
		*/
		virtual ~DB();
		/**
		*  @date        2016/07/14 17:13
		*  @brief       ���������ݿ�
		*  @param[in]   conn[const char*] �����ַ���
		*  @return      �ɹ� true ʧ��false ������Ϣд��־
		conn �ַ������
		@code
		MySql "host=127.0.0.1;port=3306;dbname=test;user=root;pwd=root;charset=gbk;"
		@endcode
		*  @remarks     ����
		*  @see         �ο�����
		*  @test        ����
		*/
		bool Open(const char* conn);
		/**
		*  @date        2016/07/14 17:13
		*  @brief       �ر��������ݿ�
		*  @return      void
		*  @pre         ����
		*  @remarks     ����
		*  @see         �ο�����
		*  @test        ����
		*/
		void Close(void);
		/**
		*  @date        2016/07/14 17:13
		*  @brief       ���ݿ��Ƿ��Ѿ���
		*  @return      �� true �ر� false
		*  @pre         ����
		*  @remarks     ����
		*  @see         �ο�����
		*  @test        ����
		*/
		bool IsOpen();
		/**
		*  @date        2016/07/14 17:13
		*  @brief       ִ����� ���� ɾ��
		*  @param[in]   sql[const char*]ִ����䣬���ǹ�ϵ�����ݿ���Ϊsql��䣬���Ƿǹ�ϵ�����ݿ���Ϊ�������
		*  @param[in]   ...[const char*]�������ַ���
		*  @return     �ɹ� true ʧ��false ������Ϣд��־
		*  @pre         ����
		*  @remarks     ����
		*  @see         �ο�����
		*  @test        ����
		*/
		bool ExecuteNoQuery(const char* sql, ...);
		/**
		*  @date        2016/07/14 17:13
		*  @brief       ִ�в�ѯ�����ص�һ���ֶε�ֵ
		*  @param[in]   sql[const char*]ִ����䣬���ǹ�ϵ�����ݿ���Ϊsql��䣬���Ƿǹ�ϵ�����ݿ���Ϊ�������
		*  @param[in]   ...[const char*]�������ַ���
		*  @return     �ɹ� true ʧ��false ������Ϣд��־
		*  @pre         ����
		*  @remarks     ����
		*  @see         �ο�����
		*  @test        ����
		*/
		std::string ExecuteScalar(const char* sql, ...);

		/**
		*  @date        2016/07/14 17:13
		*  @brief       ִ�в�ѯ�����ؽ���� 
		*  @param[in]   sql[const char*]ִ����䣬���ǹ�ϵ�����ݿ���Ϊsql��䣬���Ƿǹ�ϵ�����ݿ���Ϊ�������
		*  @param[in]   ...[const char*]�������ַ���
		*  @return		���ؽ����������ָ�� @see gpl::DBTable
		*  @pre         ����
		*  @remarks     ����
		*  @see         �ο�����
		*  @test        ����
		*/

		std::shared_ptr<DBTable> ExecuteQuery(const char* sql, ...);
		/**
		*  @date        2016/07/14 17:13
		*  @brief       ִ�в�ѯ���Իص��ķ�ʽ���ؽ��
		*  @param[in]	fun[std::function<void(const char*, const char*)>&] ������ص�����
		*  @param[in]   sql[const char*]ִ����䣬���ǹ�ϵ�����ݿ���Ϊsql��䣬���Ƿǹ�ϵ�����ݿ���Ϊ�������
		*  @param[in]   ...[const char*]�������ַ���
		*  @return		void
		*  @pre         ����
		*  @remarks     ����
		*  @see         �ο�����
		*  @test        ����
		*/
		void ExecuteQuery(const std::function<void(const char*, const char*)>& fun, const char* sql, ...);

		/**
		*  @date        2016/07/14 17:13
		*  @brief       ִ������
		*  @param[in]	fun[std::function<void()>&] ������
		*  @return		void
		*  @pre         ����
		*  @remarks     ����
		*  @see         �ο�����
		*  @test        ����
		*/
		void OnTransaction(const std::function<void()>& fun);
	private:
		class dbimpl;
		dbimpl *m_db;
	};
}