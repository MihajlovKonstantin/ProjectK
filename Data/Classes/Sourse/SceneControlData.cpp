#include "Data/Classes/Header/SceneControlData.h"

bool SceneControlData::GetEditMode()
{
	return editMode;
}

void SceneControlData::SetEditMode(bool input)
{
	editMode = input;
}

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
