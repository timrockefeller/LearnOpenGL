#include <Util/Operation.h>

using namespace KTKR;

using namespace std;

Operation::Operation(const std::function<void()>& op_, bool isHold_)
    : op(op_), hold(isHold_) {}

bool Operation::isHold() {
    return hold;
}

void Operation::Run() {
    if (op != NULL)
        op();
}
