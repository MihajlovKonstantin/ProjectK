#pragma once
#include "Pch.h"

enum SpawnType { PlayerType = 1, EnemyType, EnemysType};

class Spawner
{
	int m_index,m_type, m_interval, m_num;
	std::pair<float, float> m_charaPos;
	std::vector<NPC> m_enemy;
	std::vector<TerrainObject>*m_terrain;
	PC* m_player;
	bool m_spawnFlg = false;
	int cnt = 0;
	KdTexture* m_enemyTex;

public:
	
	Spawner(int charaIndex, std::pair<float, float>pos, PC* player = NULL, std::vector<TerrainObject >* terrain = NULL, int type = 1, int interval = 0, int num = 0);
	//Spawner(int charaIndex, std::pair<float, float>pos, int type = 1, KdTexture& tex, int interval = 0, int num = 0);
	//std::vector<int> GetIndex();
	int GetIndex();
	int GetType();
	int GetInterval();
	int GetNum();
	std::pair<float, float> GetCharaPos();
	void Update();
	void SetTexture(KdTexture texture);
	KdTexture* GetTexture();
};

