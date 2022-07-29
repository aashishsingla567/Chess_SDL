#pragma once

#include "game.hpp"
#include "imageObject.hpp"

class TextureHandler {
public:
    static std::unique_ptr <Image> loadTexture(const char* path);
};

