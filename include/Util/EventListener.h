#pragma once
#include <Util/OpQueue.h>
#include <Util/Singleton.h>
#include <functional>
#include <map>
namespace KTKR {
class EventListener : public Singleton<EventListener> {
   public:
    enum Event_Type {
        // KEY = 0x00000000 ~ 0x0000FFFF

        KEYBOARD_PRESS = 0x00010000,
        KEYBOARD_REPEAT = 0x00020000,
        KEYBOARD_RELEASE = 0x00040000,
        KEYBOARD = KEYBOARD_PRESS | KEYBOARD_REPEAT | KEYBOARD_RELEASE,

    };

    EventListener& bind(size_t event, const std::function<void()>& op);
    void response(size_t event);

   private:
    EventListener(const EventListener&) = delete;
    EventListener& operator=(const EventListener&) = delete;
    std::map<size_t, Ptr<OpQueue>> listenerList;
};

}  // namespace KTKR
