#pragma once
#include "Pch.h"
class SceneControlData
{
	int currentScene;
	int currentMenu;
	bool editMode = false;
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
	bool GetEditMode();
	void SetEditMode(bool input);
	int GetCurrentScene();
	void SetCurrentScene(int input);
	int GetCurrentMenu();
	void SetCurrentMenu(int input);
};

