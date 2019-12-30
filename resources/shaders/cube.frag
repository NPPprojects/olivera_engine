#version 330 core

out vec4 Frag_Color;

in vec4 ex_Color;



void main()
{
  Frag_Color= ex_Color;
}
