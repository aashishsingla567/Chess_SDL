#pragma once

#include "game.hpp"
#include "Sprite.hpp"
#include "ECS.hpp"

enum COLOR {
	BLACK = 0,
	WHITE
};

class Tile;

class Tile : public Entity {
	const int color;
	const SDL_Rect position;
	const std::shared_ptr <Image> img;
public:
	Tile(int color, SDL_Rect position, std::shared_ptr <Image> img);
	~Tile();
	int getColor();
	SDL_Rect getPosition();
	std::shared_ptr <Image> getImg();
};

class Piece : public Entity {
private:
	const int color;
	const int name;
	const std::shared_ptr <Image> img;
public:
	Piece(const int color, const int name, const std::shared_ptr <Image> img);
	~Piece();
	int getColor();
	int getName();
	std::shared_ptr <Image> getImg();
};

