#include"window.h"

void MyWindow::MakeWindowCurrent()
{
	glfwMakeContextCurrent(m_window);
}

bool MyWindow::WindowShouldClose()
{
	return glfwWindowShouldClose(m_window);
}

GLFWwindow* MyWindow::GetWindowPtr()
{
	return m_window;
}

void MyWindow::WindowInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
}
