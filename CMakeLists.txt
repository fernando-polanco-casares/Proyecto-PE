cmake_minimum_required(VERSION 3.31)
project(Proyecto_PE C)

set(CMAKE_C_STANDARD 11)

add_executable(mainPolanco Polanco/cuboRubik_main.c)
add_executable(imprimirCuboRubik Polanco/imprimirCuboRubik_V1.0.2.c)
add_executable(movimientoCuboRubik Polanco/movimientoCuboRubik_V1.0.1.c)