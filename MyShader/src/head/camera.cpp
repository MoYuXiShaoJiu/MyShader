#include"camera.h"
#include<GLFW/glfw3.h>
/*
* 
* ע�⣬��ʱ��model��projection������ֱ��ָ����
* ֮����Ҫ����޸ĵ����
*/



MyCamera::MyCamera(const glm::vec3& position, const glm::vec3& destination, const glm::vec3& up)
{
	//Ҫע������ķ���ʵ�����Ǵ�
	//��z���Ǵ���Ļָ�����
	//��������֪�������ָ��z�Ḻ���򣬵�����ϣ����������(Direction Vector)ָ���������z��������
	//������ǽ��������˳�����Ǿͻ���һ��ָ���������z�᷽���������
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


