#include <stdio.h>
#include "Table.h"

int main()
{
        boost::shared_ptr<TableFactory> pfac;
        boost::shared_ptr<Table> ptbl;

        pfac = boost::shared_ptr<TableFactory>(new MysqlTableFactory());
        ptbl = pfac->CreateUserInfo();
        ptbl->ShowTable();
        ptbl.reset();
        ptbl = pfac->CreateNodeInfo();
        ptbl->ShowTable();
        ptbl.reset();

        pfac.reset();
        pfac = boost::shared_ptr<TableFactory>(new OracleTableFactory());
        ptbl = pfac->CreateUserInfo();
        ptbl->ShowTable();
        ptbl.reset();
        ptbl = pfac->CreateNodeInfo();
        ptbl->ShowTable();
        ptbl.reset();
        return 0;
}
