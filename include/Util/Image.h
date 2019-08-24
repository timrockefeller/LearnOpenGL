#pragma once
#include <string>
namespace KTKR {
typedef unsigned char uByte;
class Image {
   public:
    Image(const char* imagePath_,bool flip = false, int req_comp = 0);
    Image();
    ~Image();
    int getWidth();
    int getHeight();
    int getChannels();
    uByte * getData();
    bool isValid();
    void Load(const char* imagePath_,bool flip,int req_comp);
void Free();
   private:
    
    std::string imagePath;
    uByte* data;
    int width,height,channels;
};
}  // namespace KTKR
