#include <LOGL/Texture.h>
#include <Util/Image.h>
#include <glad/glad.h>
#include <iostream>
using namespace LOGL;
using namespace KTKR;
using namespace std;
Texture::Texture(const std::string& path, bool flip) : ID(0), type(TEXTURE_2D) {
    Load(path, flip);
}

Texture::Texture(std::vector<std::string> cubeMapFiles)
    : ID(0), type(TEXTURE_CUBE_MAP) {
    Load(cubeMapFiles);
}

Texture::Texture(size_t width, size_t height) : type(TEXTURE_2D) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
    type = TEXTURE_2D;
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
    // 对于含有alpha通道的图像，为了防止出现边缘问题，使用以下方案：
    if (nrComponents == 4) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

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
    return true;
}

bool Texture::Load(std::vector<std::string> cubeMapFiles,
                   bool gammaCorrection) {
    if (IsValid()) {
        cout << "ERROR: The texture is valid already." << endl;
        return false;
    }
    if (cubeMapFiles.size() != 6) {
        cout << "ERROR: The cubemap format is valid already." << endl;
        return false;
    }
    type = TEXTURE_CUBE_MAP;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
    unsigned int i = 0;
    for (auto& path : cubeMapFiles) {
        Image img(path.c_str());
        if (!img.isValid()) {
            cout << "ERROR: Texture [" << path.c_str() << "] load failed"
                 << endl;
            return false;
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + (i++), 0, GL_RGB,
                     img.getWidth(), img.getHeight(), 0, GL_RGB,
                     GL_UNSIGNED_BYTE, img.getData());
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

bool Texture::setUnit(GLuint unit) const {
    if (!IsValid())
        return false;

    glActiveTexture(GL_TEXTURE0 + unit);
    if (TEXTURE_2D == type)
        glBindTexture(GL_TEXTURE_2D, ID);
    else if (TEXTURE_CUBE_MAP == type)
        glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
    return true;
}
