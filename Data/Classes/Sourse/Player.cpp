#include "Pch.h"
#include <utility>
#include "Data/Classes/Header/Player.h"
std::pair<float, float> Player::RotatePoint(float x, float y, float cx, float cy, float angle)
{
	float s = sin(angle);
	float c = cos(angle); 
	
	x -= cx;
	y -= cy;

	float xnew = x * c - y * s;
	float ynew = x * s + y * c;
	
	x = xnew + cx; y = ynew + cy;
	return {x, y};
}
bool Player::IsCircleIntersectingRotatedRectangle(float cx, float cy, float width, float height, float angle, float h, float k, float r)
{
	std::pair<float, float> vertices[4] = 
	{ {cx - width / 2, cy - height / 2},
		{cx + width / 2, cy - height / 2},
		{cx + width / 2, cy + height / 2},
		{cx - width / 2, cy + height / 2}
	};

	for (int i = 0; i < 4; ++i) 
	{
		vertices[i] = RotatePoint(vertices[i].first, vertices[i].second, cx, cy, angle);
	}
	for (int i = 0; i < 4; i++)
	{
		if (std::sqrt((vertices[i].first - h) * (vertices[i].first - h) + (vertices[i].second) * (vertices[i].second)) <= r)
		{
			return true;
		}
	}
	return false;
}
Player::~Player()
{
}

bool Player::IsGround(Block block)
{
	bool _result = false;
	std::pair<float, float> _bPos = block.GetGPos();
	std::pair<float, float> _bSize = block.GetSize();
	std::pair<float, float> _position = m_pos;
	float _bAngle = block.GetAngle();
	_result = IsCircleIntersectingRotatedRectangle(_bPos.first, _bPos.second, _bSize.first, _bSize.second, _bAngle, _position.first, _position.second, sqrt(pow(16,2)*2));

	return _result;
}
