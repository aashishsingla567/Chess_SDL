// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "gameEntities.hpp"
#include "TextureHandler.hpp"

// TODO :: make all the methods in the above classes

// Tile constructor
Tile::Tile (
	int color, 
	SDL_Rect position, 
	std::shared_ptr <Image> img) 
	: color(color), position(position), img(img) {
}

// Tile destructor
Tile::~Tile() {
}

// getColor method
int Tile::getColor() {
	return color;
}

// getPosition method
SDL_Rect Tile::getPosition() {
	return position;
}

// getImg method
std::shared_ptr<Image> Tile::getImg() {
	return img;
}

// Piece constructor
Piece::Piece(
	const int color,
	const int name,
	const std::shared_ptr <Image> img) 
	:
	color(color),
	name(name),
	img(img) 
{};

// Piece destructor
Piece::~Piece() {
}

// getColor method
int Piece::getColor() {
	return color;
}

// getName method
int Piece::getName() {
	return name;
}

// getImg method
std::shared_ptr<Image> Piece::getImg() {
	return img;
}