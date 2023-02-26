#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
class MyWindow
{
public:
	MyWindow(const int width,const int height,const char* name)
		:width(width),height(height)
	{
		WindowInit();
		m_window = glfwCreateWindow(width, height, name, nullptr, nullptr);
		if (m_window == NULL)
		{
			std::cout << "creat window fail\n" << std::endl;
			glfwTerminate();
		}

	}
	~MyWindow()
	{
		glfwDestroyWindow(m_window);
	}
	//
	void MakeWindowCurrent();
	bool WindowShouldClose();
	GLFWwindow* GetWindowPtr();
private:
	int width, height;
	GLFWwindow* m_window = nullptr;
	void WindowInit();

};



