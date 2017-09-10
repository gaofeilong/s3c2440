#include "Company.h"
int main()
{
        Company *c = new ConcreteComany("huawei");
        Company *d1 = new Department("development1");
        Company *d2 = new Department("test1");
        c->AddDepartment(d1);
        c->AddDepartment(d2);

        Company *c1 = new ConcreteComany("huawei_jinan");
        Company *d3 = new Department("development2");
        Company *d4 = new Department("test2");
        c->AddDepartment(c1); 
        c1->AddDepartment(d3);
        c1->AddDepartment(d4);

        c->Show();
}
