#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3  normalv;
in vec3 FragPos;

uniform sampler2D diffuse1;
uniform sampler2D spec1;

uniform vec3 light;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{    
    //float 
    
   // FragColor = texture(diffuse1, TexCoords);
    vec3 objColor=vec3(texture(diffuse1,TexCoords));
	//环境光
	float ambientStrength=0.8;
	vec3 ambientLight=ambientStrength*light*objColor;
	//漫反射
	vec3 lightDir=normalize(lightPos-FragPos);
	float diff=max(dot(normalv,lightDir),0.0);
	vec3 diffuse=diff*light*objColor;
	//镜面反射
	float specularStrength=0.5;
	vec3 viewDir=normalize(viewPos-FragPos);
	vec3 reflectDir=reflect(-lightDir,normalv);
	float spec=pow(max(dot(viewDir,reflectDir),0.0),64);
	vec3 specLight=specularStrength*spec*light*vec3(texture(spec1,TexCoords));

	//总的
	//FragColor=texture(ourText,OTextCoord);	
	///vec3 result=ambientLight+diffuse+specLight;
	vec3 result=specLight;
	//vec3 result=diffuse;
	FragColor=vec4(result,1.0);
}