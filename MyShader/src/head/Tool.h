#pragma once
#include<glm/glm.hpp>
#include<string>

class Tool
{
public:

	static glm::vec3 CameraDirection(const glm::vec3& Cameraposition, const glm::vec3& target);
	static void OutPutMat4(glm::mat4 matrix, const std::string& info);
	static void OutPutVec3(glm::vec3 vector, const std::string& info);


};


