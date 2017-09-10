#ifndef  _MANAGER_H_
#define _MANAGER_H_
#include <stdio.h>
#include <string>

class Person {
public:
        Person(const std::string &name): m_Name(name) {}
        Person(const std::string &name, Person *boss): 
                m_Name(name), m_Boss(boss) {}
        virtual ~Person() {}

public:
        virtual void DealRequest(const std::string &name, int num) {}
        virtual void Request(int num) {}

protected:
        std::string m_Name;
        Person *m_Boss;
};

class Chairman: public Person {
public:
        Chairman(const std::string &name): Person(name) {}

public:
        void DealRequest(const std::string &name, int num) 
        {
                if (num <= 5000) {
                        printf("%s say: \"%s's wage can rise %d\"\n", 
                                        m_Name.c_str(), name.c_str(), num);
                } else {
                        printf("%s say: \"no, %s's wage can't rize so high\"\n",
                                        m_Name.c_str(), name.c_str());
                }
        }
};

class Manager: public Person {
public:
        Manager(const std::string &name, Person *boss): 
                Person(name, boss) {}

public:
        void DealRequest(const std::string &name, int num) 
        {
                if (num <= 3000) {
                        printf("%s say: \"%s's wage can rise %d\"\n", 
                                        m_Name.c_str(), name.c_str(), num);
                } else {
                        printf("%s say: \"no, %s, I cannot make a decision\"\n", 
                                        m_Name.c_str(), name.c_str());
                        m_Boss->DealRequest(name, num);
                }
        }
};

class TeamLeader: public Person {
public:
        TeamLeader(const std::string &name, Person *boss): 
                Person(name, boss) {}

public:
        void DealRequest(const std::string &name, int num) 
        {
                if (num <= 1000) {
                        printf("%s say: \"%s's wage can rise %d\"\n", 
                                        m_Name.c_str(), name.c_str(), num);
                } else {
                        printf("%s say: \"no, %s, I cannot make a decision\"\n", 
                                        m_Name.c_str(), name.c_str());
                        m_Boss->DealRequest(name, num);
                }
        }
};

class Teamer: public Person {
public:
        Teamer(const std::string &name, Person *boss): 
                Person(name, boss) {}

public:
        void Request(int num) 
        {
                m_Boss->DealRequest(m_Name, num);
        }
};

#endif  //_MANAGER_H_
