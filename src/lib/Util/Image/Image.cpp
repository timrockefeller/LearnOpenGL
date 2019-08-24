#define STB_IMAGE_IMPLEMENTATION
#define STBI_WINDOWS_UTF8

#include <Util/Image.h>
#include <Util/stb_image.h>

using namespace KTKR;
using namespace std;

Image::Image() : data(NULL), width(0), height(0), channels(0) {}
Image::~Image() {
    Free();
}
Image::Image(const char* imagePath_,bool flip,int req_comp) : width(0), height(0), channels(req_comp) {
    Load(imagePath_,flip, req_comp);
}
void Image::Load(const char* imagePath_,bool flip, int req_comp){
    //Free();
    stbi_set_flip_vertically_on_load(flip);
    if (imagePath_) {
        data = stbi_load(imagePath_, &width, &height, &channels, req_comp);
        imagePath = imagePath_;
    }
}
void Image::Free(){ 
    // TODO
    stbi_image_free(data);
    data = NULL;
}

bool Image::isValid() {
    return data != NULL;
}
int Image::getWidth() {
    return width;
}
int Image::getHeight() {
    return height;
}
int Image::getChannels() {
    return channels;
}
uByte* Image::getData() {
    return data;
}
