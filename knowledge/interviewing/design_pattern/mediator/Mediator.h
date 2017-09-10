#ifndef _MEDIATOR_H_
#define _MEDIATOR_H_
#include <stdio.h>
#include <vector>

class Mediator;
class Person {
public:
        Person(const char *name): m_Name(name) {}
        virtual ~Person() {}
public:
        virtual void SetMediator(Mediator *pm) { m_Mediator = pm; }
        virtual void SendMessage(const char *msg)  = 0;
        const char *GetName() { return m_Name; }
protected:
        Mediator *m_Mediator;
private:
        const char *m_Name;
};

class Mediator {
public:
        void SetRenter(Person *p)
        {
                m_Renters.push_back(p); 
        }

        void SetLandlord(Person *p)
        {
                m_Landlords.push_back(p); 
        }

        void SendToLandlord(const char *msg)
        {
                std::vector<Person *>::iterator it;
                for (it = m_Landlords.begin(); it != m_Landlords.end(); ++it) {
                        printf("send message[%s] to landlord[%s]\n", 
                                                msg, (*it)->GetName());
                }
        }

        void SendToRenter(const char *msg)
        {
                std::vector<Person *>::iterator it;
                for (it = m_Renters.begin(); it != m_Renters.end(); ++it) {
                        printf("send message[%s] to renter[%s]\n", 
                                                msg, (*it)->GetName());
                }
        }
private:
        std::vector<Person *> m_Renters;
        std::vector<Person *> m_Landlords;
};

class Renter: public Person {
public:
        Renter(const char *name): Person(name) {}
public:
        void SetMediator(Mediator *pm) 
        { 
                m_Mediator = pm; 
                m_Mediator->SetRenter(this);
        }

        void SendMessage(const char *msg)
        {
                m_Mediator->SendToLandlord(msg); 
        }
};

class Landlord: public Person {
public:
        Landlord(const char *name): Person(name) {}
public:
        void SetMediator(Mediator *pm) 
        { 
                m_Mediator = pm; 
                m_Mediator->SetLandlord(this);
        }

        void SendMessage(const char *msg)
        {
                m_Mediator->SendToRenter(msg); 
        }
};

#endif  //_MEDIATOR_H_
