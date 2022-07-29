#pragma once

#include "Game.hpp"

class MousePosition{
private:
	static point m_pos;
private:
	static inline bool isMouseEvent(Uint32 Event) {
		return Event >= SDL_MOUSEMOTION && Event <= SDL_MOUSEWHEEL;
		return Event == SDL_MOUSEMOTION;
		// SDL_MOUSEEVENT are given values from [1024, 1027]
	}
public:
	static void update();
	// get position
	static point getPos() {
		return m_pos;
	}
	
	static point getPosOnBoard();
};

class EventsHandler {
private:
	static bool m_quit;
	/* TODO :: 
	static bool m_pause;
	static bool m_resume;
	static bool m_restart;
	static bool m_save;
	static bool m_load;
	*/
	static bool m_fullscreen;
public:
	static void update();
};

