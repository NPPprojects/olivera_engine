#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float time;
const float offset= 1.0/300.0;

uniform float gamma;

uniform float exposure;

uniform bool filter;
uniform int blurIntesity;
void main()
{

	   vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );
	float kernel[9];
	if(filter ==true)
	{
			//Edges 
	//		1,1,1,
	//		1,-8,1,
	//		1,1,1

			//Default
			kernel[0]=0;kernel[1]=0;kernel[2]=0;
			kernel[3]=0;kernel[4]=1;kernel[5]=0;
			kernel[6]=0;kernel[7]=0;kernel[8]=0;
			//Blur
			//1.0 / 16, 1 / 8, 1.0 / 16,
			//1.0 / 8, 1.0 / blurIntesity, 1.0 / 8,
			//1.0 / 16, 1.0 / 8, 1.0 / 16  

		
	}
     	if(filter == false)
	{

		//Edges 
		kernel[0]=1;kernel[1]=1;kernel[2]=1;
		kernel[3]=1;kernel[4]=-8;kernel[5]=1;
		kernel[6]=1;kernel[7]=1;kernel[8]=1;

		//Blur
		//1.0 / 16, 1 / 8, 1.0 / 16,
		//1.0 / 8, 1.0 / blurIntesity, 1.0 / 8,
		//1.0 / 16, 1.0 / 8, 1.0 / 16  
	}
   
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    
	// Exposure tone mapping
    vec3 mapped =  vec3(1.0) - exp(-col * exposure);
	  // gamma correction 
    mapped = pow(mapped, vec3(1.0 / gamma));

    FragColor = vec4(mapped, 1.0);
	 
}	