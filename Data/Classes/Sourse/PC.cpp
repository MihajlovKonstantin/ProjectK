#include "Pch.h"
#include "Data/Classes/Header/PC.h"

PC::PC(std::pair<float, float> pos, std::pair<float, float>speed, KdTexture* texture)
{
	m_pos = pos;
	m_texture = texture;
	m_speedBase = speed;
	m_speed = m_speedBase;
}

std::pair<float, float> PC::GetPos()
{
	return m_pos;
}

void PC::Init(std::pair<float, float>pos)
{
	m_pos = pos;
	m_rad = 0;
	m_sideRad = -1.0f;
	m_currentCollisionValue = -1.0f;
	m_groundFlag = false;
	Update();
	m_mRotation = Math::Matrix::CreateRotationZ(0);
	m_matrix = m_mTrans * m_mRotation;
}


void PC::Update()
{

	switch (m_direction)
	{
	case Direction::Up:
		break;
	case Direction::Down:
		break;
	case Direction::Left:
		break;
	case Direction::Right:
		break;
	}
	if (!m_onGroundFlag)
	{
		m_sideRad = -1;
		m_rad = 0;
		m_currentCollisionValue = -1.0f;
	}
	m_groundFlag = m_onGroundFlag;
	Player::Update();
}


void PC::Stop()
{
	m_onGroundFlag = false;
}

void PC::SetOnGroundFlag(bool flag)
{
	m_onGroundFlag = flag;
}

bool PC::MovePossible()
{
	for (int i = 0; i < m_collisionData.size(); i++)
	{
		if (!IsPossibleAngle(m_collisionData[i].rad))
		{
			return false;
		}
	}
	return false;
}

int PC::GetDirection()
{
	return m_direction;
}

std::pair<float, float> PC::GetPlayerPos()
{
	return m_pos;
}

void PC::SetPlayerPos(std::pair<float, float> pos)
{
	m_pos = pos;
}
