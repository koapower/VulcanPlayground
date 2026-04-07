#pragma once
#include <string>
#include <vector>

// return struct
struct ImageData {
    unsigned char* pixels = nullptr;
    int width = 0;
    int height = 0;
    int channels = 0;
    size_t size = 0;

    void free(); // to release stb memory
};

class TextureLoader {
public:
    // load normal file
    static ImageData loadImage(const std::string& path);

    // load file inside memory
    static ImageData loadImageFromMemory(const unsigned char* data, int len);
};