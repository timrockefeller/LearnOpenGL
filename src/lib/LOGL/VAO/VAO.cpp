#include <LOGL/VAO.h>
#include <glad/glad.h>

using namespace std;
using namespace LOGL;


VAO::VAO(float const* data,
         size_t dataSize,
         const std::vector<unsigned int>& attrLen) {
    if (data == nullptr || dataSize == 0 || attrLen.size() == 0) {
        isValid = 0;
        ID = 0;
        return;
    }
    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    unsigned int patchLen = 0;
    for (auto& len : attrLen)
        patchLen += len;
    attrNum = attrLen.size();
    for (int i = 0, cur = 0; i < attrLen.size(); i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(0, attrLen[i], GL_FLOAT, GL_FALSE,
                              patchLen * sizeof(float),
                              (void*)(cur * sizeof(float)));
        cur += attrLen[i];
    }
    pointNum = dataSize / (sizeof(float) * patchLen);
    hasIndex = false;
    isValid = true;
}
// VAO::~VAO(){
//     glDeleteVertexArrays(1, &ID);
//     glDeleteBuffers(1, &VBO);
// }
unsigned int VAO::GetID() const {
    return ID;
}
unsigned int VAO::GetAttrNum() const {
    return attrNum;
}
bool VAO::IsValid() const {
    return isValid;
}
bool VAO::Use() const {
    if (!IsValid()) {
        return false;
    }
    glBindVertexArray(ID);
    return true;
}
bool VAO::Draw() const {
    if (!IsValid()) {
        return false;
    }
    Use();
    glDrawArrays(GL_TRIANGLES, 0, pointNum);
    return true;
}
