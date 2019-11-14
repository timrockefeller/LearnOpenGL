#pragma once
#include <Util/Operation.h>
#include <list>

namespace KTKR {
template <typename T>
using Ptr = std::shared_ptr<T>;

class OpQueue {
   public:
    OpQueue();
    ~OpQueue();
    OpQueue& operator<<(const Ptr<Operation> & op);
    OpQueue& operator<<(Operation* op);
    OpQueue& operator<<(const std::function<void()>& op);
    std::list<Ptr<Operation>> queue;
    void Run();
    bool isHold();

    template <typename T>
    static Ptr<T> toPtr(T* op) {
        return Ptr<T>(op, [&](T* op_) { delete op_; });
    }

   protected:
    bool hold;

   private:
    OpQueue(const OpQueue&) = delete;
    OpQueue& operator=(const OpQueue&) = delete;
};

}  // namespace KTKR
