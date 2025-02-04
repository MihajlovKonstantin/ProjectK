#pragma once
#include"Pch.h"
class InformPanel
{
	std::pair<float, float> m_gPos;
	int m_index;
	std::string text;
public:
	InformPanel();
	InformPanel(std::pair<float, float> pos, int index);
	std::string GetText();
	std::pair<float, float> GetGPos();
	int GetIndex();
};

