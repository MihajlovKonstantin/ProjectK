#include "Data/Classes/Header/Spawner.h"

Spawner::Spawner(int charaIndex, std::pair<float, float> pos, std::array<std::vector<KdTexture*>, 2>* texLib, PC* player, std::vector<TerrainObject >* terrain, int type, int interval, int num)
{
	m_player = player;
	m_index = charaIndex;
	m_charaPos = pos;
	m_terrain = terrain;
	m_type = type;
	m_interval = interval;
	m_num = num;
	m_enemylibrary = texLib;
	m_enemyTex = NULL;

	switch (m_type)
	{
	case EnemyType::TypeSlime:
		m_enemyTex = m_enemylibrary->at(EnemyType::TypeSlime).at(0);
		break;
	case EnemyType::TypeSnowBall:
		m_enemyTex = m_enemylibrary->at(EnemyType::TypeSnowBall).at(0);
		break;
	}
}

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
			//m_enemy.push_back(NPC(m_charaPos, { 0,0 }, m_enemyTex));
			switch (m_type)
			{
			case EnemyType::TypeSlime:
				m_slimes.push_back(Slime(m_enemyTex, m_charaPos));
				m_slimes[m_slimes.size() - 1].SetScroll(m_scroll);
				m_slimes[m_slimes.size() - 1].InitPlayer(m_player);
				m_slimes[m_slimes.size() - 1].InitTrreainObject(m_terrain);
				break;
			case EnemyType::TypeSnowBall:
				m_snowBall.push_back(SnowBall(m_enemyTex, m_charaPos));
				m_snowBall[m_snowBall.size() - 1].SetScroll(m_scroll);
				m_snowBall[m_snowBall.size() - 1].InitPlayer(m_player);
				m_snowBall[m_snowBall.size() - 1].InitTrreainObject(m_terrain);
				break;
			}
			
			//m_enemy[m_enemy.size() - 1].InitPlayer(m_player);
			//m_enemy[m_enemy.size() - 1].InitTrreainObject(m_terrain);
		}
		m_spawnFlg = true;
		break;
	case EnemysType:	//敵(複数)
		if (m_slimes.size()+m_snowBall.size() < m_num)
		{
			cnt++;
			if (cnt < m_interval) {}
			else
			{
				//m_enemy.push_back(NPC(m_charaPos, { 0,0 }, m_enemyTex));
				switch (m_type)
				{
				case EnemyType::TypeSlime:
					m_slimes.push_back(Slime(m_enemyTex, m_charaPos));
					m_slimes[m_slimes.size() - 1].SetScroll(m_scroll);
					m_slimes[m_slimes.size() - 1].InitPlayer(m_player);
					m_slimes[m_slimes.size() - 1].InitTrreainObject(m_terrain);
					m_slimes[m_slimes.size() - 1].UpdateTransMat();
					break;
				case EnemyType::TypeSnowBall:
					m_snowBall.push_back(SnowBall(m_enemyTex, m_charaPos));
					m_snowBall[m_snowBall.size() - 1].SetScroll(m_scroll);
					m_snowBall[m_snowBall.size() - 1].InitPlayer(m_player);
					m_snowBall[m_snowBall.size() - 1].InitTrreainObject(m_terrain);
					break;
				}
				//m_enemy[m_enemy.size() - 1].InitPlayer(m_player);
				//m_enemy[m_enemy.size() - 1].InitTrreainObject(m_terrain);
				cnt = 0;
			}
		}
		break;
	}


	for (int j = 0; j < m_slimes.size(); )
	{
		m_slimes[j].Update();
		if (m_slimes[j].GetHp() == 0)
		{
			m_slimes.erase(m_slimes.begin() + j);
		}
		else
		{
			j++;
		}
		//m_slimes[j].Discovery();
	}
	for (int k = 0; k < m_snowBall.size();)
	{
		m_snowBall[k].Update();
		if (m_snowBall[k].GetHp() == 0)
		{
			m_snowBall.erase(m_snowBall.begin() + k);
		}
		else
		{
			k++;
		}
		//m_snowBall[k].Discovery();
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

std::vector<Slime>* Spawner::GetSlime()
{
	return &m_slimes;
}

std::vector<SnowBall>* Spawner::GetSnowBall()
{
	return &m_snowBall;
}

void Spawner::SetScroll(std::pair<int, int>* scroll)
{
	m_scroll = scroll;
}
