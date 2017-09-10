#ifndef _ARCHIVE_H_
#define _ARCHIVE_H_

class State;
class Archive {
public:
        Archive() {}
        ~Archive() {}

public:
        int StartArchive();
        int GetDataCount();
        void GetAchiveState();
        void SetArchiveState(State *state);

private:
        static void *DataCountUp(void *args);

private:
        static int m_DataCount;
        State *m_DataState;
};

class State {
public:
        State() {}
        virtual ~State() {}
public:
        virtual void CurrentState(Archive *arv) = 0;
};

class LastState: public State {
public:
        LastState() {}
        ~LastState() {}
public:
        void CurrentState(Archive *arv);
};

class MidState: public State {
public:
        MidState() {}
        ~MidState() {}
public:
        void CurrentState(Archive *arv);
};

class PreState: public State {
public:
        PreState() {}
        ~PreState() {}
public:
        void CurrentState(Archive *arv);
};

#endif  //_ARCHIVE_H_
