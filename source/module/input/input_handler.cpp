#include"input_handler.hpp"
void inputhandler::InputPlayer(GLFWwindow* window, InputDinosaur& inputDinosaur, MenuState& menuState, bool& freeMode)
{
	if (menuState.isDead == false)
	{
		if (freeMode == false)
		{
			inputDinosaur.walk = 1;
		}
		else
		{
			inputDinosaur.walk = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) - (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
		}
		inputDinosaur.jump = (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);
	}
	else
	{
		inputDinosaur.walk = 0;
		inputDinosaur.jump = 0;
	}
	//inputDinosaur.down = (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS);
}