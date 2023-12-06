cmake_minimum_required(VERSION 3.26)
project(SnoopyFinal C)

set(CMAKE_C_STANDARD 23)

add_executable(SnoopyFinal main.c
        src/gameplay/gameplay.h
        src/gameplay/gameplay.c
        src/keyboard/keyboard.h
        src/keyboard/keyboard.c
        src/menu/menu.h
        src/menu/menu.c
        src/tools/tools.h
        src/tools/tools.c)
