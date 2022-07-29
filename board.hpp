#pragma once

#include "Game.hpp"
#include "Sprite.hpp"
#include "GameEntities.hpp"

enum PIECE_NAMES {

	b_pawn1, b_pawn2, b_pawn3, b_pawn4, b_pawn5, b_pawn6, b_pawn7, b_pawn8,
	b_bishop1, b_bishop2,
	b_knight1, b_knight2,
	b_rook1, b_rook2,
	b_king1,
	b_queen1,

	w_pawn1, w_pawn2, w_pawn3, w_pawn4, w_pawn5, w_pawn6, w_pawn7, w_pawn8,
	w_bishop1, w_bishop2,
	w_knight1, w_knight2,
	w_rook1, w_rook2,
	w_king1,
	w_queen1,

};

class board {
public:
	constexpr static int ROWS = 8;
	constexpr static int COLS = 8;


	constexpr static int TILE_SIZE = 86;						// Side of the Tile tile
	constexpr static int WIDTH = TILE_SIZE * ROWS;
	constexpr static int HEIGHT = TILE_SIZE * ROWS;
	
	constexpr static int piece_shift_origin = (double)TILE_SIZE / 8;	// amount to center each piece
	constexpr static int PIECE_SIZE = 64;	// (3/4 * tile)	// reduced size of each piece 
																// (w.r.t. to TILE_SIZE)
	
	
	constexpr static int total_pieces = 16;					// total number of pieces on the board
	constexpr static int total_tiles = ROWS*COLS;			// total number of tiles on the board
	
	constexpr static int LEFT_MARGIN = 0*TILE_SIZE;
	constexpr static int TOP_MARGIN = 0*TILE_SIZE;

	constexpr static int RIGHT_MARGIN = WIN_W - LEFT_MARGIN - board::WIDTH;
	constexpr static int BOTTOM_MARGIN = WIN_H - TOP_MARGIN - board::HEIGHT;

	constexpr static point start = {				/// position of the board on the window
		LEFT_MARGIN,
		TOP_MARGIN
	};
public:
	static std::unordered_map < int, std::shared_ptr <Piece> > piecesMap;
	static std::array < std::array < std::shared_ptr <Tile>, COLS >, ROWS > background;
	static void init();
	static void mouseDetection();
private:
	static void makeBackground();
	static void makeMap();
	static point getPosOnWindow(point pos);
};
