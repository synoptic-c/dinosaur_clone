#pragma once
#include<imgui.h>
#include<vector>
#include<string>
struct Resolution
{
	int width;
	int height;
};
struct ImageSettings
{
	bool isFullScreen;
	bool isResetSync;
};
struct ApplyState
{
	int windowChoose;
	bool isWindow;
};
struct MenuState
{
	bool isStart;
	bool isDead;
	bool isPause;
	bool isPlaying;
	bool isSettings;
	bool isQuit;
};
namespace menu
{
	void Render(MenuState& menuState, ImageSettings& imageSettings, std::vector<std::string>& displayResolutions, ApplyState& applyState);
}