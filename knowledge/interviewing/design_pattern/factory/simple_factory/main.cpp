#include <stdio.h>
#include "Table.h"

int main()
{
        boost::shared_ptr<TableFactory> pfac;
        boost::shared_ptr<Table> ptbl;

        pfac = boost::shared_ptr<TableFactory>(new TableFactory());
        ptbl = pfac->CreateTable(USERINFO);
        ptbl->ShowTable();
        ptbl.reset();

        ptbl = pfac->CreateTable(NODEINFO);
        ptbl->ShowTable();
        return 0;
}
