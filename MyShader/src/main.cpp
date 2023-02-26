#include<iostream>
#include"window.h"

using namespace std;

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
    glViewport(0, 0, screenWidth, screenHeight);


    while (!mWindow.WindowShouldClose())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�������

        glfwSwapBuffers(mWindow.GetWindowPtr());//ʹ��˫���壬�����ǽ���ǰ�󻺳�
        glfwPollEvents();//��鴥���¼�
    }
    return 0;


}