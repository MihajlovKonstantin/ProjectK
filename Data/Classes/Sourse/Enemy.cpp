#include "Pch.h"
#include "Data/Classes/Header/Enemy.h"
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

void NPC::AIUpdate()	//プレイヤーを追尾する
{
	
	if (m_groundFlag)
		m_onGroundFlag = true;

	if (Discovery() && ((m_emyMoveFlg)|| ((m_groundFlag)&&(OnLadderBlockFlag)) ))
	{
		//プレイヤーが敵の左側に居たら左に移動する
		if (m_player->GetGPos().first < m_gPos.first)Player::SetDirection(Left);
		//右ver
		else Player::SetDirection(Right);
		if ((m_player->GetGPos().second > m_gPos.second)&&OnLadderBlockFlag&&(abs(m_player->GetGPos().second - m_gPos.second)> abs(m_player->GetGPos().first - m_gPos.first)))
		{
			Player::SetDirection(Up);
		}
		else
		{
			if (OnLadderBlockFlag && (abs(m_player->GetGPos().second - m_gPos.second) > abs(m_player->GetGPos().first - m_gPos.first)))
			{
				Player::SetDirection(Down);
			}
			
		}
	}
	else Player::SetDirection(Stand);
	
	if (!m_onGroundFlag)
	{
		m_sideRad = -1;
		m_rad = -1;
	}
	m_groundFlag = m_onGroundFlag;
	Hit();
	Player::Update();
}

void NPC::BotUpdate()	//同じ動きを繰り返す
{
	if (m_groundFlag)
		m_onGroundFlag = true;

	if (!m_snowBallFlg)
	{
		//壁に当たると向きを変える
		if (!m_directionFlg)Player::SetDirection(Left);
		else Player::SetDirection(Right);
	}


	if (!m_groundFlag)
	{
		m_sideRad = -1;
		m_rad = 0;
	}
	Hit();
	Player::Update();
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
	auto _playerPos = m_player->GetGPos();
	auto _curenntDistance = GetDistance();
	//auto _curenntDistance = 1;
	
	if (m_discoveryCoolTime-- < 0)	//30フレーム毎に発見判定を行う
	{
		m_discoveryCoolTime = 30;
		if (_curenntDistance <= m_discoveryDistance)	//発見可能距離かどうか
		{
			m_result = true;
			m_box.clear();
			FindTerrainObject();
			Normalize = DirectX::XMVector3Normalize({ m_player->GetGPos().first - m_gPos.first ,
													  m_player->GetGPos().second - m_gPos.second,0 });
			float foo;
			auto _enemyPos = DirectX::XMVECTOR{ m_gPos.first, float(m_gPos.second),0 };
			for (size_t i = 0; i < m_terrain.size(); i++)
			{
				int deltaX, deltaY;
				auto v = m_terrain[i]->GetTypeBlockSize();
				switch (m_terrain[i]->GetAngle())	//ブロックには角度があるため
				{
				case 0:
					deltaX = 16 * v * 1;
					deltaY = 16 * v * 0;
					break;
				case 1:
					deltaX = 16 * v * 1;
					deltaY = 16 * v * 1;
					break;
				case 2:
					deltaX = 16 * v * 0;
					deltaY = 16 * v * 1;
					break;
				case 3:
					deltaX = 16 * v * -1;
					deltaY = 16 * v * 1;
					break;
				case 4:
					deltaX = 16 * v * -1;
					deltaY = 16 * v * 0;
					break;
				case 5:
					deltaX = 16 * v * -1;
					deltaY = 16 * v * -1;
					break;
				case 6:
					deltaX = 16 * v * 0;
					deltaY = 16 * v * -1;
					break;
				case 7:
					deltaX = 16 * v * 1;
					deltaY = 16 * v * -1;
					break;
				case 8:
					deltaX = 16 * v * 1;
					deltaY = 16 * v * 0;
					break;
				}
				DirectX::BoundingBox _boundBox(DirectX::XMFLOAT3(m_terrain[i]->GetGPOS().first + deltaX,
					m_terrain[i]->GetGPOS().second + deltaY, 0),
					DirectX::XMFLOAT3(16 * v, 16 * v, 0));
				m_box.push_back(_boundBox);

				//必要なBoundingBoxを抽出する
				if (!m_box[i].Intersects(_enemyPos, Normalize, foo))
				{
					m_terrainBool[i] = false;
				}
				else
				{
					m_terrainBool[i] = true;
				}
			}
			DirectX::BoundingSphere _newSphere;
			std::pair<float, float> _blockPos;
			for (int i = 0; m_terrainBool.size() > i; i++)
			{
				if (m_terrainBool[i])
				{
					m_blockBuff = m_terrain[i]->GetBlocks();
					m_sphere.clear();
					for (size_t j = 0; m_blockBuff->size() > j; j++)
					{
						_blockPos = m_blockBuff->at(j).GetGPos();
						if (!m_blockBuff->at(0).GetBackStage())
						{
							_newSphere = DirectX::BoundingSphere({ _blockPos.first,_blockPos.second,0 }, 16.0f);
							m_sphere.push_back(_newSphere);
						}
						
					}
					for (size_t k = 0; m_sphere.size() > k; k++)
					{
						//xray上にブロックがあるかどうか
						if (m_sphere.at(k).Intersects(_enemyPos, Normalize, foo))
						{
							if (_curenntDistance > foo)
							{
								m_result = false;
							}
							
						}
					}
				}
			}
		}
		else m_result = false;
		m_discovery = m_result;
	}

	return m_result;
}

void NPC::FindTerrainObject()
{
	m_terrain.clear();
	for (size_t i = 0; i < m_allTerrain->size(); i++)
	{
		auto _xBorder = m_allTerrain->at(i).GetBorderX();
		auto _yBorder = m_allTerrain->at(i).GetBorderY();
		//auto _test = &terreain->at(i);
		if ((m_gPos.first >= _xBorder.first) && (m_gPos.first <= _xBorder.second))
		{
			if ((m_gPos.second >= _yBorder.first) && (m_gPos.second <= _yBorder.second))
			{
				m_terrain.push_back(&m_allTerrain->at(i));
			}
		}
	}
	m_terrainBool.resize(m_terrain.size());
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

void NPC::SetOnGroundFlag(bool flag)
{
	m_onGroundFlag = flag;
}

void NPC::Hit()
{
	//敵とキャラの当たり判定(円判定)
	float _hight = m_gPos.second - m_player->GetGPos().second;
	float _width = m_gPos.first - m_player->GetGPos().first;

	float _distance = sqrt(_hight * _hight + _width * _width);

	//無敵時間
	if (m_hitCooltime-- < 0)m_hitCooltime = 0;

	if (_distance < 16 && m_hitCooltime == 0)
	{
		m_player->SetHp(m_player->GetHp() - 10);
		m_hitCooltime = m_hitHpCoolTime;
	}
	
}
