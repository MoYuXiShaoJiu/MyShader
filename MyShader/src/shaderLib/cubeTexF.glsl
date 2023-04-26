#version 330 core
in vec3 TexCoords; // ����3D��������ķ�������
uniform samplerCube cubemap; // ��������ͼ�����������
out vec4 FragColor;
void main()
{             
    FragColor = texture(cubemap, TexCoords);
}