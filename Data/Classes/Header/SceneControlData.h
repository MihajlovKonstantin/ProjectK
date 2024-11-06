#pragma once
class SceneControlData
{
	int currentScene;
	int currentMenu;
public:
	enum Scenes
	{
		MainScene = 1,
		MenuScene = 2,
		SubScene = 3
	};
	enum Menus
	{
		SettingMenu = 1,
		Inventory = 2
	};
	int GetCurrentScene();
	void SetCurrentScene(int input);
	int GetCurrentMenu();
	void SetCurrentMenu(int input);
};

