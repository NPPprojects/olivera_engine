cmake_minimum_required(VERSION 2.6)
project(OLIVERA)

include_directories(
${PROJECT_SOURCE_DIR}/src
contrib
)
add_definitions(-DSTD_SR1_DEBUG)

FILE(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")
if(MSVC)
  include_directories(
    contrib/msvc-2017-windows-x86/glew/include
    contrib/msvc-2017-windows-x86/SDL2/include
    contrib/msvc-2017-windows-x86/openal-soft/include
    contrib/msvc-2017-windows-x86/ogg/include
    contrib/msvc-2017-windows-x86/vorbis/include
  )

  link_directories(
    ${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/SDL2/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/glew/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/openal-soft/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/ogg/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/vorbis/lib
  )
else()
  include_directories(
    /usr/X11R6/include
    /usr/local/include
  )

  link_directories(
    /usr/X11R6/lib
    /usr/local/lib
  )
endif()

if(MSVC)
  add_definitions(-DSDL_MAIN_HANDLED)
endif()
add_library(olivera 
	src/olivera/Core.cpp
	src/olivera/Core.h
	src/olivera/Entity.cpp
	src/olivera/Entity.h
	src/olivera/Component.cpp
	src/olivera/Component.h
	src/olivera/olivera.h
	src/olivera/ShaderProgram.cpp
	src/olivera/ShaderProgram.h
	src/olivera/Meshrenderer.cpp
	src/olivera/Meshrenderer.h
	src/olivera/Mesh.cpp
	src/olivera/Mesh.h
	src/olivera/Sound.cpp
	src/olivera/Sound.h
	src/olivera/TextureAdapter.h
	src/olivera/mathutil.h
	src/olivera/Context.h
	src/olivera/Context.cpp
	src/olivera/Texture.cpp
	src/olivera/Texture.h
	src/olivera/Exception.h
	src/olivera/Exception.cpp
	src/olivera/olivera.h
	src/olivera/RenderTexture.h
	src/olivera/RenderTexture.cpp
	src/olivera/Shader.cpp
	src/olivera/Shader.h
	src/olivera/Buffer.h
	src/olivera/Buffer.cpp
)

if(MSVC)
  target_link_libraries(olivera
    SDL2 glew32 opengl32 OpenAL32 ogg vorbis vorbisfile
  )
else()
  target_link_libraries(olivera
    SDL2 GLU GLEW GL openal ogg vorbis vorbisfile
  )
endif()

add_executable(TestScreen
  src/TestScreen/main.cpp  
)

target_link_libraries(TestScreen olivera)

if(MSVC)
  add_custom_command(TARGET TestScreen POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:TestScreen>"
  )

  add_custom_command(TARGET TestScreen POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/glew/bin/glew32.dll"
      "$<TARGET_FILE_DIR:TestScreen>"
  )

  add_custom_command(TARGET TestScreen POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/openal-soft/bin/OpenAL32.dll"
      "$<TARGET_FILE_DIR:TestScreen>"
  )
endif()
