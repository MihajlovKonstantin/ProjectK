#include "Pch.h"

NPC::NPC(int index, std::pair<float, float> pos, int enemyType, int interval, int num)
{
	m_enemyIndex = index;
	m_pos = pos;
	m_enemyType = enemyType;
	m_enemyInterval = interval;
	m_enemyNum = num;
}

NPC::NPC(std::pair<float, float> pos, std::pair<float, float>speed, KdTexture* texture)
{
	m_pos = pos;
	m_speed = speed;
	m_texture = texture;
}

NPC::NPC()
{
}

void NPC::Update()
{


	/*switch (m_direction)
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
	Player::Update();*/
}

void NPC::Stop()
{
	m_onGroundFlag = false;
}

void NPC::SetOnGroundFlag(bool flag)
{
	m_onGroundFlag = flag;
}

bool NPC::MovePossible()
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

int NPC::GetDirection()
{
	return m_direction;
}
