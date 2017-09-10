#ifndef _TABLE_H_
#define _TABLE_H_
#include <boost/shared_ptr.hpp>

#define MINTABLEINDEX   0      
#define USERINFO        1
#define NODEINFO        2
#define MAXTABLEINDEX   3

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
        boost::shared_ptr<Table> CreateTable(int type)
        {
                assert(type > MINTABLEINDEX && type < MAXTABLEINDEX);
                switch (type) {
                case USERINFO: 
                        return boost::shared_ptr<Table>(new UserInfo());
                        break;
                case NODEINFO:
                        return boost::shared_ptr<Table>(new NodeInfo());
                        break;
                default:
                        break;
                }
        }
};

#endif  //_TABLE_H_
