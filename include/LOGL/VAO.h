#pragma once
#include <vector>
namespace LOGL {
class VAO {
   public:
    VAO() = default;
    // struct VBO_DataPatch {
    //     float const* data;
    //     unsigned int dataSize;
    //     unsigned int attrLen;
    // };
    VAO(unsigned int ID,unsigned int num):ID(ID),isValid(true),pointNum(num){}
    VAO(float const * data, size_t dataSize, const std::vector<unsigned int>& attrLen);
    VAO(float const* data,
        unsigned int dataSize,
        const std::vector<unsigned int>& attrLen,
        unsigned int const* index,
        unsigned int indexSize);
    // VAO(const std::vector<VBO_DataPatch>& vec_VBO_DataPatch,
    //     const std::vector<unsigned int>& divisors = std::vector<unsigned int>());
    // VAO(const std::vector<VBO_DataPatch>& vec_VBO_DataPatch,
    //     unsigned int const* index,
    //     unsigned int indexSize,
    //     const std::vector<unsigned int>& divisors = std::vector<unsigned int>());
    ~VAO();

    unsigned int GetID() const;
    unsigned int GetAttrNum() const;
    bool IsValid() const;
    bool Use() const;
    bool Draw() const;
    
   private:
    bool GenBindEBO(unsigned int const* index, unsigned int indexSize);
    //------------
    unsigned int attrNum;
    unsigned int ID;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int pointNum;
    bool hasIndex;
    bool isValid;
};
}  // namespace LOGL
