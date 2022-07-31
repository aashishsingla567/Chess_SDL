#include "EventsHandler.h"
#include "board.hpp"
// MousePosition
Point2d MousePosition::m_pos;

inline void Print(const Point2d& data) {
	std::cout << "x :: " << data.x << " y :: " << data.y << '\n';
}

void MousePosition::update() {
	if (isMouseEvent(Game::Event.type)) {
		SDL_GetMouseState(&m_pos.x, &m_pos.y);
	}
}
// static Point2d getPosOnBoard();
Point2d MousePosition::getPosOnBoard() {
	return {
		int ( double (m_pos.x - board::LEFT_MARGIN) * board::ROWS / double (board::WIDTH) ),
		int ( double (m_pos.y - board::TOP_MARGIN)  * board::COLS / double (board::HEIGHT) )
	};
}

void EventsHandler::update() {
	MousePosition::update();
}