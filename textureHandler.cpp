// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "TextureHandler.hpp"
#include "Sprite.hpp"

std::unique_ptr <Image> TextureHandler::loadTexture(const char* path) {
    // laod the image from file
    sdl::unique_ptr <SDL_Surface> surface = sdl::make_unique(
        IMG_Load(path)
    );
	
	//  check if the image was loaded correctly
    if (surface == nullptr) {
		throw std::runtime_error(
			"Failed to load texture: " + std::string(path) +
			": " + std::string(IMG_GetError())
		);
	}

    // imporove quality
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

	// create a new image from the loaded surface
    return std::make_unique <Image> (
        Image (
            {0, 0, surface->w, surface->h}, // full Image size
            sdl::make_shared <SDL_Texture> (
                SDL_CreateTextureFromSurface(
                    Game::renderer.get(),
                    surface.get ()
                )
            )
        )
    );
}