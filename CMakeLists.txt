cmake_minimum_required (VERSION 2.6)

project (DubstepZombies)

include_directories(/usr/include/allegro5)

#Force drawutils to build because everything depends on that.
add_library(drawutils STATIC src/drawutils/drawutils.cpp)

#Force inputs to build 
add_library(inputs STATIC src/input/inputs.cpp)
add_library(keyboard STATIC src/input/keyboard.cpp)
add_library(gamestate STATIC src/gamestate/gamestate.cpp)
add_library(titlescreen STATIC src/gamestate/titlescreen.cpp)
add_library(ingame STATIC src/gamestate/ingame.cpp)


#TODO: can i include headers instead of CPP files?
add_executable(../bin/DZ src/launcher.cpp)

# link against it.
target_link_libraries(../bin/DZ inputs)
target_link_libraries(../bin/DZ drawutils)
target_link_libraries(../bin/DZ gamestate)
target_link_libraries(../bin/DZ ingame)
target_link_libraries(../bin/DZ keyboard)
target_link_libraries(../bin/DZ titlescreen)
target_link_libraries(../bin/DZ allegro)
target_link_libraries(../bin/DZ allegro_font)
target_link_libraries(../bin/DZ allegro_ttf)


