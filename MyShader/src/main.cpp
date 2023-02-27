#include<iostream>
#include"head/window.h"
#include"head/shader.h"

using namespace std;

float vertex[] =
{
    0.5,0.5,0.0,
    -0.5,0.5,0.0,
    0.5,-0.5,0.0
};

unsigned int index[] = { 0,1,2 };

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    MyWindow mWindow(screenWidth, screenHeight, "shader");
    mWindow.MakeWindowCurrent();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "fail to initialize glad\n" << std::endl;
        return -1;
    }
    glViewport(0, 0, screenWidth, screenHeight);//�ӿ�

    MyShader mShader("src/shaderLib/vertex.glsl", "src/shaderLib/fragment.glsl");
    mShader.Bind();

    unsigned int vao, vbo;
    //��vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //��ɲ��ҽ��

    
    
    while (!mWindow.WindowShouldClose())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�������

        //bind and draw
        mShader.Bind();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //over

        glfwSwapBuffers(mWindow.GetWindowPtr());//ʹ��˫���壬�����ǽ���ǰ�󻺳�
        glfwPollEvents();//��鴥���¼�
    }
    return 0;


}