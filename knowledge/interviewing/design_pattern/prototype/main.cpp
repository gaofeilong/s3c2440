#include "Config.h"

int main()
{
        Config *c = new IniConfig("123");
        c->Show();
        Config *c1 = c->Clone();
        c1->Show();

        Config *c2 = new IniConfig("321");
        c2->Show();
        Config *c3 = c->Clone();
        c2->Show();
        return 0;
}
