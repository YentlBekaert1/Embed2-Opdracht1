cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Input_log)

add_executable(Input_log main.c)

include_directories(/usr/include/mariadb/)
include_directories(/usr/include/mariadb/mysql)
include_directories(/usr/lib/arm-linux-gnueabihf/ -lmariadb)
set(-I/usr/include/mariadb -I/usr/include/mariadb/mysql)
target_link_libraries(Input_log -L/usr/lib/arm-linux-gnueabihf/ -lmariadb)
target_link_libraries(Input_log PJ_RPI)