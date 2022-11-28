cmake_minimum_required(VERSION 3.10)

project(SquareEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

set (SRCS	Main.cpp
			Rectangle.cpp
			Scene.cpp
			SquareEngine.cpp)

set (HEADERS	Rectangle.h
				Scene.h
				SquareEngine.h
				utils/Color.h
				utils/Vector.h)

add_executable(SquareEngine ${SRCS} ${HEADERS} ${SDL} ${SDL_SRC})
target_link_libraries(SquareEngine ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})