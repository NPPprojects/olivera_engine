#version 330 core
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec4 in_Color;
layout(location = 2) in vec2 in_TexCoords;

out vec4 ex_Color;
out vec2 TexCoords;
void main()
{
  gl_Position = vec4(in_Position, 1.0);
  ex_Color = in_Color;
  TexCoords = vec2(in_TexCoords.x, in_TexCoords.y);
}

