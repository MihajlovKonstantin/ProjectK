#pragma once
#include "Pch.h"

enum EnemyType
{
    TypeSlime = 1, TypeSnowBall
};

class NPC :
    public Player
{
protected:

    PC* m_player;
    bool m_discovery = false;
    int m_discoveryDistance = 200;
    int m_discoveryCoolTime = 30;
    std::vector<TerrainObject>* m_allTerrain;
    std::vector<TerrainObject*> m_terrain;
    std::vector<DirectX::BoundingBox> m_box;
    //DirectX::BoundingBox m_box[];

public:
    NPC(std::pair<float, float> pos, std::pair<float, float>speed, KdTexture* texture);
    NPC();
    //void Init(std::pair<float, float>pos, int Type, KdTexture* texture);
    static void Update();
    bool MovePossible();
    int GetDirection();
    std::pair<float,float> GetEnemyPos();
    float GetDistance();
    bool Discovery();
    void FindTerrainObject();
    void InitTO(std::vector<TerrainObject> &terrain);
    void InitPlayer(PC*player);
    void InitTrreainObject(std::vector<TerrainObject>* terrain);
};