#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 anormal;

//out vec2 OTextCoord;
out vec3 normalv;
out vec3 FragPos;

uniform mat4 MVP;
//uniform mat4 trans;
uniform mat4 model;

void main()
{

	 gl_Position = MVP*vec4(aPos.x, aPos.y, aPos.z, 1.0);
	 //gl_Position = trans*vec4(aPos.x, aPos.y, aPos.z, 1.0);
	 //OTextCoord=textCoord;
	 FragPos=vec3(model*vec4(aPos,1.0));
	 normalv=normalize(anormal);
}