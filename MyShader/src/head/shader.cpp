#include "shader.h"
#include<vector>
#include<iostream>
#include<glm/gtc/type_ptr.hpp>
std::string MyShader::PathToSrc(const std::string& path)
{
	return std::string();
}

MyShader::MyShader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	//test
	std::string vertexSource = PathToSrc(vertexSrc);// Get source code for vertex shader.
	std::string fragmentSource = PathToSrc(fragmentSrc);// Get source code for fragment shader.


	// Read our shaders into the appropriate buffers
	//std::string vertexSource = vertexSrc;// Get source code for vertex shader.
	//std::string fragmentSource = fragmentSrc;// Get source code for fragment shader.

		// Create an empty vertex shader handle
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar* source = (const GLchar*)vertexSource.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(vertexShader);

		// Use the infoLog as you see fit.

		// In this simple program, we'll just leave
		std::cout << "vertex shader compile failed!" << std::endl;
		std::cout <<  infoLog.data()<<std::endl;
		return;
	}

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = (const GLchar*)fragmentSource.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		// Use the infoLog as you see fit.
		std::cout << "fragment shader compile failed!" << std::endl;
		std::cout << infoLog.data() << std::endl;
		// In this simple program, we'll just leave
		return;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	this->m_RendererId = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(m_RendererId, vertexShader);
	glAttachShader(m_RendererId, fragmentShader);

	// Link our program
	glLinkProgram(m_RendererId);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(m_RendererId, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_RendererId, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_RendererId, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_RendererId);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Use the infoLog as you see fit.
		std::cout << "shader link failed!"<<std::endl;
		std::cout << infoLog.data()<<std::endl;
		// In this simple program, we'll just leave
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(m_RendererId, vertexShader);
	glDetachShader(m_RendererId, fragmentShader);

}

MyShader::~MyShader()
{
	glDeleteProgram(this->m_RendererId);
}

void MyShader::Bind() const
{
	glUseProgram(m_RendererId);
}

void MyShader::UnBind() const
{
	glUseProgram(0);
}

void MyShader::UpLoadUniformMat4(const std::string& name, const glm::mat4& m_matrix)
{

	int location = glGetUniformLocation(m_RendererId, name.c_str());
	if (location == -1)
	{
		std::cout<<"up load mat4 fail!"<<std::endl;
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_matrix));
}

void MyShader::UpLoadUniformMat3(const std::string& name, const glm::mat3& m_matrix)
{

	int location = glGetUniformLocation(m_RendererId, name.c_str());
	if (location == -1)
	{
		std::cout << "up load mat3 fail!" << std::endl;
	}
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(m_matrix));
}

void MyShader::UpLoadUniformInt(const std::string& name, const int num)
{
	int location = glGetUniformLocation(m_RendererId, name.c_str());
	if (location == -1)
	{
		std::cout << "up load int fail!" << std::endl;
	}
	glUniform1i(location, num);
}

void MyShader::UPLoadUniformFloat2(const std::string& name, const glm::vec2& m_vec2)
{
	int location = glGetUniformLocation(m_RendererId, name.c_str());
	if (location == -1)
	{
		std::cout << "up load float2 fail!"<<std::endl;
	}
	glUniform2f(location, m_vec2.x, m_vec2.y);
}

void MyShader::UpLoadUniformFloat3(const std::string& name, const glm::vec3& m_vec3)
{
	int location = glGetUniformLocation(m_RendererId, name.c_str());
	if (location == -1)
	{
		std::cout << "up load float3 fail!" << std::endl;
	}
	glUniform3f(location, m_vec3.x, m_vec3.y, m_vec3.z);
}

void MyShader::UpLoadUniformFloat4(const std::string& name, const glm::vec4& m_vec3)
{
	int location = glGetUniformLocation(m_RendererId, name.c_str());
	if (location == -1)
	{
		std::cout << "up load float4 fail!" << std::endl;
	}
	glUniform4f(location, m_vec3.x, m_vec3.y, m_vec3.z, m_vec3.w);
}
