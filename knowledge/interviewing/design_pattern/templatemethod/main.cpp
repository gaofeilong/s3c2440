#include "Database.h"

int main()
{
        Table t;
        DatabaseOperation *dp;

        dp = new OracleOperation();
        dp->GetTable(&t);
        delete dp;

        dp = new MysqlOperation();
        dp->GetTable(&t);
        delete dp;

        return 0;
}
