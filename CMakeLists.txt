cmake_minimum_required(VERSION 3.7)

project(SquareEngine)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
		
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
target_link_libraries(SquareEngine ${SDL2_LIBRARIES})