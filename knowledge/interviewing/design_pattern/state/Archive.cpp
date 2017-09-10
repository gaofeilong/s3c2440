#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include "Archive.h"

int Archive::m_DataCount;

int Archive::StartArchive()
{
        int ret;
        pthread_t tid; 
        m_DataState = new PreState();

        ret = pthread_create(&tid, NULL, DataCountUp, NULL);
        assert(ret == 0);
}

int Archive::GetDataCount() 
{ 
        return m_DataCount; 
}

void Archive::GetAchiveState() 
{ 
        m_DataState->CurrentState(this); 
}

void Archive::SetArchiveState(State *state) 
{ 
        m_DataState = state; 
}

void *Archive::DataCountUp(void *args)
{
        for (m_DataCount = 0; m_DataCount <= 10; m_DataCount++) {
                sleep(1);
        }
}

void PreState::CurrentState(Archive *arv)
{
        if (arv->GetDataCount() < 3) {
                printf("just beginning\n"); 
        } else {
                arv->SetArchiveState(new MidState());
                arv->GetAchiveState();
        }
}


void MidState::CurrentState(Archive *arv)
{
        if (arv->GetDataCount() < 6) {
                printf("half pasting\n"); 
        } else {
                arv->SetArchiveState(new LastState());
                arv->GetAchiveState();
        }
}


void LastState::CurrentState(Archive *arv)
{
        printf("reaching end\n"); 
}
