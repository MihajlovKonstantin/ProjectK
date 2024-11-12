#pragma once
#include "Data/Classes/Header/Button.h"
#include "Pch.h"
#include "Src/Application/Direction.h"
class Player
{
protected:
	std::pair<float, float> m_pos;
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
	bool CollisionToBlock(Block block);
	void Move();//�ړ��֐�
	Math::Matrix GetMatrix();
	KdTexture* GetTexture();
};
