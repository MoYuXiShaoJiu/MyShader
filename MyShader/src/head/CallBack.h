#pragma once
#include<GLFW/glfw3.h>
#include<iostream>

/*
* ʵ��������������Ҫ��ά�ַ�װ�Ļ�
* ����Ҫʹ��event 
* ����ʼ����Ҫ��һЩ������¶������
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