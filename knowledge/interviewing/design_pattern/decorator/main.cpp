#include "Blog.h"
int main()
{
        Blog *pblog = new SinaBlog();
        BlogDecorator *pd1 = new DarkStyle(pblog);
        BlogDecorator *pd2 = new WithGrass(pd1);
        pblog->Show();
        printf("\n");
        pd1->Show();
        printf("\n");
        pd2->Show();
        printf("\n");
        delete pd2;
        delete pd1;
        delete pblog;

        return 0;
}
