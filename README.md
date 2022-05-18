# Olivera Engine

Olivera Engnie is a passionate project, that started off as a uni assigment to build a simple 3D Game Engine, using openGL and SDL. 
At it's current state, it's an Entity Component System, that has the following features:
3D sound, .obj file loading, method of loading simple primative shapes that the user can create themselves, texture loading, pre-written GLSL shaders that handle lighting and shadows, as well as the ability to use custom shaders. Some additional features include: multiple split screen with different post-processing on each screen; Box Collision.
Doxygen Documentation can be found here: 
The ultimate goal for this engine is to used for making 3D games for game jams. I have frequently stuggled with finishing games when working on a game jam, as using engines like Unity and Unreal provide me with too much functionality, that I struggle to implement in time.

To build using git Bash and Cmake for Visual Studio 2019: 

1. Clone repo
2. Navigate to repo source directory
3. Using git Bash type makedir Build
4. cd Build
5. cmake .. -G "Visual Studio 16 2019" -A Win32
6. Open Olivera.sln and set TestScreen as Start-Up Project.
