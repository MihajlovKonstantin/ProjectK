#pragma once
#include "Pch.h"

class Spawner
{
	//std::vector<int>m_Index;
	int m_index,m_Type, m_Interval, m_Num;
	std::pair<float, float> m_CharaPos;
	std::vector<NPC> m_enemy;
	//std::vector<Spawner> m_spawner;
	PC* m_Player;
	bool m_spawnFlg = false;
	int cnt = 0;
	KdTexture* m_enemyTex;

public:
	
	Spawner(int charaIndex, std::pair<float, float>pos, PC* player = NULL, int type = 1, int interval = 0, int num = 0);
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

