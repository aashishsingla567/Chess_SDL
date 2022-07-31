// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "TextureHandler.hpp"
#include "AssetsManager.hpp"
#include "board.hpp"

//
//enum TEXTURE_NAMES {
//	sq_dark_brown,
//	sq_light_brown,
//	sq_dark_gray,
//	sq_light_gray,
//
//	b_pawn,
//	b_bishop,
//	b_king,
//	b_knight,
//	b_queen,
//	b_rook,
//
//	w_pawn,
//	w_bishop,
//	w_king,
//	w_knight,
//	w_queen,
//	w_rook,
//};

AssetsManager::ImagesMap AssetsManager::Images;
AssetsManager::soundsMap AssetsManager::sounds;

void AssetsManager::init ( ) {
	using namespace std;
	cout << "Loading Assets... " << endl;

	Images.map.reserve(board::total_pieces);
	
	Images.map [sq_dark_brown] =
		TextureHandler::loadTexture
		( "./assets/PNGs/With Shadow/1024px/square brown dark_png_shadow_1024px.png" );

	Images.map [sq_light_brown] =
		TextureHandler::loadTexture
		( "./assets/PNGs/With Shadow/1024px/square brown light_png_shadow_1024px.png" );

	Images.map [sq_dark_gray] =
		TextureHandler::loadTexture
		( "./assets/PNGs/With Shadow/1024px/square gray dark _png_shadow_1024px.png" );

	Images.map [sq_light_gray] =
		TextureHandler::loadTexture
		( "./assets/PNGs/With Shadow/1024px/square gray light _png_shadow_1024px.png" );

	Images.map [b_bishop] =
		TextureHandler::loadTexture
		( "./assets/PNGs/With Shadow/1024px/b_bishop_png_shadow_1024px.png" );
	
	Images.map [b_king] =
		TextureHandler::loadTexture
		( "./assets/PNGs/With Shadow/1024px/b_king_png_shadow_1024px.png" );
	
	Images.map [b_knight] =
		TextureHandler::loadTexture
		( "./assets/PNGs/With Shadow/1024px/b_knight_png_shadow_1024px.png" );
	
	Images.map [b_pawn] =
		TextureHandler::loadTexture
		( "./assets/PNGs/With Shadow/1024px/b_pawn_png_shadow_1024px.png" );
	
	Images.map [b_queen] =
		TextureHandler::loadTexture
		( "./assets/PNGs/With Shadow/1024px/b_queen_png_shadow_1024px.png" );
	
	Images.map [b_rook] =
		TextureHandler::loadTexture
		( "./assets/PNGs/With Shadow/1024px/b_rook_png_shadow_1024px.png" );
	Images.map [w_bishop] =
		TextureHandler::loadTexture
		( "./assets/PNGs/With Shadow/1024px/w_bishop_png_shadow_1024px.png" );
	
	Images.map [w_king] =
		TextureHandler::loadTexture
		( "./assets/PNGs/With Shadow/1024px/w_king_png_shadow_1024px.png" );
	
	Images.map [w_knight] =
		TextureHandler::loadTexture
		( "./assets/PNGs/With Shadow/1024px/w_knight_png_shadow_1024px.png" );
	
	Images.map [w_pawn] =
		TextureHandler::loadTexture
		( "./assets/PNGs/With Shadow/1024px/w_pawn_png_shadow_1024px.png" );
	
	Images.map [w_queen] =
		TextureHandler::loadTexture
		( "./assets/PNGs/With Shadow/1024px/w_queen_png_shadow_1024px.png" );
	
	Images.map [w_rook] =
		TextureHandler::loadTexture
		( "./assets/PNGs/With Shadow/1024px/w_rook_png_shadow_1024px.png" );

	// debug
	{
		int fail = 0, success = 0;
		for (const auto& [name, sprite] : Images.map) {
			if (sprite.get() == nullptr) {
				fail++;
			}
			else success++;
		}
		std::cout << Images.map.size() << " Images initiallized to load" << std::endl;
		std::cout << fail << " Images failed to load " << std::endl;
		std::cout << success << " Images successfully loaded" << std::endl;
	}
}

// get texture
std::shared_ptr <Image> AssetsManager::getImg (int name) {
	return Images.map[name];
}
