#include <LOGL/FBO.h>
#include <glad/glad.h>
#include <iostream>
using namespace LOGL;
using namespace std;

FBO::FBO(size_t width_, size_t height_) : width(width_), height(height_) {
    glGenFramebuffers(1, &ID);
    Use();

    // create texture
    colorTexture = new Texture(width, height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           colorTexture->GetID(), 0);

    // render buffer
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER, rbo);
    if (!IsComplete())
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!"
                  << std::endl;
    UseDefault();
}

FBO::~FBO() {
    glDeleteFramebuffers(1, &ID);
    delete colorTexture;
}
void FBO::UseDefault() {
    glBindFramebuffer(GL_FRAMEBUFFER, DefaultBuffer);
}
void FBO::Use() {
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

GLuint FBO::GetID() const {
    return ID;
}
Texture* FBO::GetTexture() const {
    return colorTexture;
}
bool FBO::IsComplete() const {
    return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}
