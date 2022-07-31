#pragma once

#include "Game.hpp"
#include "Sprite.hpp"
#include "ECS.hpp"

enum COLOR {
	BLACK = 0,
	WHITE
};

class Piece;

class Tile : public Entity {
	const int color;
	const SDL_Rect position;
	const std::shared_ptr <Image> img;
	std::shared_ptr <Piece> pieceOnMe;
public:
	Tile(
		int color, 
		SDL_Rect position, 
		std::shared_ptr <Image> img,
		std::shared_ptr <Piece> piece = nullptr
	);
	~Tile();
	// This is what i look like
	int getColor();
	// where am I?
	SDL_Rect getPosition();
	// get my image
	std::shared_ptr <Image> getImg();
	// put piece on me
	void putPiece(std::shared_ptr <Piece> piece);
};

class Piece : public Entity {
private:
	const int color;
	const int name;
	SDL_Rect position;
	const std::shared_ptr <Image> img;
public:
	Piece(const int color, const int name, SDL_Rect dst, const std::shared_ptr <Image> img);
	~Piece();
	int getColor();
	int getName();
	std::shared_ptr <Image> getImg();
	SDL_Rect getPosition() const;
	void setPosition (int x, int y);
};

