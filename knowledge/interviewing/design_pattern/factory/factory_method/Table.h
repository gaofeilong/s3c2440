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

class UserInfo: public Table {
public:
        void ShowTable()
        {
                printf("do something on talbe UserInfo\n"); 
        }
};

class NodeInfo: public Table {
public:
        void ShowTable()
        {
                printf("do something on talbe NodeInfo\n"); 
        }
};

class TableFactory {
public:
        TableFactory() {}
        virtual ~TableFactory() {}
public:
        virtual boost::shared_ptr<Table> CreateTable() = 0;
};

class UserInfoFactory: public TableFactory {
public:
        UserInfoFactory() {}
        virtual ~UserInfoFactory() {}
public:
        boost::shared_ptr<Table> CreateTable()
        {
                return boost::shared_ptr<Table>(new UserInfo());
        }
};

class NodeInfoFactory: public TableFactory {
public:
        NodeInfoFactory() {}
        virtual ~NodeInfoFactory() {}
public:
        boost::shared_ptr<Table> CreateTable()
        {
                return boost::shared_ptr<Table>(new NodeInfo());
        }
};

#endif  //_TABLE_H_
