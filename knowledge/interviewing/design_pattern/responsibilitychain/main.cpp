#include "Manager.h"

int main()
{
        Person *cm = new Chairman("zy");
        Person *mg = new Manager("wsp", cm);
        Person *tl = new TeamLeader("zhw", mg);
        Person *tm = new Teamer("gfl", tl);

        tm->Request(5500);


        return 0;
}
