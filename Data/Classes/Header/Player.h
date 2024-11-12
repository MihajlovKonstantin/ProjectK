#pragma once
#include "Data/Classes/Header/Button.h"
#include "Pch.h"
#include "Src/Application/Direction.h"
class Player
{
	//ˆø”
protected:
	std::pair<float,float> m_pos;
	float m_collisionSize = 32.0f;
	float m_collisionRadius = m_collisionSize / 2;
	KdTexture* m_texture;
	Math::Matrix m_mTrans;
	Math::Matrix m_mRotation;
	Math::Matrix m_mScale;
	Math::Matrix m_matrix;
	float m_rad;
	std::pair<float, float> m_speed;
	virtual ~Player();
	bool m_groundFlag;
	Direction m_direction;
public:
	void Update();
	bool IsGround(Block block);
	void Move();//ˆÚ“®ŠÖ”
	Math::Matrix GetMatrix();
	KdTexture* GetTexture();
	//ŠÖ”
};

