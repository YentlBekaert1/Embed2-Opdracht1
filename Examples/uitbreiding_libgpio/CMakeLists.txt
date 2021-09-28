cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Uitbreiding_libgpio)

add_executable(Uitbreiding_libgpio main.c)
include_directories(/usr/include/mariadb /usr/include/mariadb/mysql)

target_link_libraries(Uitbreiding_libgpio mariadb gpiod)
