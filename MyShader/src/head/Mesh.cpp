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
    //定义diffuse为漫反射贴图
    //定义spec为镜面反射贴图
    unsigned int diffuseN = 1;
    unsigned int specN = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number,name;
        //获取纹理的编号和类型
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
        //我们需要在shader中设置好material+name+bumber的struct
        shader.UpLoadUniformInt(name + number,i);
        //std::cout << name + number << std::endl;
        std::cout << "texture num is" << textures.size() << std::endl;
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    //绘制网格
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

    // 顶点位置
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // 顶点法线
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // 顶点纹理坐标
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    //offsetof 是struct的预处理指令，可知找到指定成员的偏移量
    glBindVertexArray(0);
}
