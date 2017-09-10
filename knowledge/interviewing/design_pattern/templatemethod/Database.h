#ifndef _DATABASE_H_
#define _DATABASE_H_
#include <stdio.h>

struct Table {
        int fields;
};

class DatabaseOperation {
public:
        virtual ~DatabaseOperation() {}
public:
        void GetTable(struct Table *t)
        {
                Connect(); 
                Select();
                DisConnect();
        }
protected:
        virtual void Connect() = 0;
        virtual void Select() = 0;
        virtual void DisConnect() = 0;
};

class OracleOperation: public DatabaseOperation {
protected:
        void Connect() { printf("connect to oracle\n"); }
        void Select() { printf("select from oracle\n"); }
        void DisConnect() { printf("close connect to oracle\n"); }
};

class MysqlOperation: public DatabaseOperation {
protected:
        void Connect() { printf("connect to mysql\n"); }
        void Select() { printf("select from mysql\n"); }
        void DisConnect() { printf("close connect to mysql\n"); }
};

#endif  //_DATABASE_H_
