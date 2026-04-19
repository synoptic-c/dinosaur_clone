#include"menu.hpp"
void menu::Render(MenuState& menuState, ImageSettings& imageSettings, std::vector<std::string>& displayResolutions, ApplyState& applyState)
{
	if (menuState.isPlaying == false && menuState.isSettings == false)
	{
		ImGui::Begin("Menu");
		menuState.isStart = ImGui::Button("Start");
		menuState.isSettings = ImGui::Button("Settings");
		menuState.isQuit = ImGui::Button("Quit");
		ImGui::End();
	}
	if (menuState.isPlaying == true && menuState.isSettings == false)
	{
		if (menuState.isPause == true)
		{
			ImGui::Begin("Pause");
			menuState.isPause = !ImGui::Button("back");
			menuState.isStart = ImGui::Button("Reset");
			menuState.isSettings = ImGui::Button("Settings");
			menuState.isPlaying = !ImGui::Button("Return");
			ImGui::End();
		}
	}
	if (menuState.isSettings == true)
	{
		ImGui::Begin("Settings");
		if (ImGui::BeginCombo("Resolution", displayResolutions[applyState.windowChoose].c_str()))
		{
			for (int i = 0; i < displayResolutions.size(); i++)
			{
				if (ImGui::Selectable(displayResolutions[i].c_str()))
				{
					applyState.windowChoose = i;
					applyState.isWindow = true;
				}
			}
			ImGui::EndCombo();
		}
		ImGui::Checkbox("FullScreen", &imageSettings.isFullScreen);
		ImGui::Checkbox("ResetSync", &imageSettings.isResetSync);
		menuState.isSettings = !ImGui::Button("back");
		ImGui::End();
	}
}