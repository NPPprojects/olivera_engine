# Olivera Engine

Olivera Engine is a lightweight 3D game engine built in C++ using OpenGL and SDL. It began as a university assignment, where I received a First, and later grew into a personal engine project focused on learning, experimentation, and small-scale 3D game development.

The engine follows an Entity Component System architecture and is designed to provide enough structure for building small games while keeping the core systems simple and usable.

## Features

- Entity Component System architecture
- OpenGL rendering
- SDL-based windowing and input
- 3D sound support
- `.obj` model loading
- Simple vertex-defined primitive loading from plain text-style data files
- Texture loading
- Pre-written GLSL shaders for lighting and shadows
- Support for custom shaders
- Split-screen rendering with different post-processing effects per screen
- Box collision support
- Doxygen-generated documentation

## Build

To build using git Bash and CMake for Visual Studio 2019: 

1. Clone repo
2. Navigate to the repo source directory
3. Using git Bash, type makedir Build
4. cd Build
5. cmake .. -G "Visual Studio 16 2019" -A Win32
6. Open Olivera.sln and set TestScreen as Start-Up Project.
