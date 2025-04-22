cmake_minimum_required(VERSION 3.31)
project(Proyecto_PE C)

set(CMAKE_C_STANDARD 11)

add_executable(mainPolanco Polanco/cuboRubik_main.c)
add_executable(imprimirCuboRubik Polanco/imprimirCuboRubik.c)
add_executable(mainJoseMaria Jose_Maria/Cubik.c)
