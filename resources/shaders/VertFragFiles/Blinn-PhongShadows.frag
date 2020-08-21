#version 330 core
out vec4 FragColor;

 
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

 struct	Material
 {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
};

struct PointLight {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

#define NR_POINT_LIGHTS 2
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform PointLight pointLight;
uniform Material material;


uniform samplerCube depthMap;

//uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float far_plane;
uniform bool displayDepth;

uniform bool shadows;
// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float ShadowCalculation(PointLight pointLight);
vec3 pointLightCalc(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir, bool activeShadow);



void main()
{ 
// properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result = vec3(0.0,0.0,0.0); 


	result = pointLightCalc(pointLight, norm, FragPos, viewDir, shadows);
	FragColor = vec4(result, 1.0);

}


float ShadowCalculation(PointLight pointLight)
{
    // get vector between fragment position and light position
    vec3 fragToLight = FragPos - pointLight.position;
     //use the fragment to light vector to sample from the depth map    
     float closestDepth = texture(depthMap, fragToLight).r;
     //it is currently in linear range between [0,1], let's re-transform it back to original depth value
     closestDepth *= far_plane;
     //now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    
	//test for shadows
	float bias = 0.15; // we use a much larger bias since depth is now in [near_plane, far_plane] range
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;

	if(currentDepth > 8.0f && shadow != 0.0f)
	{
		//PCF
		shadow = 0.0f;
		int samples = 20;
		float viewDistance = length(viewPos - FragPos);
		float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
		for(int i = 0; i < samples; ++i)
			{
			float closestDepth = texture(depthMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
			closestDepth *= far_plane;   // undo mapping [0;1]
			if(currentDepth - bias > closestDepth)
				shadow += 1.0;
			}
		shadow /= float(samples);
	} 
    
// display closestDepth as debug (to visualize depth cubemap)
	if(displayDepth){
		FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    
	}
        
    return shadow;
}

vec3 pointLightCalc(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir, bool activeShadow)
{

	//Direciton of light based of light sources position unit v ector
    vec3 lightDir = normalize(pointLight.position - fragPos);
	// ambient
    vec3 ambient = pointLight.ambient * vec3(texture(material.diffuse, TexCoords).rgb);
  	
    // diffuse 
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = pointLight.diffuse * diff * vec3(texture(material.diffuse, TexCoords).rgb);

    // specular
	float spec = 0.0;
	vec3 halfwayDir = normalize(lightDir+viewDir);  
	spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = pointLight.specular * spec * vec3(texture(material.specular, TexCoords).rgb);

    //Point Light Attenuation

	float distance = length(pointLight.position -FragPos);
	float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic *(distance *distance));
 	
	float shadows = ShadowCalculation(pointLight);
	vec3 lighting = vec3(0.0f,0.0f,0.0f);
	

	lighting = (ambient * (diffuse + specular))*attenuation;
	
	if (activeShadow == true)
	{
	lighting = (ambient+(1.0f- shadows) * (diffuse + specular))*attenuation;
	}
	return lighting;
    
}