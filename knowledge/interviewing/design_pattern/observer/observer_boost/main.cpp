#include "GroupBuy.h"

int main()
{
        boost::shared_ptr<GroupBuy> pbuy(new StickyRice());
        boost::shared_ptr<Mail> netease(new NetEase("gaofeilonglcu@163.com"));
        boost::shared_ptr<Mail> qq(new QQ("841243496@qq.com"));

        pbuy->SetItem("a swim");
        pbuy->Attach(netease);
        pbuy->Attach(qq);
        qq->Attach(pbuy);
        netease->Attach(pbuy);
        pbuy->Notify();
        return 0;
}
