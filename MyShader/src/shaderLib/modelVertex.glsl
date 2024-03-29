//#version 330 core
//layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aNormal;
//layout (location = 2) in vec2 aTexCoords;
//
//out vec2 TexCoords;
//out vec3 normalv;
//out vec3 FragPos;
//
////uniform mat4 model;
////uniform mat4 view;
////uniform mat4 projection;
//uniform mat4 MVP;
//uniform mat4 model;
//
//void main()
//{
//    TexCoords = aTexCoords;    
//    //gl_Position = projection * view * model * vec4(aPos, 1.0);
//    gl_Position=MVP*vec4(aPos,1.0);
//    FragPos=vec3(model*vec4(aPos,1.0));
//}
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 MVP;

void main()
{
    TexCoords = aTexCoords;    
    //gl_Position = projection * view * model * vec4(aPos, 1.0);
    gl_Position=MVP*vec4(aPos,1.0);
}