#include <boost/shared_ptr.hpp>
#include "Queue.h"

int main()
{
        boost::shared_ptr<Sequence> queue(new Queue());
        Sequence *stack = new Stack();

        queue->push(1);
        queue->pop();
        stack->push(1);
        stack->pop();

        return 0;
}
