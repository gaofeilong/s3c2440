#include "Mediator.h"

int main()
{
        Renter r1("g1");
        Renter r2("g2");
        Landlord l1("z1");
        Landlord l2("z2");
        Mediator m;

        r1.SetMediator(&m);
        r2.SetMediator(&m);
        l1.SetMediator(&m);
        l2.SetMediator(&m);

        r1.SendMessage("I want rent a house!!!");
        r2.SendMessage("I want rent a house too!!!");

        l1.SendMessage("I have a house to rend!");
        l1.SendMessage("I have a house to rend!");

        return 0;
}
