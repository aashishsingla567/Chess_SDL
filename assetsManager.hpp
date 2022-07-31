#pragma once

#include "Game.hpp"
#include "imageObject.hpp"

enum TEXTURE_NAMES {
	sq_dark_brown,
	sq_light_brown,
	sq_dark_gray,
	sq_light_gray,

	b_pawn,
	b_bishop,
	b_king,
	b_knight,
	b_queen,
	b_rook,

	w_pawn,
	w_bishop,
	w_king,
	w_knight,
	w_queen,
	w_rook,
};

using sound = int; // ! CHANGE WHEN ADDING SOUNDS

class AssetsManager {
public:
	typedef struct SpritesMap {
		std::unordered_map < int, std::shared_ptr <Image> > map;
	} ImagesMap;
	typedef struct soundsMap {
		std::unordered_map < int, std::shared_ptr <sound> > map;
	} soundsMap;
	static ImagesMap Images;
	static soundsMap sounds;
public:
	static void init ( );
	static std::shared_ptr<Image> getImg ( int name );
};
