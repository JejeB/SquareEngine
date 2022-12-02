cmake_minimum_required(VERSION 3.10)

project(SquareEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

set (SRCS
		Rectangle.cpp
		Scene.cpp
		SquareEngine.cpp)

set (HEADERS	Rectangle.hpp
		Scene.hpp
		SquareEngine.hpp
		utils/Color.hpp
		utils/Vector.hpp)

add_library(SquareEngine ${SRCS} ${HEADERS} ${SDL} ${SDL_SRC})
target_link_libraries(SquareEngine ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_include_directories(SquareEngine PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
