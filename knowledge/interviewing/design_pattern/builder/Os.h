#ifndef _OS_H_
#define _OS_H_
#include <stdio.h>

class Os {
public:
        virtual ~Os() {}
public:
        virtual void MemoryManagement() = 0;
        virtual void Driver() = 0;
        virtual void FileSystem() = 0;
        virtual void ProcessManagement() = 0;
};

class Linux: public Os {
public:
        void MemoryManagement() { printf("linux init memory module\n"); }
        void Driver() { printf("linux init driver\n"); }
        void FileSystem() { printf("linux init filesystem\n"); }
        void ProcessManagement() { printf("linux init process management\n"); }
};

class Windows: public Os {
public:
        void MemoryManagement() { printf("windows init memory module\n"); }
        void Driver() { printf("windows init driver\n"); }
        void FileSystem() { printf("windows init filesystem\n"); }
        void ProcessManagement() { printf("windows init process management\n"); }
};

class Creater {
public:
        void Create(Os *os)
        {
                os->MemoryManagement(); 
                os->Driver();
                os->FileSystem();
                os->ProcessManagement();
        }
};

#endif  //_OS_H_
