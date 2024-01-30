cmake_minimum_required(VERSION 3.23)
project(SNAKE)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(SNAKE snake.cpp)
target_link_libraries(SNAKE ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image -mwindows)
