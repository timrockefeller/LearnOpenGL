#include <Util/OpQueue.h>
#include <vector>
using namespace KTKR;
using namespace std;

OpQueue::OpQueue() : hold(true), queue(std::list<Ptr<Operation>>()) {}

OpQueue& OpQueue::operator<<(Ptr<Operation> op) {
    if (op != NULL) {
        queue.push_back(op);
    }
    return *this;
}
OpQueue& OpQueue::operator<<(Operation* op) {
    if (op != NULL) {
        queue.push_back(toPtr(op));
    }
    return *this;
}
OpQueue& OpQueue::operator<<(const std::function<void()>& op) {
    if (op != NULL) {
        queue.push_back(toPtr(new Operation(op)));
    }
    return *this;
}
void OpQueue::Run() {
    vector<list<Ptr<Operation>>::const_iterator> removeIt;
    for (auto it = queue.cbegin(); it != queue.cend(); ++it) {
        (*it)->Run();
        if (!(*it)->isHold())
            removeIt.push_back(it);
    }
    for (int i = removeIt.size() - 1; i >= 0; i--)
        queue.erase(removeIt[i]);

    if (queue.empty())
        hold = false;
}

bool OpQueue::isHold() {
    return hold;
}

template <typename T>
Ptr<T> OpQueue::toPtr(T* op) {
    return Ptr<T>(op, [&](T* op_) { delete op_; });
}

OpQueue::~OpQueue() {
    //clean all
    vector<list<Ptr<Operation>>::const_iterator> removeIt;
    for (auto it = queue.cbegin(); it != queue.cend(); ++it) {
        removeIt.push_back(it);
    }
    for (int i = removeIt.size() - 1; i >= 0; i--)
        queue.erase(removeIt[i]);
}
