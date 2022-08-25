#pragma once

#include "Game.hpp"
#include "imageObject.hpp"

class TextureHandler {
public:
    static std::unique_ptr <Image> loadTexture(const char* path);
};