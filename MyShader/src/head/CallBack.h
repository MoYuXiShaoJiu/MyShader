#pragma once
#include<GLFW/glfw3.h>
#include<iostream>

/*
* 实际上这个部分如果要想维持封装的话
* 就需要使用event 
* 否则始终需要把一些东西暴露在外面
*/

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		std::cout << "press q" << std::endl;
	}


}



void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{



}