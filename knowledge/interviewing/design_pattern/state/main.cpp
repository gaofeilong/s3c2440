#include <stdio.h>
#include <unistd.h>
#include "Archive.h"


int main()
{
        Archive arv;
        arv.StartArchive();
        for (int i = 0; i <= 5; i++) {
                printf("current archive state is ");
                arv.GetAchiveState();
                sleep(2);
        }
        return 0;
}
