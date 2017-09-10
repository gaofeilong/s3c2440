#ifndef _GROUPBUG_H_
#define _GROUPBUG_H_

#include <list>
#include <stdio.h>
#include <boost/shared_ptr.hpp>

class GroupBuy;
class Mail
{
public:
        Mail(std::string user):m_User(user) {}
        virtual ~Mail() {};

public:
        virtual void Update() {}
        virtual void Attach(boost::shared_ptr<GroupBuy> pgb)
        {
                m_GroupBuy = pgb; 
        }

protected:
        boost::shared_ptr<GroupBuy> m_GroupBuy;
        std::string m_User;
};

class GroupBuy {
public:
        GroupBuy() {}
        virtual ~GroupBuy() {}
        virtual void Notify()
        {
                std::list< boost::shared_ptr<Mail> >::iterator lmIter;
                for (lmIter = m_MailList.begin(); lmIter != m_MailList.end();
                                        ++lmIter) {
                        (*lmIter)->Update(); 
                }
        }
        
        virtual void Attach(boost::shared_ptr<Mail> pmail)
        {
                m_MailList.push_back(pmail); 
        }

        virtual void SetItem(const std::string item)
        {
                m_NewItem = item; 
        }

        virtual std::string GetItem()
        {
                return m_NewItem; 
        }

protected:
        std::string m_NewItem;

private:
        std::list< boost::shared_ptr<Mail> > m_MailList;
};

class StickyRice: public GroupBuy {
public:
        StickyRice() {}
        ~StickyRice() {}
public:
        virtual void SetItem(const std::string item)
        {
                m_NewItem = "sticky rice: " + item; 
        }
};

class NetEase: public Mail {
public:
        NetEase(const std::string user):Mail(user) {}
        ~NetEase() {}
public:
        virtual void Update()
        {
                printf("send to netease mail: %s, massage is %s\n", 
                                m_User.c_str(), m_GroupBuy->GetItem().c_str());
        }
};

class QQ: public Mail {
public:
        QQ(const std::string user):Mail(user) {}
        ~QQ() {}
public:
        virtual void Update()
        {
                printf("send to tencent mail: %s, massage is %s\n", 
                                m_User.c_str(), m_GroupBuy->GetItem().c_str());
        }
};

#endif  //_GROUPBUG_H_
