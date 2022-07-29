// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Sprite.hpp"
#include "TextureHandler.hpp"

// constructor
Sprite::Sprite(
	SDL_Rect dest,
	std::shared_ptr <Image> img,
	std::shared_ptr <Entity> entity
) {
	this->img = img;
	this->position = dest;
	init <Sprite>(entity);
};

/// consturctors & assigners
//// move constructor
//Sprite::Sprite (Sprite&& obj) :
//
//// copy constructor
//Sprite::Sprite(const Sprite& obj) :
//	texture(obj.texture),
//	srcRect(obj.srcRect),
//	position(obj.position)
//{
//	if (obj.getEntity() != nullptr)
//		this->init <Sprite>(obj.getEntity());
//};
//
//// sprite copy assignment constructor
//Sprite& Sprite::operator=(const Sprite& obj) {
//	texture = obj.texture;
//	srcRect = obj.srcRect;
//	position = obj.position;
//	return *this;
//}
//
//// sprite move assignment constructor
//Sprite& Sprite::operator=(Sprite&& obj) noexcept {
//	texture = obj.texture;
//	srcRect = obj.srcRect;
//	position = obj.position;
//	return *this;
//}

// render
void Sprite::render() {
	SDL_RenderCopy(
		game::renderer.get ( ),
		&this->img->getTexture(),
		&this->img->size,
		&this->position
	);
}

// set texture
void Sprite::setImage (std::shared_ptr <Image> img) {
	this->img = img;
}
