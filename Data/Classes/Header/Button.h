#pragma once
#include "Pch.h"
#include "Data/Classes/Header/WindowsControlData.h"
class Button
{
private:
	std::array<float, 2> size;
	std::array<float, 2> position;
	std::string text;
	float scale;
	int SwitchControlIndex;
	int DataControlIndex;
	int ButtonIndex;
	//int SecondSwithControlIndex;
	//int SecondDataControlIndex;
	bool visable = true;
	bool active = true;

public:
	Button(std::array<float, 2>inputSize, std::array<float, 2>inputPosition, std::string inputText, float inputScale,  int inputButtonIndex, int inputSwitchControlIndex, int inputDataControlIndex,int SecondSCI, std::vector<int>& SecondDCI);
	Button(std::array<float, 2>inputSize, std::array<float, 2>inputPosition, std::string inputText, float inputScale,  int inputButtonIndex, int inputSwitchControlIndex, int inputDataControlIndex);
	Button();
	~Button();
	std::string GetText();
	std::array<float,2> GetSize();
	std::array<float,2> GetPosition();
	float GetScale();
	std::array<int,2> SendClickData();
	void ChangeVisiable();
	bool GetVisable();
	void ChangeActive();
	bool GetActive();
	void SetVisable(bool input);
	void SetActive(bool input);
};

