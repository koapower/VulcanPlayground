#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ImageData TextureLoader::loadImage(const std::string& path) {
    ImageData img;
    img.pixels = stbi_load(path.c_str(), &img.width, &img.height, &img.channels, STBI_rgb_alpha);
    if (img.pixels) {
        img.size = img.width * img.height * 4; // force STBI_rgb_alpha
    }
    return img;
}

ImageData TextureLoader::loadImageFromMemory(const unsigned char* data, int len) {
    ImageData img;
    img.pixels = stbi_load_from_memory(data, len, &img.width, &img.height, &img.channels, STBI_rgb_alpha);
    if (img.pixels) {
        img.size = img.width * img.height * 4;
    }
    return img;
}

void ImageData::free() {
    if (pixels) {
        stbi_image_free(pixels);
        pixels = nullptr;
    }
}