cmake_minimum_required (VERSION 2.6)

project (DubstepZombies)

include_directories(/usr/include/allegro5)

#Force drawutils to build because everything depends on that.
add_library(drawutils STATIC src/drawutils/drawutils.cpp)

#TODO: can i include headers instead of CPP files?
add_executable(../bin/DZ src/launcher.cpp)

# link against it.
target_link_libraries(../bin/DZ drawutils)
target_link_libraries(../bin/DZ allegro)
target_link_libraries(../bin/DZ allegro_font)
target_link_libraries(../bin/DZ allegro_ttf)


