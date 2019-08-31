#pragma once
#include "LStorage.h"
#include "Singleton.h"

namespace KTKR {
template <typename T>
class GStorage final : public Singleton<GStorage<T>>, public LStorage<T> {
    friend class Singleton<GStorage<T>>;

   public:
   private:
    GStorage() = default;
    ~GStorage() = default;
};
}  // namespace KTKR
