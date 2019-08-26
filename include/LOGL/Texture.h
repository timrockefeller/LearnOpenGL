#pragma once
#include <glad/glad.h>
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
    bool setUnit(GLuint unit = 0) const;
    GLuint GetID() const;
   private:
    GLuint ID;
};

}  // namespace LOGL
