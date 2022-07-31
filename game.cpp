// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Game.hpp"
#include "Sprite.hpp"
#include "TextureHandler.hpp"
#include "AssetsManager.hpp"
#include "ECS.hpp"
#include "board.hpp"
#include "EventsHandler.h"

constexpr bool IS_ON = true;
constexpr bool IS_OFF = false;

#define DEBUG_MODE IS_ON

constexpr char SEPERATOR_STR[] =
    "-------------------------------------\n";

static size_t total_mem = 0;
//
//// make custom new for debuging
//void* operator new (size_t size) {
//    total_mem += size;
//    std::cout << "Allocating " << size << " bytes" << std::endl;
//    return malloc(size);
//}
//
//// make custom delete for debuging
//void operator delete (void* ptr, size_t size) {
//    total_mem -= size;
//    std::cout << "Deallocating " << size << " bytes" << std::endl;
//    std::cout << "Total Mem " << total_mem << std::endl;
//    free(ptr);
//}


sdl::shared_ptr<SDL_Window> Game::window = nullptr;
sdl::shared_ptr<SDL_Renderer> Game::renderer = nullptr;
SDL_Event Game::Event;

 // constexpr int WIN_W = 704, WIN_H = 640;  // in hpp file 

static Entity windowEntity;

const bool Game::init()
{

    using namespace std;

    // SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
		
#if DEBUG_MODE == IS_ON
        cout << "SDL initialization ERROR ::" << ' ' << SDL_GetError() << endl;
#endif // DEBUG_MODE

		// throw runtime error
        throw std::runtime_error("SDL initialization ERROR ::" + string(SDL_GetError()));
        return false;
    }

    // SDL_Image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {

#if DEBUG_MODE == IS_ON
        cout << "Failed to initialize SDL_Image for PNG, ERROR :: " << IMG_GetError() << endl;
#endif // DEBUG_MODE
        return false;
    }

    cout << "All Initializations successfull" << endl;
    cout << SEPERATOR_STR;

    return true;
}

Game::Game(
    const std::string &windowName,
    const std::pair<int, int> &windowPos,
    const std::pair<int, int> &windowSize,
    bool fullscreen
) :

    isPlaying(true),
    xPos(windowPos.first),
    yPos(windowPos.second),
    WIDTH(windowSize.first),
    HEIGHT(windowSize.second) {

    using namespace std;  // DON'T USE OUTSIDE // only for debug

    if (init() == false)
    {

        cout << "INITILIZATIONS FAILED!" << endl;

        isPlaying = false;

        return;
    }

    auto flags = ((fullscreen) ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_ALLOW_HIGHDPI;

    // ---------- create window -------------
    this->window =
        sdl::make_shared(SDL_CreateWindow (
            windowName.c_str(),
            xPos,  yPos,         
            WIDTH, HEIGHT,      
            flags
        )
    );

    if (this->window == nullptr)
    {

        std::cout << "SDL could not create window, ERROR :: " << SDL_GetError() << std::endl;

        isPlaying = false;

        return;
    }

    this->renderer = sdl::make_shared(SDL_CreateRenderer(this->window.get(), -1, 0));

    if (this->renderer == nullptr)
    {

        std::cout << "SDL could not create renderer, ERROR :: " << SDL_GetError() << std::endl;

        isPlaying = false;

        return;
    }

    SDL_SetRenderDrawColor(this->renderer.get(), 255, 255, 255, 255);

    /***************************************************************************
    *                           IMPORTANT NOTE:-                               *
    *       SPRITES ARE RENDERED IN THE ORDER IN WHICH THEY ARE INITIALIZED    *
    *               (same goes for other component types as well)              *
    *       i.e. the sprite with the lowest index is rendered first,           *
    *        and the sprite with the highest index is rendered last.           *
    *                                                                          *
    *       P.S. These are indexes inside the type vector of ComponentsMap     *
    *                                                                          *
    ***************************************************************************/
	
    AssetsManager::init();
	
    windowEntity.addComponent <Sprite>( std::make_shared <Sprite> (
        Sprite (
			    {0, 0, WIN_W, WIN_H},
			    AssetsManager::getImg (sq_dark_gray),
			    std::make_shared <Entity> (windowEntity)
            )
        )
    );
    board::init();
};

Game::~Game()
{
#if DEBUG_MODE == IS_ON
    std::cout << "Destroying the Game. Please wait while we free your memory." << std::endl;
#endif // DEBUG_MODE
    SDL_Quit();
    return;
}

void Game::handleEvents()
{
    SDL_WaitEvent(&Event);

    switch (Event.type)
    {
    case SDL_QUIT:
        isPlaying = false;
        return;
    }
    EventsHandler::update();
    board::mouseDetection();
}

void Game::update()
{
    componentsMap::updateComponets();
}

void Game::render()
{
    SDL_RenderClear(Game::renderer.get());

    // empty space
    //windowEntity.render();
    // Game board
    componentsMap::renderComponets();

    SDL_RenderPresent(Game::renderer.get());
}
