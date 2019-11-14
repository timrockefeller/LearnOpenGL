#pragma once
#include <functional>
#include <memory>

namespace KTKR {
class Operation {
    friend class OpQueue;

   public:
    Operation(const std::function<void()>& op_, bool isHold_ = true);
    void Run();
    bool isHold();
    void operator()();

   protected:
    std::function<void()> op;
    bool hold;

   private:
    Operation(const Operation&) = delete;
    Operation& operator=(const Operation&) = delete;
};

}  // namespace KTKR
