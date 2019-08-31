#include <Util/EventListener.h>
#include <Util/OpQueue.h>
#include <memory>
using namespace KTKR;
using namespace std;

EventListener* EventListener::bind(size_t event,
                                   const std::function<void()>& op) {
    if (listenerList.find(event) == listenerList.end()) {
        OpQueue* opq = new OpQueue();
        listenerList[event] =
            std::shared_ptr<OpQueue>(opq, [&](OpQueue* op_) { delete op_; });
    }
    listenerList[event]->operator<<(op);
    return this;
}

void EventListener::response(size_t event) {
    auto it = listenerList.find(event);
    if (it != listenerList.end())
        it->second->Run();
}
