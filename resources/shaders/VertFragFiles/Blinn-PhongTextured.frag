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
struct Light 
{
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
    float linear;
    float quadratic;
};


uniform Material material;

uniform vec3 viewPos;

#define NR_POINT_LIGHTS 2
uniform Light pointLights[NR_POINT_LIGHTS];



vec3 pointLightCalc(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	// properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result = vec3(0.0,0.0,0.0); 
	 for(int i = 0; i < NR_POINT_LIGHTS; i++)
	 {
       result += pointLightCalc(pointLights[i], norm, FragPos, viewDir);    
	 }

   FragColor = vec4(result, 1.0);

} 


//Point Lights

vec3 pointLightCalc(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	
	//Direciton of light based of light sources position unit vector
    vec3 lightDir = normalize(light.position - FragPos);
	// ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords).rgb);
  	
    // diffuse 
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords).rgb);

    // specular
	float spec = 0.0;
	vec3 halfwayDir = normalize(lightDir+viewDir);  
	spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords).rgb);

    //Point Light Attenuation

	float distance = length(light.position -FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic *(distance *distance));
 	
    return (ambient * (diffuse+specular))*attenuation;
}