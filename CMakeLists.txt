cmake_minimum_required(VERSION 3.16)
project(gauss_row C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENTIONS OFF)
if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()
add_compile_options(-Wall -Wextra)
set(CMAKE_C_FLAG_RELEASE "-02")
set(CMAKE_C_FLAG_DEBUG "-g -00")
add_executable(gauss_row
main.c
matr.c
form.c
Gau.c
)
target_link_libraries(gauss_row PRIVATE m)
targersources(gauss_row PRIVATE
matr.h
form.h
gau.h
)

