#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout (location=2) in vec2 aTexCoord;


out vec3 Normal;
out vec2 TexCoord;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	
	TexCoord=aTexCoord;
	//Normal=vec3(view*model*vec4(aNormal,1.0));
	Normal=aNormal;
	//FragPos=vec3(view*model*vec4(aPos,1.0));
	FragPos=aPos;
	gl_Position=projection*view*model*vec4(aPos,1.0);


}