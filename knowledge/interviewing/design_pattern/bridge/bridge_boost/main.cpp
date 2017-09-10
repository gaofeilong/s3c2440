#include "Task.h"

int main()
{
        Task *ptask;
        boost::shared_ptr<Log> log;

        ptask = new ArchiveTask();
        log = boost::shared_ptr<Log>(new FileLog);
        ptask->WriteTaskLog(log);
        delete ptask;

        ptask = new DatabaseTask();
        log = boost::shared_ptr<Log>(new ConsoleLog);
        ptask->WriteTaskLog(log);
        delete ptask;

        return 0;
}
