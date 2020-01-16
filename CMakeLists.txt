cmake_minimum_required(VERSION 2.6)
project(OLIVERA)

include_directories(
src
contrib
)
FILE(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")
if(MSVC)
  include_directories(
    contrib/msvc-2017-windows-x86/glew/include
    contrib/msvc-2017-windows-x86/SDL2/include
    contrib/msvc-2017-windows-x86/openal-soft/include
    contrib/msvc-2017-windows-x86/ogg/include
    contrib/msvc-2017-windows-x86/vorbis/include
	contrib/msvc-2017-windows-x86/assimp/include
  )

  link_directories(
    ${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/SDL2/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/glew/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/openal-soft/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/ogg/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/vorbis/lib
	${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/assimp/lib
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
src/olivera/MeshRenderer.cpp
src/olivera/MeshRenderer.h
src/olivera/Mesh.cpp
src/olivera/Mesh.h
src/olivera/Model.cpp
src/olivera/Model.h
src/olivera/Sound.cpp
src/olivera/Sound.h
src/olivera/Keyboard.cpp
src/olivera/Keyboard.h
src/olivera/Texture.h
src/olivera/Texture.cpp
src/olivera/VertexBuffer.h
src/olivera/VertexBuffer.cpp
src/olivera/stb_image.cpp

src/olivera/CurrentCamera.h
src/olivera/CurrentCamera.cpp
src/olivera/Mouse.h
src/olivera/Mouse.cpp
src/olivera/Transform.h
src/olivera/Transform.cpp
src/olivera/Environment.h
src/olivera/Environment.cpp

src/olivera/Resource.h
src/olivera/Resource.cpp

src/olivera/ResourceManager.h
src/olivera/ResourceManager.cpp

src/olivera/Collision.h
src/olivera/Collision.cpp

src/olivera/PostProcessing.h
src/olivera/PostProcessing.cpp

src/olivera/SoundSource.cpp
src/olivera/SoundSource.h

stc/olivera/Material.h
src/olivera/Material.cpp

src/olivera/Light.h
src/olivera/Light.cpp
)


if(MSVC)
  target_link_libraries(olivera 
    SDL2 glew32 opengl32 OpenAL32 ogg vorbis vorbisfile assimp-vc140-mt
  )
else()
  target_link_libraries(olivera
    SDL2 GLU GLEW GL openal ogg vorbis vorbisfile assimp-vc140-mt
  )
endif()

add_executable(TestScreen

src/TestScreen/FPSCamera.cpp
src/TestScreen/FPSCamera.h

src/TestScreen/CameraInputManager.cpp
src/TestScreen/CameraInputManager.h

src/TestScreen/SoundInputManager.cpp
src/TestScreen/SoundInputManager.h

src/TestScreen/GameObject.cpp
src/TestScreen/GameObject.h

src/TestScreen/BoxInputManager.cpp
src/TestScreen/BoxInputManager.h
  
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
      "${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/assimp/bin/assimp-vc140-mt.dll"
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
