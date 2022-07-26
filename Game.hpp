
#pragma once
#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

// IO
#include <iostream>

// DS
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <list>

// mem & func
#include <memory>
#include <functional>

// SDL
#include "SDL.h"
#include "SDL_image.h"

// CUSTOM
#include "SDL_memory.h"

#define CLION true

struct Point2d {
    int x, y;
};

struct Rect {
    int x, y;
    int w, h;
};

constexpr int WIN_W = 683, WIN_H = 683;
class Game
{
private: // all the stuff in the initializer list
    bool isPlaying;
    const int xPos, yPos;
    const int WIDTH, HEIGHT;

private: // basic UI stuff
    bool m_isFullScreen = false;

public:
    static sdl::shared_ptr<SDL_Window> window;
    static sdl::shared_ptr<SDL_Renderer> renderer;
    static SDL_Event Event;

public:
    Game(
        const std::string &windowName,
        const std::pair<int, int> &windowPos = {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED},
        const std::pair<int, int> &windowSize = {800, 600},
        bool fullscreen = false);
    ~Game();

    static bool init();
    void update();
    void handleEvents();
    void render();
	
    void fullscreen_toogle()
    {
        m_isFullScreen = !m_isFullScreen;
    }

    const inline bool isFullScreen() const
    {
        return m_isFullScreen;
    }

    const inline bool isRunning() const
    {
        return isPlaying;
    };
};

//
//void* operator new (size_t size);
//void operator delete (void* ptr, size_t size);

#endif // GAME_HPP_INCLUDED
