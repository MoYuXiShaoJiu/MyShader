#include"camera.h"
#include<GLFW/glfw3.h>
/*
* 
* 注意，此时的model和projection矩阵还是直接指定的
* 之后需要添加修改的入口
*/



MyCamera::MyCamera(const glm::vec3& position, const glm::vec3& destination, const glm::vec3& up)
{
	//要注意这里的方向实际上是从
	//正z轴是从屏幕指向你的
	//由于我们知道摄像机指向z轴负方向，但我们希望方向向量(Direction Vector)指向摄像机的z轴正方向。
	//如果我们交换相减的顺序，我们就会获得一个指向摄像机正z轴方向的向量：
	Model = glm::mat4(1.0);
	Model = glm::rotate(Model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
	View = glm::lookAt(position, destination, up);
	Projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
	MVP = Projection * View * Model;
	this->up = glm::normalize(up);
	this->right = glm::normalize(glm::cross(up, (destination - position)));
}

MyCamera::~MyCamera()
{

}

//update
void MyCamera::UpdateModel(const glm::mat4& newModel)
{
	Model = newModel;
	UPdateMVP();
}

void MyCamera::UpdateView(const glm::mat4& newView)
{
	View = newView;
	UPdateMVP();
}

void MyCamera::UpdateProjection(const glm::mat4& newprojection)
{
	Projection = newprojection;
	UPdateMVP();
}

void MyCamera::UPdateMVP()
{
	MVP = Projection*View*Model;
}

//get


