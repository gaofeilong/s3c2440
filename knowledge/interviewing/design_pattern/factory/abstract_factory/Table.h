#ifndef _TABLE_H_
#define _TABLE_H_
#include <boost/shared_ptr.hpp>

/*
#define MINTABLEINDEX   0      
#define USERINFO        1
#define NODEINFO        2
#define MAXTABLEINDEX   3
*/

class Table {
public:
        Table() {}
        virtual ~Table() {}
public:
        virtual void ShowTable() = 0;
};

class MysqlTable: public Table {
public:
        MysqlTable() {}
        virtual ~MysqlTable() {}
};

class OracleTable: public Table {
public:
        OracleTable() {}
        virtual ~OracleTable() {}
};

class MysqlUserInfo: public MysqlTable {
public:
        void ShowTable()
        {
                printf("do something on talbe UserInfo in Mysql database\n"); 
        }
};

class MysqlNodeInfo: public MysqlTable {
public:
        void ShowTable()
        {
                printf("do something on talbe NodeInfo in Mysql database\n"); 
        }
};

class OracleUserInfo: public OracleTable {
public:
        void ShowTable()
        {
                printf("do something on talbe UserInfo in Oracle database\n"); 
        }
};

class OracleNodeInfo: public OracleTable {
public:
        void ShowTable()
        {
                printf("do something on talbe NodeInfo in Oracle database\n"); 
        }
};

class TableFactory {
public:
        TableFactory() {}
        virtual ~TableFactory() {}
public:
        virtual boost::shared_ptr<Table> CreateUserInfo() = 0;
        virtual boost::shared_ptr<Table> CreateNodeInfo() = 0;
};

class MysqlTableFactory: public TableFactory {
public:
        MysqlTableFactory() {}
        virtual ~MysqlTableFactory() {}
public:
        boost::shared_ptr<Table> CreateUserInfo()
        {
                return boost::shared_ptr<Table>(new MysqlUserInfo());
        }
        boost::shared_ptr<Table> CreateNodeInfo()
        {
                return boost::shared_ptr<Table>(new MysqlNodeInfo());
        }
};

class OracleTableFactory: public TableFactory {
public:
        OracleTableFactory() {}
        virtual ~OracleTableFactory() {}
public:
        boost::shared_ptr<Table> CreateUserInfo()
        {
                return boost::shared_ptr<Table>(new OracleUserInfo());
        }

        boost::shared_ptr<Table> CreateNodeInfo()
        {
                return boost::shared_ptr<Table>(new OracleNodeInfo());
        }
};


#endif  //_TABLE_H_
