#pragma once
#include<string>
#include<glm/glm.hpp>
#include<glad/glad.h>
class MyShader
{
public:
	MyShader(const std::string& vertexSrc, const std::string& fragmentSrc);
	MyShader(const std::string& vertexSrc, const std::string& GeoSrc, const std::string& fragmentSrc);
	~MyShader();
	void Bind() const;
	void UnBind()const;
	//upload uniform
	void UpLoadUniformMat4(const std::string& name, const glm::mat4& m_matrix);
	void UpLoadUniformMat3(const std::string& name, const glm::mat3& m_matrix);

	void UpLoadUniformInt(const std::string& name, const int num);

	void UPLoadUniformFloat2(const std::string& name, const glm::vec2& m_vec2);
	void UpLoadUniformFloat3(const std::string& name, const glm::vec3& m_vec3);
	void UpLoadUniformFloat4(const std::string& name, const glm::vec4& m_vec3);




private:
	std::string vertexShader;
	std::string fragmentShader;
	unsigned int m_RendererId;
	std::string PathToSrc(const std::string& path);
};