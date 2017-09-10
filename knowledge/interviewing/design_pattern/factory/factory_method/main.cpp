#include <stdio.h>
#include "Table.h"

int main()
{
        boost::shared_ptr<TableFactory> pfac;
        boost::shared_ptr<Table> ptbl;

        pfac = boost::shared_ptr<TableFactory>(new NodeInfoFactory());
        ptbl = pfac->CreateTable();
        ptbl->ShowTable();
        ptbl.reset();
        pfac.reset();

        pfac = boost::shared_ptr<TableFactory>(new UserInfoFactory());
        ptbl = pfac->CreateTable();
        ptbl->ShowTable();
        return 0;
}
