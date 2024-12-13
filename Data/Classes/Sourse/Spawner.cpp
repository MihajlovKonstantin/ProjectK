#include "Pch.h"
#include "Data/Classes/Header/Spawner.h"

Spawner::Spawner(int charaIndex, std::pair<float, float> pos, PC* player, int type, int interval, int num)
{
	m_Player = player;
	m_index = charaIndex;
	m_CharaPos = pos;
	m_Type = type;
	m_Interval = interval;
	m_Num = num;
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
	return m_Type;
}

int Spawner::GetInterval()
{
	return m_Interval;
}

int Spawner::GetNum()
{
	return m_Num;
}

std::pair<float, float> Spawner::GetCharaPos()
{
	return m_CharaPos;
}

void Spawner::Update()
{

	switch (m_index)
	{
	case 1:
		if (!m_spawnFlg)m_Player->Init(m_CharaPos);
		m_spawnFlg = true;
		break;
	case 2:
		if (!m_spawnFlg)m_enemy.push_back(NPC(m_CharaPos, { 0,0 }, m_enemyTex));
		m_spawnFlg = true;
		break;
	case 3:
		if (m_enemy.size() < m_Num)
		{
			cnt++;
			if (cnt < m_Interval) {}
			else
			{
				m_enemy.push_back(NPC(m_CharaPos, { 0,0 }, m_enemyTex));
				cnt = 0;
			}
		}
		break;
	}


	for (int j = 0; j < m_enemy.size(); j++)
	{
		m_enemy[j].Update();
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
