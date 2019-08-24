#pragma once
#include <string>

namespace LOGL {
class Texture {
   public:
    Texture(const std::string& path, bool flip = false);

    //~Texture();

    bool IsValid() const;

    bool Load(const std::string& path,
              bool flip = false,
              bool gammaCorrection = false  // TODO
    );
    bool setUnit(unsigned int unit = 0) const;
    unsigned int GetID() const;
   private:
    unsigned int ID;
};

}  // namespace LOGL
