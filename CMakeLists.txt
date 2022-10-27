cmake_minimum_required(VERSION 3.13)

project(allegro CXX)

include_directories("C:\\lib\\allegro\\allegro\\include")
link_directories("C:\\lib\\allegro\\allegro")
link_directories("C:\\lib\\allegro\\allegro\\lib")
add_executable(a.out main.cpp astar.cpp game.cpp)

target_link_libraries(a.out allegro allegro_font allegro_primitives)

# add_executable(astar.out astar.cpp)