#pragma once
#include<glad/glad.h>
#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>
#include<GLFW/glfw3.h>
#include<map>
#include<string>
#include"../tool/resource_manager.hpp"
class GuiManager
{
private:
	std::map<std::string, std::string> m_resourcesPath;
public:
	void Create(GLFWwindow* window, std::string loadPath);
	void NewFrame();
	void UpdatePlatformWindows();
	void Destroy();
};