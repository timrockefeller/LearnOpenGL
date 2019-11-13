#pragma once
#include <glad/glad.h>
#include <string>

namespace LOGL {
class Texture {
   public:
    Texture(const std::string& path, bool flip = false);

    Texture(size_t width, size_t height);

    //~Texture();

    bool IsValid() const;

    bool Load(const std::string& path,
              bool flip = false,
              bool gammaCorrection = false  // TODO
    );
    bool setUnit(GLuint unit = 0) const;
    GLuint GetID() const;

    std::string type;
    std::string path;

   private:
    GLuint ID;
};

}  // namespace LOGL
