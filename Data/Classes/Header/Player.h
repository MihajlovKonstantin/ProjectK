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
		std::pair<float, float>dPos;
	};
	int animation = 0;
	float m_jumpPower = 0.0f;
	float m_jumpSpeed = 3.0f;
	float m_secondJumpSpeed = 2.0f;
	bool m_moveBlock[4] = {false,false,false,false};
	bool m_stopFlag;
	std::vector<CollisionBlockData> m_collisionData;

	std::pair<float, float> m_pos;
	std::pair<float, float> m_gPos;

	std::pair<int, int> _scroll = { 0,0 };
	std::pair<int, int>* m_scroll = &_scroll;

	float m_collisionSize = 32.0f;
	float m_collisionRadius = m_collisionSize / 2;
	KdTexture* m_texture;
	//std::pair<float, float>m_scale = { 1,1 };
	Math::Matrix m_mTrans;
	Math::Matrix m_mRotation;
	Math::Matrix m_mScale;
	Math::Matrix m_matrix;
	Math::Rectangle m_rectangle = Math::Rectangle(0,33,32,32);
	float m_rad;
	float m_sideRad=-1.0f;
	float m_currentCollisionValue = -1.0f;
	std::pair<float, float> m_speed;
	std::pair<float, float> m_speedBase;
	virtual ~Player();
	bool m_groundFlag;
	bool m_collision;
	Direction m_direction;
	std::pair<float, float> m_currentSpeed;
	bool IsPossibleAngle(float radian);
	bool m_secondJumpFlg = false;
	bool m_notJumpFlg;
public:
	Math::Rectangle GetRect();
	void Update();
	void Jump();
	bool CollisionToBlock(Block block);
	bool CollisionToBlock(std::pair<float, float> b_pos, std::pair<float, float> b_size, float b_rad);
	bool CollisionToItem(Item* item);
	void Move(float x,float y);//�ړ��֐�
	Math::Matrix GetMatrix();
	KdTexture* GetTexture();
	float GetAngle();
	void SetDirection(Direction direction);
	void CollisionClear();
	bool GetOnGroundFlag();
	void SetScroll(std::pair<int, int>* scroll);
	std::pair<float, float> GetGPos();
};
