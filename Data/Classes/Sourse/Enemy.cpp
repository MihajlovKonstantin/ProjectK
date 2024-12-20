#include "Pch.h"

NPC::NPC(std::pair<float, float> pos, std::pair<float, float>speed, KdTexture* texture)
{
	m_pos = pos;
	m_speedBase = speed;
	m_speed = m_speedBase;
	m_texture = texture;
}

NPC::NPC()
{
}

void NPC::Update()
{
	//Discovery();
//	if (GetDistance() <= 10)
//	{
//		switch (GetDirection())
//		{
//		case Direction::Up:
//			break;
//		case Direction::Down:
//			break;
//		case Direction::Left:
//			break;
//		case Direction::Right:
//			break;
//		}
//		if (!m_onGroundFlag)
//		{
//			m_sideRad = -1;
//			m_rad = 0;
//			m_currentCollisionValue = -1.0f;
//		}
//		m_groundFlag = m_onGroundFlag;
//	}
//	switch (GetType())
//	{
//	case EnemyType::TypeSlime:
//		Slime::Update();
//		break;
//	case EnemyType::TypeSnowBall:
//
//		break;
//	}
//
//	Player::Update();
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

std::pair<float, float> NPC::GetEnemyPos()
{
	return m_pos;
}

float NPC::GetDistance()
{
	float distanceY = m_player->GetPos().second - m_pos.second;
	float distanceX = m_player->GetPos().first - m_pos.first;
	float distance = sqrt(distanceY * distanceY + distanceX * distanceX);
	return distance;
}

bool NPC::Discovery()
{
	bool _result = false;

	auto _playerPos = m_player->GetPos();
	//auto _curenntDistance = GetDistance();
	auto _curenntDistance = 1;
	
	if (_curenntDistance <= m_discoveryDistance)
	{
		if (m_discoveryCoolTime-- < 0)
		{
			m_discoveryCoolTime = 30;
			m_box.clear();
			FindTerrainObject();
			for (int i = 0; i < m_terrain.size(); i++)
			{
				DirectX::BoundingBox _boundBox(DirectX::XMFLOAT3(m_terrain[i]->GetGPOS().first, m_terrain[i]->GetGPOS().second, 0),
											   DirectX::XMFLOAT3(16, 16, 0));
				m_box.push_back(_boundBox);
			}
			/*DirectX::XMVectorSet(m_pos.first, m_pos.second + 16,
								 m_player->GetPos().first, m_player->GetPos().second);*/
		}
	}

	return _result;
}

void NPC::FindTerrainObject()
{
	for (size_t i = 0; i < m_allTerrain->size(); i++)
	{
		auto _xBorder = m_allTerrain->at(i).GetBorderX();
		auto _yBorder = m_allTerrain->at(i).GetBorderY();
		//auto _test = &terreain->at(i);
		if ((m_pos.first >= _xBorder.first) && (m_pos.first <= _xBorder.second))
		{
			if ((m_pos.second >= _xBorder.second) && (m_pos.second <= _xBorder.second))
			{
				m_terrain.push_back(&m_allTerrain->at(i));
			}
		}
	}
}

void NPC::InitTO(std::vector<TerrainObject> &terrain)
{
	m_allTerrain = &terrain;
}

void NPC::InitPlayer(PC* player)
{
	m_player = player;
}

void NPC::InitTrreainObject(std::vector<TerrainObject>* terrain)
{
	m_allTerrain = terrain;
}
