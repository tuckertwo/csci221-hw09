cmake_minimum_required(VERSION 3.10)
project(tsp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -pedantic)
add_library(Cities cities.cc)

add_executable(tsp tsp.cc)

find_package(Catch2 REQUIRED)
add_executable(test_cities test_cities.cc)
target_link_libraries(test_cities PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_cities LINK_PUBLIC Cities)
target_link_libraries(tsp         LINK_PUBLIC Cities)
