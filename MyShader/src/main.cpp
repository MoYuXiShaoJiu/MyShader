#include<iostream>
#include"head/window.h"
#include"head/shader.h"
#include"head/Texture.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"head/camera.h"
#include"head/Tool.h"
//#include"head/Model.h"


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
float cubeVertices[] = {
    // positions          // texture Coords
     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
float planeVertices[] = {
    // positions            // normals         // texcoords
        10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
       -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
       -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

        10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
       -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
        10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
};
float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};
float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

std::vector<std::string> CubeTexpath
{
    "src/texture/skybox/skybox/right.jpg",
    "src/texture/skybox/skybox/left.jpg",
    "src/texture/skybox/skybox/top.jpg",
    "src/texture/skybox/skybox/bottom.jpg",
    "src/texture/skybox/skybox/front.jpg",
    "src/texture/skybox/skybox/back.jpg"
};
float points[] = {
      -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 左上
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // 右上
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 右下
    -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // 左下
};

MyCamera mCamera(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);




int main()
{
    //init
    const int screenWidth = 1600;
    const int screenHeight = 900;
    MyWindow mWindow(screenWidth, screenHeight, "shader");
    mWindow.MakeWindowCurrent();
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "fail to initialize glad\n" << std::endl;
        return -1;
    }
    
    //glDepthFunc(GL_LESS);
    glViewport(0, 0, screenWidth, screenHeight);//视口
    glfwSetKeyCallback(mWindow.GetWindowPtr(),key_callback);
    glfwSetCursorPosCallback(mWindow.GetWindowPtr(), cursor_position_callback);
    /////////////////////////////////////////////////////////////////////////////////////////////
    //shader
    //MyShader DepthTestShader("src/shaderLib/depthTestV.glsl", "src/shaderLib/depthTestF.glsl");
    MyShader DepthTestShader("src/shaderLib/depthTestV.glsl", "src/shaderLib/depthTestF.glsl");
    MyShader skyBox("src/shaderLib/cubeTexV.glsl", "src/shaderLib/cubeTexF.glsl");
    MyShader normalDisplay("src/shaderLib/normalDisplayV.glsl", "src/shaderLib/normalDisplayG.glsl",
        "src/shaderLib/normalDisplayF.glsl");
    //Texture
    MyTexture container("src/texture/container.jpg");
    MyTexture metal("src/texture/metal.png");
    CubeTexture skyBoxTex(CubeTexpath);
    // cube VAO
    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // plane VAO
    unsigned int planeVAO, planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // screen quad VAO
    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    //skybox
    unsigned int skyBoxVAO, skyBoxVBO;
    glGenVertexArrays(1, &skyBoxVAO);
    glGenBuffers(1, &skyBoxVBO);
    glBindVertexArray(skyBoxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyBoxVAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * (sizeof(float)), (void*)0);


    
    DepthTestShader.Bind();
    DepthTestShader.UpLoadUniformInt("skybox", 0);
    skyBox.Bind();
    skyBox.UpLoadUniformInt("cubemap", 0);
    glEnable(GL_DEPTH_TEST);
    while (!mWindow.WindowShouldClose())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除缓存

        DepthTestShader.Bind();
        glm::mat4 model = glm::mat4(1.0);
        glm::mat4 view = mCamera.GetViewMatrix();
        glm::mat4 projection = mCamera.GetProjectionMatrix();
        DepthTestShader.UpLoadUniformMat4("model", model);
        DepthTestShader.UpLoadUniformMat4("view", view);
        DepthTestShader.UpLoadUniformMat4("projection", projection);
        // floor
        //glBindVertexArray(planeVAO);
        //metal.BindTexture();
        //DepthTestShader.UpLoadUniformMat4("model", glm::mat4(1.0f));
       //glDrawArrays(GL_TRIANGLES, 0, 6);
        //glBindVertexArray(0);
         
        //cube
        glBindVertexArray(cubeVAO);
        glActiveTexture(GL_TEXTURE0);
        //container.BindTexture();
        skyBoxTex.BindTexture();
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        DepthTestShader.UpLoadUniformMat4("model", model);
        DepthTestShader.UpLoadUniformFloat3("camPos", mCamera.GetPosition());
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        DepthTestShader.UpLoadUniformMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        normalDisplay.Bind();
        normalDisplay.UpLoadUniformMat4("model", model);
        normalDisplay.UpLoadUniformMat4("view", view);
        normalDisplay.UpLoadUniformMat4("projection", projection);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //skybox

        //glDepthMask(GL_FALSE);
        //glDepthFunc(GL_LEQUAL);
        //skyBox.Bind();
        //view = glm::mat4(glm::mat3(mCamera.GetViewMatrix()));
        //skyBox.UpLoadUniformMat4("view", view);
        //skyBox.UpLoadUniformMat4("projection", mCamera.GetProjectionMatrix());
        //glBindVertexArray(skyBoxVAO);
        //glActiveTexture(GL_TEXTURE0);
        //skyBoxTex.BindTexture();
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //glBindVertexArray(0);
        ////glDepthMask(GL_TRUE);
        //glDepthFunc(GL_LESS);

        glfwSwapBuffers(mWindow.GetWindowPtr());//使用双缓冲，这里是交换前后缓冲
        glfwPollEvents();//检查触发事件

    }
    
    //Geo test
    //unsigned int GeoVAO, GeoVBO;
    //glGenVertexArrays(1, &GeoVAO);
    //glBindVertexArray(GeoVAO);
    //glGenBuffers(1, &GeoVBO);
    //glBindBuffer(GL_ARRAY_BUFFER, GeoVBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

    //MyShader GeoShader("src/shaderLib/GeoV.glsl", "src/shaderLib/GeoG.glsl", "src/shaderLib/GeoF.glsl");
    ////MyShader GeoShader("src/shaderLib/GeoV.glsl", "src/shaderLib/GeoF.glsl");

    //while (!glfwWindowShouldClose(mWindow.GetWindowPtr()))
    //{
    //    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除缓存
    //    GeoShader.Bind();
    //    glBindVertexArray(GeoVAO);
    //    glDrawArrays(GL_POINTS, 0, 4);
    //    glfwSwapBuffers(mWindow.GetWindowPtr());//使用双缓冲，这里是交换前后缓冲
    //    glfwPollEvents();//检查触发事件
    //}


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

