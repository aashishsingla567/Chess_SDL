// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Game.hpp"


// constexpr int WIN_W = 704, WIN_H = 640; // in the hpp file

int main ( int argc, char* argv[] ) {

    using namespace std; // PLEASE DON'T USE OUTSIDE ANYWHERE !!!

    Game thisGame = Game (
        "CHESS",
        {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED},
        {WIN_W, WIN_H},
        false
    );

    constexpr int FPS = 120;
    constexpr int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    while ( thisGame.isRunning ( ) ) {
        frameStart = SDL_GetTicks();
        
        thisGame.handleEvents( );
        thisGame.update ( );
        thisGame.render ( );

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < frameDelay) {
			//std::cout << "delay " << frameDelay - frameTime << '\n';
            SDL_Delay(frameDelay - frameTime);
        }
    }
    
    if (!std::string(SDL_GetError()).empty()) {
        throw std::runtime_error(SDL_GetError());
        return EXIT_FAILURE;
    }
    
    cout << "Game ended" << endl;

    return EXIT_SUCCESS;
}
