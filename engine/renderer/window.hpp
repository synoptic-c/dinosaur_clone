#pragma once
#include"../tool/resource_manager.hpp"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<map>
struct WindowData
{
	int width;
	int height;
	int x;
	int y;
	int top;
	std::string title;
};
class Window
{
private:
	GLFWwindow* m_handle;
	std::string m_path;
	WindowData m_windowData;
public:
	void Initialize(const std::string& loadPath);
	void SetSize(int width, int height, bool& isWindow);
	void SetFullScreen(bool isFullScreen);
	GLFWwindow* GetHandle();
	int GetWidth();
	int GetHeight();
	void Destroy();
};