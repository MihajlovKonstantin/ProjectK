#pragma once
#include "Pch.h"



class Spawner
{

	int m_index,m_type, m_interval, m_num;
	std::pair<float, float> m_charaPos;
	std::vector<NPC> m_enemy;
	std::vector<TerrainObject>*m_terrain;
	std::vector<Slime> m_slimes;
	std::vector<SnowBall> m_snowBall;
	PC* m_player;
	bool m_spawnFlg = false;
	int cnt = 0;
	KdTexture* m_enemyTex;
	std::array<std::vector<KdTexture*>, 2>* m_enemylibrary;
	std::pair<int, int> _scroll = { 0,0 };
	std::pair<int, int>* m_scroll = &_scroll;
public:
	enum SpawnType { PlayerType = 1, EnemyType, EnemysType };
	Spawner(int charaIndex, std::pair<float, float>pos, std::array<std::vector<KdTexture*>, 2>* texLib, PC* player = NULL, std::vector<TerrainObject >* terrain = NULL, int type = 1, int interval = 0, int num = 0);
	int GetIndex();
	int GetType();
	int GetInterval();
	int GetNum();
	std::pair<float, float> GetCharaPos();
	void Update();
	void SetTexture(KdTexture texture);
	KdTexture* GetTexture();
	std::vector<Slime>* GetSlime();
	std::vector<SnowBall>* GetSnowBall();
	void SetScroll(std::pair<int, int>* scroll);
};

