#pragma once
#include "Data/Classes/Header/Button.h"
#include "Pch.h"
#include "Src/Application/Direction.h"
class Player
{
	//à¯êî
protected:
	std::pair<float,float> m_pos;
	float m_collisionSize = 32.0f;
	float m_collisionRadius = m_collisionSize / 2;
	KdTexture* m_texture;
	Math::Matrix m_mTrans;
	float m_tangen;
	std::pair<float, float> m_speed;
	virtual ~Player();
	bool m_groundFlag;
	Direction m_direction;
	std::pair<float, float> RotatePoint(float x, float y, float cx, float cy, float angle);
	bool IsCircleIntersectingRotatedRectangle(float cx, float cy, float width, float height, float angle, float h, float k, float r);
public:
	virtual void Update() = 0;
	bool IsGround(Block block);
	//ä÷êî
};

