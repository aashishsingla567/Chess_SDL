// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "GameEntities.hpp"
#include "TextureHandler.hpp"

// TODO :: make all the methods in the above classes

// Tile constructor
Tile::Tile(
	int color,
	SDL_Rect position,
	std::shared_ptr <Image> img,
	std::shared_ptr <Piece> piece
) : 
	color (color), position (position), img (img), pieceOnMe (piece)
{};

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

// put a piece on this tile
void Tile::putPiece(std::shared_ptr <Piece> piece) {
	this->pieceOnMe = piece;
}

// Piece constructor
Piece::Piece(
	const int color,
	const int name,
	SDL_Rect dst,
	const std::shared_ptr <Image> img
) :
	color(color),
	name(name),
	position (dst),
	img(img) 
{};

// get position
SDL_Rect Piece::getPosition() const {
	return position;
}

// set position
void Piece::setPosition (int x, int y) {
	position.x = x;
	position.y = y;
	this->getComponent <Sprite>().setPosition(x, y);
}

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