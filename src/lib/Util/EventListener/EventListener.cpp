#include <Util/EventListener.h>
using namespace KTKR;
using namespace std;

EventListener& EventListener::bind(size_t event,
                                   const std::function<void()>& op) {
    if (listenerList.find(event) == listenerList.end())
        listenerList[event] = OpQueue::toPtr(new OpQueue);
    listenerList[event]->operator<<(op);
    return *this;
}

void EventListener::response(size_t event) {
    auto it = listenerList.find(event);
    if (it != listenerList.end())
        it->second->Run();
}
