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
		std::pair<float, float> pos;
		bool BackStage = false;
		bool OnIceFlag = false;
		bool OnSnowFlag = false;
		bool OnladerFlag = false;
		bool OnLavaFlag = false;
	};
	//stats
	float m_hp = 100.f, m_maxHP = 100.0f;
	float m_hpY = 22;
	float m_jumpPower = 0.0f;
	float m_jumpSpeed = 3.0f;
	float m_secondJumpSpeed = 2.0f;
	bool m_hpAlphaFlg = false;
	bool m_secondJumpFlg = false;
	bool m_notJumpFlg;
	std::pair<float, float> m_speed;//speed after mods
	std::pair<float, float> m_speedBase;//basic speed
	std::pair<float, float> m_currentSpeed = { 0,-1 };//speed with angle comp
	std::pair<float, float> m_pos;//screen pos
	std::pair<float, float> m_gPos;//world pos

	Direction m_direction;
	
	bool m_aliveFlg = true;
	//graphic
	int animation = 0;
	std::pair<int, int> _scroll = { 0,0 };
	std::pair<int, int>* m_scroll = &_scroll;
	KdTexture* m_texture;
	KdTexture* m_hpTexture;

	Math::Matrix m_mTrans;
	Math::Matrix m_mRotation;
	Math::Matrix m_mScale;
	Math::Matrix m_matrix;
	
	Math::Matrix m_hpTrans;
	Math::Matrix m_hpRotation;
	Math::Matrix m_hpScale;
	Math::Matrix m_hpMatrix;

	Math::Rectangle m_rectangle = Math::Rectangle(0, 33, 32, 32);
	Math::Rectangle m_hpRectangle = Math::Rectangle(0, 0, 32, 32);

	//collision
	bool m_moveBlock[4] = {false,false,false,false};
	bool m_moveBlockBuff[4] = { false,false,false,false };
	std::vector<CollisionBlockData> m_collisionData;

	bool OnSnowBlockFlag = false;
	bool OnIceBlockFlag = false;
	bool OnLadderBlockFlag = false;
	bool OnLavaBlockFlag = false;

	float m_collisionSize = 32.0f;
	float m_collisionRadius = m_collisionSize / 2;
	float m_rad = 0.0f;
	float m_sideRad = -1.0f;

	bool m_groundFlag;
	bool m_collision;
	//Destructor
	virtual ~Player();
	//Legacy
	bool IsPossibleAngle(float radian);
	int __test;
public:
	//Setter
	float GetAngle();
	void SetDirection(Direction direction);
	void SetHp(float hp);
	void SetScroll(std::pair<int, int>* scroll);
	//Getter
	bool GetOnGroundFlag();
	bool GetOnLadderFlag();
	Math::Rectangle GetRect();
	Math::Rectangle GetHpRect();
	Math::Matrix GetMatrix();
	Math::Matrix GetHpMatrix();
	KdTexture* GetTexture();
	KdTexture* GetHpTexture();
	std::pair<float, float> GetGPos();
	float GetHp();
	//Other
	void Update();
	void Jump();
	bool CollisionToBlock(Block block);
	bool CollisionToItem(Item* item);
	void Move(float x,float y);//�ړ��֐�
	void CollisionClear();
	void UpdateTransMat();
	int GetColissionDataSize();
	bool GetHpAlpha();
	void SetHpAlpha(bool hpAlpha);
};
