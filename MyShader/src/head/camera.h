#pragma once
#include<iostream>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

class MyCamera
{

	//�ѱ任ȫ������camera��
public:
	MyCamera(const glm::vec3& position,const glm::vec3& direction,const glm::vec3& up);
	~MyCamera();
	//matrix
	inline glm::mat4 GetMVP() const { return MVP; }
	inline glm::mat4 GetModelMatrix() const { return Model; }
	inline glm::mat4 GetVirwMatrix() const { return View; }
	inline glm::mat4 GetProjectionMatrix() const { return Projection; }
	inline glm::vec3 GetPosition()const { return position; }
	//update
	void UpdateModel(const glm::mat4& newModel);
	void UpdateView(const glm::mat4& newView);
	void UpdateProjection(const glm::mat4& projection);
	void UPdateMVP();//ÿ���ڸ�������Ĳ���֮��Ҫ���øú���




private:
	glm::mat4 MVP, Model, View, Projection;
	glm::vec3 right, up,position;

};


