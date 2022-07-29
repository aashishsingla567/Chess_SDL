#pragma once

#include "Game.hpp"

class Image {
	// an Image cannot be changed after construction
public:
	const SDL_Rect size; // src rect for full Image load
private:
	const sdl::shared_ptr <SDL_Texture> texture;
public:
	// consturctor
	Image(SDL_Rect size, sdl::shared_ptr <SDL_Texture> texture)
		: size(size), texture(texture) {};
	// get texture
	SDL_Texture& getTexture() const {
		return *this->texture;
	}
};