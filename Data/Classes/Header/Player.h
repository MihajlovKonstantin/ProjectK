#pragma once
#include "Data/Classes/Header/Button.h"
#include "Pch.h"
#include "Src/Application/Direction.h"
class Player
{
protected:
	struct CollisionBlockData
	{
		float rad;
		float sideRad;
		float collisionValue;
		std::pair<float, float> pos;
	};
	std::vector<CollisionBlockData> m_collisionData;
	std::pair<float, float> m_pos;
	float m_collisionSize = 32.0f;
	float m_collisionRadius = m_collisionSize / 2;
	KdTexture* m_texture;
	std::pair<float, float>m_scale = { 1,1 };
	Math::Matrix m_mTrans;
	Math::Matrix m_mRotation;
	Math::Matrix m_mScale;
	Math::Matrix m_matrix;
	float m_rad;
	float m_sideRad=-1.0f;
	float m_currentCollisionValue = -1.0f;
	std::pair<float, float> m_speed;
	std::pair<float, float> m_speedBase;
	virtual ~Player();
	bool m_groundFlag;
	Direction m_direction;
	std::pair<float, float> m_currentSpeed;
public:

	void Update();
	bool CollisionToBlock(Block block);
	bool CollisionToBlock(std::pair<float, float> b_pos, std::pair<float, float> b_size, float b_rad);
	void Move();//�ړ��֐�
	Math::Matrix GetMatrix();
	KdTexture* GetTexture();
	float GetAngle();
	void SetDirection(Direction direction);
	void CollisionClear();
};
