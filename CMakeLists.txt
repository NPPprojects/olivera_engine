cmake_minimum_required(VERSION 2.6)
project(OLIVERA)

include_directories(
src
)

add_library(olivera 
src/olivera/Core.cpp
src/olivera/Core.h
src/olivera/Entity.cpp
src/olivera/Entity.h
src/olivera/Component.cpp
src/olivera/Component.h
src/olivera/olivera.h)


add_executable(TestScreen
  src/TestScreen/main.cpp
 
  
)

target_link_libraries(TestScreen olivera)
