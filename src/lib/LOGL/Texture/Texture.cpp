#include <LOGL/Texture.h>
#include <Util/Image.h>
#include <glad/glad.h>
#include <iostream>
using namespace LOGL;
using namespace KTKR;
using namespace std;
Texture::Texture(const std::string& path, bool flip):ID(0) {
    Load(path, flip);
}

bool Texture::IsValid() const {
    return ID != 0;
}

GLuint Texture::GetID() const {
    return ID;
}

bool Texture::Load(const std::string& path, bool flip, bool gammaCorrection) {
    if (IsValid()) {
        cout << "ERROR: The texture is valid already." << endl;
        return false;
    }

    Image img(path.c_str(), flip);
    if (!img.isValid()) {
        cout << "ERROR: Texture [" << path.c_str() << "] load failed" << endl;
        return false;
    }

    GLenum internalFormat;
    GLenum dataFormat;
    int nrComponents = img.getChannels();
    if (nrComponents == 1) {
        internalFormat = GL_RED;
        dataFormat = GL_RED;
    } else if (nrComponents == 3) {
        internalFormat = gammaCorrection ? GL_SRGB : GL_RGB;
        dataFormat = GL_RGB;
    } else if (nrComponents == 4) {
        internalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
        dataFormat = GL_RGBA;
    }

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    // 纹理越界、缩放样式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(          // 绑定纹理信息
        GL_TEXTURE_2D,     // 纹理目标
        0,                 // 多级渐远纹理的级别 （0 为基本级别)
        internalFormat,    // 目标纹理格式
        img.getWidth(),    // width
        img.getHeight(),   // height
        0,                 // 恒为0 (历史遗留问题)
        dataFormat,        // 源图格式
        GL_UNSIGNED_BYTE,  // 源图类型
        img.getData()      // 图像数据
    );
    glGenerateMipmap(GL_TEXTURE_2D);
    img.Free();
}

bool Texture::setUnit(GLuint unit) const {
    if (!IsValid())
        return false;

    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
    return true;
}
