#version 330 core
in vec2 OTextCoord;
out vec4 FragColor;

uniform sampler2D ourText;
void main()
{
	//FragColor=vec4(0.3,0.6,0.9,1.0);
	FragColor=texture(ourText,OTextCoord);	
}