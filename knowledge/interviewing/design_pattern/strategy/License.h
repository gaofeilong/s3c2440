#ifndef _LICENSE_H_
#define _LICENSE_H_
#include <stdio.h>

class VerifyAlgorithm {
public:
        virtual void Verify() = 0;
};

class TimeVerify: public VerifyAlgorithm {
public:
        void Verify() { printf("check time\n"); }
};

class DataVerify: public VerifyAlgorithm {
public:
        void Verify() { printf("check data\n"); }
};

class LicenseVerify: public VerifyAlgorithm {
public:
        void Verify() { printf("check license\n"); }
};

enum Type{TIME, DATA, LICENSE};

class Verifier {
public:
        void Verify(enum Type t) {
                VerifyAlgorithm *pv;
                switch (t) {
                case TIME: 
                        pv = new TimeVerify();
                        break;
                case DATA:
                        pv = new DataVerify();
                        break;
                case LICENSE:
                        pv = new LicenseVerify();
                        break;
                }
                pv->Verify();
        }
};

#endif  //_LICENSE_H_
