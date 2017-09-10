#include "Os.h"
int main()
{
        Os *los = new Linux();
        Os *wos = new Windows();
        Creater c;
        c.Create(wos);
        c.Create(los);
        return 0;
}
