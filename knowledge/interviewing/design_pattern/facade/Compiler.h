#ifndef _COMPILER_H_
#define _COMPILER_H_
#include <stdio.h>

class Scanner {
public:
        void Scan(void) { printf("scan\n"); }
};

class Parser {
public:
        void Parse (void) { printf("syntax analyse\n"); }
};

class GenMidCode {
public:
        void GenCode(void) { printf("gen mid code\n"); }
};

class GenMachineCode {
public:
        void GenCode(void) { printf("gen machine code\n"); }
};

class Compiler {
public:
        void Compile(void)
        {
                Scanner s;
                s.Scan();
                Parser p;
                p.Parse();
                GenMidCode midCode;
                midCode.GenCode(); 
                GenMachineCode machineCode;
                machineCode.GenCode();
        }
};

#endif  //_COMPILER_H_
