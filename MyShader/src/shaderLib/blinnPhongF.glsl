#version 330 core

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;


uniform sampler2D tex;

void main()
{
	vec3 color=texture(tex,TexCoord).rgb;
	//ambient
	vec3 ambient=color*0.2;
	//diff
	vec3 lightDir=normalize(lightPos-FragPos);
	vec3 normal=normalize(Normal);
	float diff=max(0.0,dot(lightDir,normal));
	vec3 diffColor=diff*color;
	//sepc
	float spec=0.0;
	vec3 viewDir=normalize(viewPos-FragPos);
	vec3 reflectDir=reflect(-viewDir,normal);

//	vec3 halfDir=normalize(lightDir+viewDir);
//	spec=pow(max(dot(normal,halfDir),0.0),32);

	vec3 newreflectDir = reflect(-lightDir, normal);
    spec = pow(max(dot(viewDir, newreflectDir), 0.0), 8.0);
	
	vec3 specular=vec3(0.3)*spec;
	FragColor=vec4(ambient+diffColor+specular,1.0);
	
}