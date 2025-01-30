#pragma once
#include "Pch.h"

class WindowsControlData
{
	
	bool EndState = false;
	int CurrentWindows = 0;
	int PreviousWindows = 0;
	float MusicVolume= 1.0f; //21
	bool GameStarted; //22
	bool Pause; //23
	std::string currentMap;
	std::string currentPath;

	bool CampainMap = false;
	int CampainMapIndex = 0;
public:
	void SetPreviousWindows(int data);
	bool IsCampain();
	void SetCampainMod(bool data);
	int GetCampainMapIndex();
	void SetCampainMapIndex(int data);
	bool IsPause();
	bool IsStarted();
	void Resume();
	void PauseGame();
	void Restart();
	void StartGame();
	float GetMusicVolume();
	void SetMusicVolume(float input);
	int GetWindow();
	void SetWindow(int input);
	void Init();
	bool GetEndState();
	void SetEndState(bool input);
	void SetMap(std::string map);
	std::string GetMap();
	void SetPath(std::string path);
	std::string Getpath();
};

