#include"game.hpp"
#include"../../engine/renderer/window.hpp"
#include"../../engine/gui/gui_manager.hpp"
#include"../module/gui/debug_console.hpp"
#include"../module/gui/menu.hpp"
#include"../../engine/tool/resource_manager.hpp"
#include<GLFW/glfw3.h>
#include<map>
#include<string>
struct MainData
{
	float red;
	float green;
	float blue;
	float alpha;
};
struct IsPress
{
	bool escapeDown;
	bool f1Down;
};
void SetSettings(ImageSettings& imageSettings, Window& window)
{
	window.SetFullScreen(imageSettings.isFullScreen);
	glfwSwapInterval(imageSettings.isResetSync);
}
int main()
{
	Window window;
	GuiManager guiManager;
	MenuState menuState;
	IsPress isPress;
	ImageSettings imageSettings;
	Game game;
	MainData mainData;
	ApplyState applyState;
	std::vector<Resolution> resolutions;
	std::vector<std::string> displayResolutions;
	std::string settingsPath;
	bool debugConsoleState;
	bool freeMode;
	float lastTime = glfwGetTime();
	{
		std::map<std::string, std::string> resourcesPath = resourcemanager::LoadFromIni("resources/config/module/core/path_main.ini");
		std::map<std::string, std::string> loadData = resourcemanager::LoadFromIni(resourcesPath["main_path"]);
		std::map<std::string, std::string> loadSettingsData = resourcemanager::LoadFromIni(resourcesPath["settings_path"]);
		settingsPath = resourcesPath["settings_path"];
		window.Initialize(resourcesPath["window_data_path"]);
		guiManager.Create(window.GetHandle(), resourcesPath["gui_path"]);
		game.Create(resourcesPath["game_path"]);
		mainData.red = std::stof(loadData["red"]);
		mainData.green = std::stof(loadData["green"]);
		mainData.blue = std::stof(loadData["blue"]);
		mainData.alpha = std::stof(loadData["alpha"]);
		isPress.escapeDown = false;
		isPress.f1Down = false;
		menuState.isStart = false;
		menuState.isDead = false;
		menuState.isPause = false;
		menuState.isPlaying = false;
		menuState.isSettings = false;
		menuState.isQuit = false;
		debugConsoleState = false;
		freeMode = false;
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		int modeCount;
		const GLFWvidmode* modes = glfwGetVideoModes(monitor, &modeCount);
		resolutions.emplace_back(modes[0].width, modes[0].height);
		for (int i = 1; i < modeCount; i++)
		{
			if (modes[i].width != modes[i - 1].width || modes[i].height != modes[i - 1].height)
			{
				resolutions.emplace_back(modes[i].width, modes[i].height);
			}
		}
		for (const Resolution& resolution : resolutions)
		{
			displayResolutions.emplace_back(std::to_string(resolution.width) + "x" + std::to_string(resolution.height));
		}
		imageSettings.isFullScreen = std::stoi(loadSettingsData["full_screen"]);
		imageSettings.isResetSync = std::stoi(loadSettingsData["reset_sync"]);
		applyState.isWindow = false;
		applyState.windowChoose = std::stoi(loadSettingsData["window_choose"]);
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while (!glfwWindowShouldClose(window.GetHandle()))
	{
		glfwPollEvents();
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		if (deltaTime > 0.033f)
		{
			deltaTime = 0.033f;
		}
		if (glfwGetKey(window.GetHandle(), GLFW_KEY_ESCAPE) == GLFW_PRESS && isPress.escapeDown == false && menuState.isSettings == false)
		{
			isPress.escapeDown = true;
			if (menuState.isPause == false)
			{
				menuState.isPause = true;
			}
			else
			{
				menuState.isPause = false;
			}
		}
		else if(glfwGetKey(window.GetHandle(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
		{
			isPress.escapeDown = false;
		}
		if (glfwGetKey(window.GetHandle(), GLFW_KEY_F1) == GLFW_PRESS && isPress.f1Down == false)
		{
			isPress.f1Down = true;
			if (debugConsoleState == false)
			{
				debugConsoleState = true;
			}
			else
			{
				debugConsoleState = false;
			}
		}
		else if (glfwGetKey(window.GetHandle(), GLFW_KEY_F1) != GLFW_PRESS)
		{
			isPress.f1Down = false;
		}
		guiManager.NewFrame();
		menu::Render(menuState, imageSettings, displayResolutions, applyState);
		if (menuState.isPlaying == true && debugConsoleState == true)
		{
			debugconsole::Render(game.GetDinosaurData(), game.GetGroundData(), game.GetObstacleData(), game.GetCameraDebug(), freeMode, menuState.isDead);
		}
		window.SetSize(resolutions[applyState.windowChoose].width, resolutions[applyState.windowChoose].height, applyState.isWindow);
		SetSettings(imageSettings, window);
		if (menuState.isStart == true)
		{
			menuState.isStart = false;
			game.SetUp();
			menuState.isPlaying = true;
			menuState.isDead = false;
		}
		if (menuState.isPlaying == true && menuState.isPause == false && debugConsoleState == false)
		{
			game.Update(window.GetHandle(), deltaTime, menuState, freeMode);
		}
		glClearColor(mainData.red, mainData.green, mainData.blue, mainData.alpha);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		if (menuState.isPlaying == true)
		{
			game.Render();
		}
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		guiManager.UpdatePlatformWindows();
		glfwSwapBuffers(window.GetHandle());
		if (menuState.isQuit == true)
		{
			glfwSetWindowShouldClose(window.GetHandle(), true);
		}
	}
	game.Destroy();
	guiManager.Destroy();
	std::map<std::string, std::string> saveSettings;
	saveSettings.emplace("window_choose", std::to_string(applyState.windowChoose));
	saveSettings.emplace("full_screen", std::to_string(imageSettings.isFullScreen));
	saveSettings.emplace("reset_sync", std::to_string(imageSettings.isResetSync));
	resourcemanager::SaveToIni(settingsPath, saveSettings);
	window.Destroy();
}