#pragma once
#include <type_traits>
namespace KTKR {
template <typename T, typename = std::enable_if<std::is_class<T>::value>>
class Singleton {
   public:
    static T* getInstance() noexcept {
        static T* instance = new T;
        return instance;
    }

   protected:
    Singleton() = default;
    virtual ~Singleton() = default;

   private:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

};  // namespace KTKR

}  // namespace KTKR
