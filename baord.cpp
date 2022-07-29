// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "board.hpp"
#include "AssetsManager.hpp"
#include "TextureHandler.hpp"

std::unordered_map<int, std::shared_ptr<Piece>> board::piecesMap;
std::array<std::array<std::shared_ptr<Tile>, board::COLS>, board::ROWS> board::background;

static std::shared_ptr<Piece> generatePeice(
	int xPos,
	int yPos,
	int color,
	int imgName,
	int pieceName
) {
	std::shared_ptr<Piece> piece = std::make_shared<Piece>(
		Piece(
			color,
			pieceName,
			AssetsManager::getImg(imgName)
		)
	);
	piece->addComponent <Sprite>(std::make_shared <Sprite>(
			Sprite(
				{	board::start.x + board::piece_shift_origin + xPos,
					board::start.y + board::piece_shift_origin + yPos,
					board::PIECE_SIZE,
					board::PIECE_SIZE
				},
				piece->getImg (),
				piece
			)
		)
	);
	return piece;
}

static std::shared_ptr<Tile> generateTile(int x, int y, int imgName, int color) {
	auto tile = std::make_shared <Tile> (
		Tile (
			color,
			{ board::start.x + x,
			  board::start.y + y,
			  board::TILE_SIZE,
			  board::TILE_SIZE },
			AssetsManager::getImg (imgName)
		)
	);
	tile->addComponent <Sprite> (
		std::make_shared <Sprite>(
			Sprite(
				tile->getPosition(),
				tile->getImg(),
				tile
			)
		)
	);
	return tile;
}

void board::makeBackground()
{
	bool isWhite = true;
	for (int i = 0; i < board::ROWS; i++)
	{
		for (int j = 0; j < board::COLS; j++)
		{
			int imgName = sq_dark_brown;
			if (isWhite)
				imgName = sq_light_brown;
			
			background[i][j] = generateTile(
				j * TILE_SIZE, 
				i * TILE_SIZE,
				imgName,
				isWhite ? COLOR::WHITE : COLOR::BLACK
			);
			isWhite = !isWhite;
		}
		isWhite = !isWhite;
	}
};

