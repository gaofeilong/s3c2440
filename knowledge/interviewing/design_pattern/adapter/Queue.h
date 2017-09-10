#ifndef _DEQUE_H_
#define _DEQUE_H_
#include <stdio.h>

class Deque {
public:
        void push_back(int x) { printf("deque push_back(%d)\n", x); }
        void pop_back() { printf("deque pop_back()\n"); }
        void push_front(int x) { printf("deque push_front(%d)\n", x); }
        void pop_front() { printf("deque pop_front()\n"); }
};

class Sequence {
public:
        virtual ~Sequence() {}
public:
        virtual void push(int x) = 0;
        virtual void pop() = 0;
};

class Stack: public Sequence {
public:
        void push(int x) { m_Deque.push_back(x); }
        void pop() { m_Deque.pop_back(); }
private:
        Deque m_Deque;
};

class Queue: public Sequence {
public:
        void push(int x) { m_Deque.push_back(x); }
        void pop() { m_Deque.pop_front(); }
private:
        Deque m_Deque;
};

#endif  //_DEQUE_H_
