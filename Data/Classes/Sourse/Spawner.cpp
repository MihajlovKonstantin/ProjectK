#include "Pch.h"
#include "Data/Classes/Header/Spawner.h"

Spawner::Spawner(int charaIndex, std::pair<float, float> pos, PC* player, std::vector<TerrainObject >* terrain, int type, int interval, int num)
{
	m_player = player;
	m_index = charaIndex;
	m_charaPos = pos;
	m_terrain = terrain;
	m_type = type;
	m_interval = interval;
	m_num = num;
}

//Spawner::Spawner(int charaIndex, std::pair<float, float> pos, int type, KdTexture& tex, int interval, int num)
//{
//
//}

int Spawner::GetIndex()
{
	return m_index;
}

int Spawner::GetType()
{
	return m_type;
}

int Spawner::GetInterval()
{
	return m_interval;
}

int Spawner::GetNum()
{
	return m_num;
}

std::pair<float, float> Spawner::GetCharaPos()
{
	return m_charaPos;
}

void Spawner::Update()
{

	switch (m_index)
	{
	case PlayerType:	//プレイヤー用
		if (!m_spawnFlg)
		{
			m_player->Init(m_charaPos);
		}
		m_spawnFlg = true;
		break;
	case EnemyType:		//敵(単体)
		if (!m_spawnFlg)
		{
			m_enemy.push_back(NPC(m_charaPos, { 0,0 }, m_enemyTex));
			m_enemy[m_enemy.size() - 1].InitPlayer(m_player);
			m_enemy[m_enemy.size() - 1].InitTrreainObject(m_terrain);
		}
		m_spawnFlg = true;
		break;
	case EnemysType:	//敵(複数)
		if (m_enemy.size() < m_num)
		{
			cnt++;
			if (cnt < m_interval) {}
			else
			{
				m_enemy.push_back(NPC(m_charaPos, { 0,0 }, m_enemyTex));
				m_enemy[m_enemy.size() - 1].InitPlayer(m_player);
				m_enemy[m_enemy.size() - 1].InitTrreainObject(m_terrain);
				cnt = 0;
			}
		}
		break;
	}


	for (int j = 0; j < m_enemy.size(); j++)
	{
		m_enemy[j].Update();
		m_enemy[j].Discovery();
	}
}
	

void Spawner::SetTexture(KdTexture texture)
{
	m_enemyTex = &texture;
}

KdTexture* Spawner::GetTexture()
{
	return m_enemyTex;
}
