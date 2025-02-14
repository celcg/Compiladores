cmake_minimum_required(VERSION 3.28)
project(proy1 C)

set(CMAKE_C_STANDARD 11)

add_executable(proy1 main.c
        abb.c
        abb.h
        analisisLexico.c
        analisisSintactico.c
        analisisLexico.h
        definiciones.h
        tablaSimbolos.c
        tablaSimbolos.h
        analisisSintactico.h)
