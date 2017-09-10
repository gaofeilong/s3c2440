#include <iostream>
#include "SharedPtr.h"

int main()
{
        SharedPtr<int> p(new int(10));
        printf("%d, count=%d\n", *p, p.GetCount());

        SharedPtr<int> p1(new int(100));
        printf("%d, count=%d\n", *p1, p1.GetCount());

        SharedPtr<int> p2(p1);
        printf("%d, count=%d\n", *p2, p2.GetCount());

        p1 = p;
        printf("%d, count=%d\n", *p, p.GetCount());
        printf("%d, count=%d\n", *p1, p1.GetCount());

        return 0;
}
