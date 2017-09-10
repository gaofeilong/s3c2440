#ifndef _PROTOTYPE_H_
#define _PROTOTYPE_H_
#include <stdio.h>
#include <string.h>

class Config {
public:
        virtual ~Config() {} 
public:
        virtual Config *Clone() = 0;
        virtual void Show() = 0;
protected:
        char *m_Data;
};

class IniConfig: public Config {
public:
        IniConfig(const char *s)
        {
                if (s) {
                        m_Data = new char (strlen(s) + 1);
                        strcpy(m_Data, s);
                } else {
                        m_Data = new char[1]; 
                        m_Data[0] = '\0';
                } 
        }

        IniConfig(const IniConfig &r)
        {
                m_Data = new char[strlen(r.m_Data) + 1];
                strcpy(m_Data, r.m_Data);
        }

        ~IniConfig()
        {
                delete [] m_Data; 
        }
public:
        Config *Clone()
        {
                return new IniConfig(*this); 
        }
        void Show()
        {
                printf("Ini config: %s\n", m_Data); 
        }
};

class XmlConfig: public Config {
public:
        XmlConfig(const char *s)
        {
                if (s) {
                        m_Data = new char (strlen(s) + 1);
                        strcpy(m_Data, s);
                } else {
                        m_Data = new char[1]; 
                        m_Data[0] = '\0';
                } 
        }

        XmlConfig(const XmlConfig &r)
        {
                m_Data = new char[strlen(r.m_Data) + 1];
                strcpy(m_Data, r.m_Data);
        }

        ~XmlConfig()
        {
                delete [] m_Data; 
        }
public:
        XmlConfig *Clone()
        {
                return new XmlConfig(*this); 
        }
        void Show()
        {
                printf("Xml config: %s\n", m_Data); 
        }
};

#endif  //_PROTOTYPE_H_
