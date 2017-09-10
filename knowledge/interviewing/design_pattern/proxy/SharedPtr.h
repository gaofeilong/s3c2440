#ifndef _SHAREDPTR_H_
#define _SHAREDPTR_H_

template<typename T>
class SharedPtr {
public:
        SharedPtr(T *p = 0): m_P(p), m_Count(new size_t(1)) {}
        SharedPtr(const SharedPtr &rp): m_P(rp.m_P), m_Count(rp.m_Count) 
        {
                ++*m_Count;
        }
        ~SharedPtr() { DesCount(); }
        SharedPtr &operator=(const SharedPtr &r)
        {
                if (&r != this) {
                        DesCount(); 
                        m_P = r.m_P;
                        m_Count = r.m_Count;
                        ++*m_Count;
                } 
                return *this;
        }

public:
        T *operator->() { return m_P; }
        const T *operator->() const { return m_P; }
        T &operator*() { return *m_P; }
        const T &operator*() const {return *m_P; }
        size_t GetCount() { return *m_Count; }

private:
        void DesCount()
        {
                if (--*m_Count == 0) {
                        delete m_P;
                        delete m_Count;
                } 
        }

private:
        T *m_P;
        size_t *m_Count;
};

#endif  //_SHAREDPTR_H_
