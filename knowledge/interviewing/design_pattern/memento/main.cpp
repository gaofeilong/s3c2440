#include "Gamer.h"

int main()
{
        Gamer gm;
        Saver sv;

        gm.ShowState();
        printf("\n");
        for (int i = 0; i < 10; i++) {
                gm.Work(); 
        }
        gm.ShowState();
        printf("\n");
        sv.Save(gm.GetState());
        gm.Work();
        gm.ShowState();
        printf("\n");
        gm.SetState(sv.Load());
        gm.ShowState();
        printf("\n");
        return 0;
}
