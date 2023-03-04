#version 330 core
in vec2 OTextCoord;
in vec3 normalv;
in vec3 FragPos;


out vec4 FragColor;

uniform vec3 light;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D ourText;
uniform sampler2D specText;

//可以使用一个struct来指定这些uniform




void main()
{
	//FragColor=vec4(0.3,0.6,0.9,1.0);
	vec3 objColor=vec3(texture(ourText,OTextCoord));
	//环境光
	float ambientStrength=0.1;
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
	vec3 specLight=specularStrength*spec*light*vec3(texture(specText,OTextCoord));

	//总的
	//FragColor=texture(ourText,OTextCoord);	
	vec3 result=ambientLight+diffuse+specLight;
	FragColor=vec4(result,1.0);
}