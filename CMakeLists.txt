cmake_minimum_required (VERSION 2.6)
add_compile_options(-std=c++11)

project (DubstepZombies)

include_directories(/usr/include/allegro5)

#Build order
add_library(drawutils STATIC src/drawutils/drawutils.cpp)

add_library(coord STATIC src/utils/coord.cpp)
add_library(gameobject STATIC src/utils/gameobject.cpp)

add_library(controller STATIC src/input/controller.cpp)
add_library(keyboard STATIC src/input/keyboard.cpp)
add_library(inputs STATIC src/input/inputs.cpp)

add_library(gamestate STATIC src/gamestate/gamestate.cpp)
add_library(titlescreen STATIC src/gamestate/titlescreen.cpp)
add_library(ingame STATIC src/gamestate/ingame.cpp)

add_library(malldraw STATIC src/mall/malldraw.cpp)
add_library(mallobject STATIC src/mall/malldraw.cpp)
add_library(mallparser STATIC src/mall/mallparser.cpp)

add_library(player STATIC src/character/player.cpp)


#TODO: can i include headers instead of CPP files?
add_executable(../bin/DZ src/launcher.cpp)

target_link_libraries(ingame coord)
target_link_libraries(mallparser malldraw)
target_link_libraries(player gameobject)
target_link_libraries(ingame player)

# link against it.
target_link_libraries(../bin/DZ drawutils)
target_link_libraries(../bin/DZ coord)

target_link_libraries(../bin/DZ player)

target_link_libraries(../bin/DZ controller)
target_link_libraries(../bin/DZ inputs)
target_link_libraries(../bin/DZ keyboard)

target_link_libraries(../bin/DZ gamestate)
target_link_libraries(../bin/DZ titlescreen)
target_link_libraries(../bin/DZ ingame)


target_link_libraries(../bin/DZ mallparser)

target_link_libraries(../bin/DZ allegro)
target_link_libraries(../bin/DZ allegro_font)
target_link_libraries(../bin/DZ allegro_ttf)
target_link_libraries(../bin/DZ allegro_image)




