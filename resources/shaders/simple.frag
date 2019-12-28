#version 330 core

out vec4 Frag_Color;

in vec4 ex_Color;
in vec2 TexCoords;



uniform sampler2D ourTexture;

void main()
{
  Frag_Color= texture(ourTexture, TexCoords)*ex_Color;
}
