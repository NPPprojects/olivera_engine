#version 330 core
#extension GL_ARB_shader_viewport_layer_array : enable
out vec4 FragColor;


in vec2 TexCoord;

// texture sampler
uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.5);
}