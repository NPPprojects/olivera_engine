cmake_minimum_required(VERSION 2.6)
project(OLIVERA)

add_library(olivera src/olivera/dummy.cpp)

target_link_libraries(olivera SDL2 opengl32 glew32)

add_executable(pizzatime
  src/pizzatime/main.cpp

)

target_link_libraries(pizzatime olivera)
