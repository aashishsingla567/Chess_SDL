#cmake_minimum_required(VERSION 3.7)
#project(Chess_SDL)
#
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
#
#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
##include_directories(${SDL2_INCLUDE_DIRS})
#
#include_directories(.
#        /usr/include/SDL2
#        /usr/include/SDL
#        ${SDL2_INCLUDE_DIRS}
#        ${SDL2_IMAGE_INCLUDE_DIRS})
#
#add_executable(Chess_SDL
#        AssetsManager.cpp
#        AssetsManager.hpp
#        baord.cpp
#        board.hpp
#        ECS.cpp
#        ECS.hpp
#        EventsHandler.cpp
#        EventsHandler.h
#        EventsSystem.cpp
#        EventsSystem.h
#        Game.cpp
#        Game.hpp
#        GameEntites.cpp
#        GameEntities.hpp
#        imageObject.hpp
#        main.cpp
#        OrderedVector.h
#        SDL_memory.h
#        Sprite.cpp
#        Sprite.hpp
#        TextureHandler.cpp
#        TextureHandler.hpp)
#
#target_link_libraries(Chess_SDL ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
#
##target_link_libraries(Chess_SDL ${SDL2_LIBRARIES})

project(Chess_SDL)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        AssetsManager.cpp
        baord.cpp
        ECS.cpp
        EventsHandler.cpp
        EventsSystem.cpp
        Game.cpp
        GameEntites.cpp
        main.cpp
        Sprite.cpp
        TextureHandler.cpp)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(. ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})