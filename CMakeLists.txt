cmake_minimum_required (VERSION 2.6)

project (DubstepZombies)

include_directories(/usr/include/allegro5)

include_directories(../src/input/)
include_directories(../src/gamestate/)
include_directories(../src/drawutils/)

add_executable(../bin/DZ src/launcher.cpp)

target_link_libraries(../bin/DZ allegro)
target_link_libraries(../bin/DZ allegro_font)
target_link_libraries(../bin/DZ allegro_ttf)

target_link_libraries(../bin/DZ src/)

