#include<iostream>
#include"head/window.h"
#include"head/shader.h"
#include"head/Texture.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"head/camera.h"
#include"head/Tool.h"
#include"head/CallBack.h"

// 下面这行代码就需要改为:
// glm::mat4 trans = glm::mat4(1.0f)
using namespace std;


float square[] = {
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};


MyCamera mCamera(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
int main()
{
    const int screenWidth = 1600;
    const int screenHeight = 900;
    MyWindow mWindow(screenWidth, screenHeight, "shader");
    mWindow.MakeWindowCurrent();
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "fail to initialize glad\n" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, screenWidth, screenHeight);//视口
    glfwSetKeyCallback(mWindow.GetWindowPtr(),key_callback);
    glfwSetCursorPosCallback(mWindow.GetWindowPtr(), cursor_position_callback);
    ///////////////////////////////////////////////////////////////////////////////////
    MyShader mShader("src/shaderLib/vertex.glsl", "src/shaderLib/fragment.glsl");
    mShader.Bind();
    
    //texture
    //Texture mTexture("src/texture/container.jpg");
    //mTexture.BindTexture();

    MyTexture DiffuseTex("src/texture/container2.png");
    DiffuseTex.BindTexture();

    MyTexture SpecText("src/texture/container2_specular.png");
    SpecText.BindTexture(1);
    

    //vao vbo
    unsigned int vao, vbo,ibo;
    //绑定vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    //vbo
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 8, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float) * 8, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(float) * 8, (void*)(6 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
 /*   glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);*/
    glBindVertexArray(0);
    //完成并且解绑
    
    //light cube
    MyShader lightShader("src/shaderLib/lightVertex.glsl", "src/shaderLib/lightFrag.glsl");
    unsigned int lightVao;
    glGenVertexArrays(1, &lightVao);
    glBindVertexArray(lightVao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 6, (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glm::mat4 lightMove(1.0);

    glm::vec3 change = glm::vec3(1, 0.5, -0.5);
    lightMove = glm::translate(lightMove, change);
    lightMove = glm::scale(lightMove, glm::vec3(0.4f));
    //////////////////////////////////////////////////

    //////////////////////////light//////////////////////////
    glm::vec3 light(1.0);
    glm::vec3 lightPos =change;
    /////////////////////////////////////////////////////////

    glm::mat4 lightMoveM = mCamera.GetProjectionMatrix() * mCamera.GetViewMatrix() * lightMove;
   
    while (!mWindow.WindowShouldClose())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除缓存
        ///////////////////////////////////////////////////////////////
        //bind 
        mShader.Bind();
        mShader.UpLoadUniformMat4("MVP",mCamera.GetMVP());
        mShader.UpLoadUniformFloat3("light", light);
        mShader.UpLoadUniformFloat3("lightPos", lightPos);
        mShader.UpLoadUniformMat4("model", mCamera.GetModelMatrix());
        mShader.UpLoadUniformFloat3("viewPos", mCamera.GetPosition());
        mShader.UpLoadUniformInt("ourText", 0);
        mShader.UpLoadUniformInt("specText", 1);
        glBindVertexArray(vao);
        //纹理
        //mTexture.BindTexture();
        glActiveTexture(GL_TEXTURE0);
        DiffuseTex.BindTexture();
        glActiveTexture(GL_TEXTURE1);
        SpecText.BindTexture(1);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //////////////////////////////////////////////////////
        //light
        lightShader.Bind();
        lightShader.UpLoadUniformMat4("lightMVP", lightMoveM);
        lightMoveM = mCamera.GetProjectionMatrix() * mCamera.GetViewMatrix() * lightMove;
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //over
        ////////////////////////////////////////////////////////////////////////

        glfwSwapBuffers(mWindow.GetWindowPtr());//使用双缓冲，这里是交换前后缓冲
        glfwPollEvents();//检查触发事件
    }
    return 0;


}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        glm::mat4 newM = glm::translate(mCamera.GetViewMatrix(), glm::vec3(0.0,0.0,0.5));
        mCamera.UpdateView(newM);
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        glm::mat4 newM = glm::translate(mCamera.GetViewMatrix(), glm::vec3(0.0, 0.0, -0.5));
        mCamera.UpdateView(newM);
    }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        glm::mat4 newM = glm::translate(mCamera.GetViewMatrix(), glm::vec3(0.5, 0.0, 0.0));
        mCamera.UpdateView(newM);
    }
    else if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        glm::mat4 newM = glm::translate(mCamera.GetViewMatrix(), glm::vec3(-0.5, 0.0, 0.0));
        mCamera.UpdateView(newM);
    }
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS)//向上
    {
        glm::mat4 newM = glm::translate(mCamera.GetViewMatrix(), glm::vec3(0.0, -0.5, 0.0));
        mCamera.UpdateView(newM);
    }
    else if (key == GLFW_KEY_E && action == GLFW_PRESS)//向下
    {
        glm::mat4 newM = glm::translate(mCamera.GetViewMatrix(), glm::vec3(0.0, 0.5, 0.0));
        mCamera.UpdateView(newM);
    }
    



}



void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{



}

