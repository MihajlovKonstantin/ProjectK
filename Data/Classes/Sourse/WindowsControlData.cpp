#include "Data/Classes/Header/WindowsControlData.h"

bool WindowsControlData::IsPause()
{
	return Pause;
}

bool WindowsControlData::IsStarted()
{
	return GameStarted;
}

void WindowsControlData::Resume()
{
	Pause = false;
}

void WindowsControlData::PauseGame()
{
	Pause = true;
}

void WindowsControlData::Restart()
{
	GameStarted = false;
}

void WindowsControlData::StartGame()
{
	GameStarted = true;
}

float WindowsControlData::GetMusicVolume()
{
	return MusicVolume;
}

void WindowsControlData::SetMusicVolume(float input)
{
	MusicVolume = input;
}

int WindowsControlData::GetWindow()
{
	return CurrentWindows;
}

void WindowsControlData::SetWindow(int input)
{
	CurrentWindows = input;
}

void WindowsControlData::Init()
{
	
	MusicVolume = 0.3;
	CurrentWindows = 1;
	Pause = false;
	GameStarted = false;
}

bool WindowsControlData::GetEndState()
{
	return EndState;
}

void WindowsControlData::SetEndState(bool input)
{
	EndState = input;
}

void WindowsControlData::SetMap(std::string map)
{
	currentMap = map;
}

std::string WindowsControlData::GetMap()
{
	return currentMap;
}

void WindowsControlData::SetPath(std::string path)
{
	currentPath = path;
}

std::string WindowsControlData::Getpath()
{
	return currentPath;
}
