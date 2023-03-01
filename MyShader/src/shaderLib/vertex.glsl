#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec2 textCoord;

out vec2 OTextCoord;

uniform mat4 MVP;
uniform mat4 trans;

void main()
{

	 gl_Position = MVP*vec4(aPos.x, aPos.y, aPos.z, 1.0);
	 //gl_Position = trans*vec4(aPos.x, aPos.y, aPos.z, 1.0);
	 OTextCoord=textCoord;

}