cmake_minimum_required(VERSION 3.10)

project(SquareEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Catch2 3 REQUIRED)

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
		
set(TESTS tests/test.cpp)


add_library(SquareEngine ${SRCS} ${HEADERS} ${SDL} ${SDL_SRC})
target_link_libraries(SquareEngine ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_include_directories(SquareEngine PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(unit_test ${TESTS} ${SRCS} ${HEADERS} ${SDL} ${SDL_SRC})
target_link_libraries(unit_test ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} Catch2::Catch2WithMain)
target_include_directories(unit_test PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
set_target_properties(unit_test PROPERTIES LINKER_LANGUAGE CXX)

add_test(NAME Test COMMAND unit_test)