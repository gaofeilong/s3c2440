#ifndef _COMPANY_H_
#define _COMPANY_H_
#include <string>
#include <list>
#include <stdio.h>

class Company {
public:
        Company(const std::string &name):m_Name(name) {}
        virtual ~Company() {}
public:
        virtual void Show() {}
        virtual void AddDepartment(Company *dep) {}
protected:
        const std::string m_Name;
};

class ConcreteComany: public Company {
public:
        ConcreteComany(const std::string &name):Company(name) {}
        ~ConcreteComany() {}
public:
        void Show()
        {
                printf("{company[%s]}\n", m_Name.c_str());
                std::list<Company *>::iterator it;
                for (it = m_Leaves.begin(); it != m_Leaves.end(); ++it) {
                        (*it)->Show(); 
                }
        }

        void AddDepartment(Company *dep)
        {
                m_Leaves.push_back(dep);
        }
private:
        std::list<Company *> m_Leaves;
};

class Department: public Company {
public:
        Department(const std::string &name):Company(name) {}
        ~Department() {}
public:
        void Show()
        {
                printf("{department[%s]}\n", m_Name.c_str());
        }
};

#endif  //_COMPANY_H_
