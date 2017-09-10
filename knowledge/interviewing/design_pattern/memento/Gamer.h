#ifndef _GAMER_H_
#define _GAMER_H_
#include <stdio.h>

class State {
public:
        State(unsigned int v = 100, unsigned int m = 100, unsigned int e = 0):
                m_Vitality(v), m_Magic(m), m_Experience(e)
        {}
public:
        void Show()
        {
                printf("vitality: %d\n", m_Vitality);
                printf("magic: %d\n", m_Magic);
                printf("experience: %d\n", m_Experience);
        }

        void IncreaseExperience()
        {
                m_Experience++; 
        }
        
private:
        unsigned int m_Vitality;
        unsigned int m_Magic;
        unsigned int m_Experience;
};

class Gamer {
public:
        State GetState() { return m_State; }
        void SetState(const State &s) { m_State = s; }
        void ShowState() { m_State.Show(); }
        void Work() { m_State.IncreaseExperience(); }
private:
        State m_State;
};

class Saver {
public:
        void Save(State s)
        {
                m_State = s; 
                printf("save state to file\n");
        }

        State Load()
        {
                printf("load state from file\n");
                return m_State; 
        }
private:
        State m_State;
};

#endif  //_GAMER_H_