void board::makeMap()
{
	piecesMap = std::unordered_map<int, std::shared_ptr<Piece>> ({
		{	b_rook1,
			generatePeice(0, 0, COLOR::BLACK, b_rook, b_rook1)
		},
		{	b_rook2,
			generatePeice(board::TILE_SIZE * 7, 0, COLOR::BLACK, b_rook, b_rook2)
		},
		
		{	b_knight1,
			generatePeice(board::TILE_SIZE * 1, 0, COLOR::BLACK, b_knight, b_knight1)
		},
		{	b_knight2,
			generatePeice(board::TILE_SIZE * 6, 0, COLOR::BLACK, b_knight, b_knight2)
		},
		
		{	b_bishop1,
			generatePeice(board::TILE_SIZE * 2, 0, COLOR::BLACK, b_bishop, b_bishop1)
		},
		{	b_bishop2,
			generatePeice(board::TILE_SIZE * 5, 0, COLOR::BLACK, b_bishop, b_bishop2)
		},
		
		{	b_queen1,
			generatePeice(board::TILE_SIZE * 3, 0, COLOR::BLACK, b_queen, b_queen)
		},
		{	b_king1,
			generatePeice(board::TILE_SIZE * 4, 0, COLOR::BLACK, b_king, b_king)
		},
			
		{	b_pawn1,
			generatePeice(0, board::TILE_SIZE * 1, COLOR::BLACK, b_pawn, b_pawn1)
		},
		{	b_pawn2,
			generatePeice(board::TILE_SIZE * 1, board::TILE_SIZE * 1, COLOR::BLACK, b_pawn, b_pawn2)
		},
		{
			b_pawn3,
			generatePeice(board::TILE_SIZE * 2, board::TILE_SIZE * 1, COLOR::BLACK, b_pawn, b_pawn3)
		},
		{
			b_pawn4,
			generatePeice(board::TILE_SIZE * 3, board::TILE_SIZE * 1, COLOR::BLACK, b_pawn, b_pawn4)
		},
		{
			b_pawn5,
			generatePeice(board::TILE_SIZE * 4, board::TILE_SIZE * 1, COLOR::BLACK, b_pawn, b_pawn5)
		},
		{
			b_pawn6,
			generatePeice(board::TILE_SIZE * 5, board::TILE_SIZE * 1, COLOR::BLACK, b_pawn, b_pawn6)
		},
		{
			b_pawn7,
			generatePeice(board::TILE_SIZE * 6, board::TILE_SIZE * 1, COLOR::BLACK, b_pawn, b_pawn7)
		},
		{
			b_pawn8,
			generatePeice(board::TILE_SIZE * 7, board::TILE_SIZE * 1, COLOR::BLACK, b_pawn, b_pawn8)
		},

		{
			w_rook1,
			generatePeice(0, board::TILE_SIZE * 7, COLOR::WHITE, w_rook, w_rook1)
		},
		{
			w_rook2,
			generatePeice(board::TILE_SIZE * 7, board::TILE_SIZE * 7, COLOR::WHITE, w_rook, w_rook2)
		},
		{
			w_knight1,
			generatePeice(board::TILE_SIZE * 1, board::TILE_SIZE * 7, COLOR::WHITE, w_knight, w_knight1)
		},
		{
			w_knight2,
			generatePeice(board::TILE_SIZE * 6, board::TILE_SIZE * 7, COLOR::WHITE, w_knight, w_knight2)
		},
		{
			w_bishop1,
			generatePeice(board::TILE_SIZE * 2, board::TILE_SIZE * 7, COLOR::WHITE, w_bishop, w_bishop1)
		},
		{
			w_bishop2,
			generatePeice(board::TILE_SIZE * 5, board::TILE_SIZE * 7, COLOR::WHITE, w_bishop, w_bishop2)
		},
		{
			w_queen1,
			generatePeice(board::TILE_SIZE * 3, board::TILE_SIZE * 7, COLOR::WHITE, w_queen, w_queen)
		},
		{
			w_king1,
			generatePeice(board::TILE_SIZE * 4, board::TILE_SIZE * 7, COLOR::WHITE, w_king, w_king)
		},
		{
			w_pawn1,
			generatePeice(0, board::TILE_SIZE * 6, COLOR::WHITE, w_pawn, w_pawn1)
		},
		{
			w_pawn2,
			generatePeice(board::TILE_SIZE * 1, board::TILE_SIZE * 6, COLOR::WHITE, w_pawn, w_pawn2)
		},
		{
			w_pawn3,
			generatePeice(board::TILE_SIZE * 2, board::TILE_SIZE * 6, COLOR::WHITE, w_pawn, w_pawn3)
		},
		{
			w_pawn4,
			generatePeice(board::TILE_SIZE * 3, board::TILE_SIZE * 6, COLOR::WHITE, w_pawn, w_pawn4)
		},
		{
			w_pawn5,
			generatePeice(board::TILE_SIZE * 4, board::TILE_SIZE * 6, COLOR::WHITE, w_pawn, w_pawn5)
		},
		{
			w_pawn6,
			generatePeice(board::TILE_SIZE * 5, board::TILE_SIZE * 6, COLOR::WHITE, w_pawn, w_pawn6)
		},
		{
			w_pawn7,
			generatePeice(board::TILE_SIZE * 6, board::TILE_SIZE * 6, COLOR::WHITE, w_pawn, w_pawn7)
		},
		{
			w_pawn8,
			generatePeice(board::TILE_SIZE * 7, board::TILE_SIZE * 6, COLOR::WHITE, w_pawn, w_pawn8)
		}
	});
	
};

void board::init() {
	piecesMap.reserve(total_pieces);
	makeBackground();
	makeMap();
}