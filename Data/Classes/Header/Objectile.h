#pragma once
#include "Pch.h"
class Objectile
{
	string m_texture;
	std::array<int,4> m_rect;
	std::array<float, 4> m_baseColor;
	float m_colorMul;
	std::array<float, 4> m_color;
public:
	~Objectile();
	Objectile(std::string texture, std::array<int, 4> rect, std::array<float, 4> color);
	std::string GetTexture();
	std::array<int, 4> GetRectangle();
	std::array<float, 4> GetColor();
	//test

};

