#pragma once
#include <glad/glad.h>
#include <string>
#include <vector>
namespace LOGL {
class Texture {
    enum Texture_Type { TEXTURE_2D, TEXTURE_CUBE_MAP };

   public:
    Texture(const std::string& path, bool flip = false);

    Texture(size_t width, size_t height);

    // Cube Map
    Texture(std::vector<std::string> cubeMapFiles);
    //~Texture();

    bool IsValid() const;

    bool Load(const std::string& path,
              bool flip = false,
              bool gammaCorrection = false  // TODO
    );
    bool Load(std::vector<std::string> cubeMapFiles,
              bool gammaCorrection = false);

    bool setUnit(GLuint unit = 0) const;
    GLuint GetID() const;

    Texture_Type tex_type;
    std::string type;
    std::string path;

   private:
    GLuint ID;
};

}  // namespace LOGL
