#pragma once
#include <LOGL/Texture.h>
namespace LOGL {
class FBO {
   public:
    FBO(size_t width, size_t height);
    ~FBO();

    void Use();

    static void UseDefault();
    static const unsigned int DefaultBuffer = 0;

    unsigned int GetID() const;
    Texture* GetTexture() const;
    FBO& operator=(const FBO& fbo) = delete;

   private:
    bool IsComplete() const;
    unsigned int ID;
    Texture* colorTexture;
    size_t width;
    size_t height;
};
}  // namespace LOGL
