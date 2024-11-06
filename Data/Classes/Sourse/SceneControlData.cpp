#include "Pch.h"
#include "Data/Classes/Header/SceneControlData.h"

int SceneControlData::GetCurrentScene()
{
	return currentScene;
}

void SceneControlData::SetCurrentScene(int input)
{
	currentScene = input;
}

int SceneControlData::GetCurrentMenu()
{
	return currentMenu;
}

void SceneControlData::SetCurrentMenu(int input)
{
	currentMenu = input;
}
