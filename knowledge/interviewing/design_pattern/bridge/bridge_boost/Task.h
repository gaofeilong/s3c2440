#ifndef _TASK_H_
#define _TASK_H_

#include <stdio.h>
#include <boost/shared_ptr.hpp>

class Log {
public:
        Log() {}
        virtual ~Log() {}
public:
        virtual void WriteLog() = 0;
};

class FileLog: public Log {
public:
        FileLog() {}
        ~FileLog() {}
public:
        void WriteLog() { printf("write log to file\n"); }
};

class ConsoleLog: public Log {
public:
        ConsoleLog() {}
        ~ConsoleLog() {}
public:
        void WriteLog() { printf("write log to console\n"); }
};

class Task {
public:
        Task() {}                
        virtual ~Task() {}
public:
        virtual void WriteTaskLog(boost::shared_ptr<Log> log) = 0;
};

class ArchiveTask: public Task {
public:
        ArchiveTask() {}
        ~ArchiveTask() {}
public:
        void WriteTaskLog(boost::shared_ptr<Log> log)
        {
                printf("Task log: ");
                log->WriteLog(); 
        }
};

class DatabaseTask: public Task {
public:
        DatabaseTask() {}
        ~DatabaseTask() {}
public:
        void WriteTaskLog(boost::shared_ptr<Log> log)
        {
                printf("Database log: ");
                log->WriteLog(); 
        }
};

#endif  //_TASK_H_
