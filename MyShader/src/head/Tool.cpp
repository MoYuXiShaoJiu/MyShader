#include"Tool.h"
#include<iostream>
#include<glm/ext.hpp>
#include<glm/gtx/string_cast.hpp>


glm::vec3 Tool::CameraDirection(const glm::vec3& Cameraposition,const glm::vec3& target)
{
	return target-Cameraposition;
}

void Tool::OutPutMat4(glm::mat4 matrix,const std::string& info)
{
	std::cout << info << std::endl;
	std::cout << glm::to_string(matrix) << std::endl;
}

void Tool::OutPutVec3(glm::vec3 vector, const std::string& info)
{
	std::cout << info << std::endl;
	std::cout << glm::to_string(vector) << std::endl;

}
