#include"Mesh.h"
#include<iostream>
Mesh::Mesh(const std::vector<Vertex>& vertex, const std::vector<unsigned int>& index, const std::vector<Texture>& tex)
	:vertices(vertex), indices(index), textures(tex)
{
	setupMesh();
}


Mesh::~Mesh()
{
}

void Mesh::Draw( MyShader& shader)
{
    //����diffuseΪ��������ͼ
    //����specΪ���淴����ͼ
    unsigned int diffuseN = 1;
    unsigned int specN = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number,name;
        //��ȡ����ı�ź�����
        if (textures[i].type == TexType::diffuse)
        {
            number = std::to_string(diffuseN++);
            name = "diffuse";
        }
        else if (textures[i].type == TexType::spec)
        {
            number = std::to_string(specN++);
            name = "spec";
        }
        else
        {
            std::cout << "Error type of tex" << std::endl;
        }
        //������Ҫ��shader�����ú�material+name+bumber��struct
        shader.UpLoadUniformInt(name + number,i);
        //std::cout << name + number << std::endl;
        std::cout << "texture num is" << textures.size() << std::endl;
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    //��������
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);

    // ����λ��
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // ���㷨��
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // ������������
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    //offsetof ��struct��Ԥ����ָ���֪�ҵ�ָ����Ա��ƫ����
    glBindVertexArray(0);
}
