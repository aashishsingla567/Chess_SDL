#pragma once

#include "Game.hpp"
#include "imageObject.hpp"
#include "ECS.hpp"

class Sprite : public Component {
private:
	SDL_Rect position;
	std::shared_ptr <Image> img;
public:
	// defualt
	Sprite() {
		this->position = {0, 0, 0, 0};
	}
	Sprite(
		SDL_Rect dest,
		std::shared_ptr <Image> img,
		std::shared_ptr <Entity> entity
	);
	
	//// spirte copy assignment constructor
	//Sprite& operator=(const Sprite& other);
	//
	//// sprite move assignment constructor
	//Sprite& operator=(Sprite&& other) noexcept;

	//Sprite(Sprite&& obj) noexcept;
	//Sprite(const Sprite& obj);
	//
	// render
	void render() override;
	
	//update
	void update() override {};

	// set Image
	void setImage(std::shared_ptr <Image> img);
	// change position
	inline void setPosition(int x, int y) {
		position.x = x;
		position.y = y;
	}
	// keep in mind linker does not respond kindly to inline functions
	// change size
	inline void setSize(int w, int h) {
		position.w = w;
		position.h = h;
	}
};