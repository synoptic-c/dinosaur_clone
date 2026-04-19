#pragma once
#include"../gui/menu.hpp"
#include"input_dinosaur.hpp"
#include"../scene/camera.hpp"
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<iostream>
namespace inputhandler
{
	void InputPlayer(GLFWwindow* window, InputDinosaur& inputDinosaur, MenuState& menuState, bool& freeMode);
}