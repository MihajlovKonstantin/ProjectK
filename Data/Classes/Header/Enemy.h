#pragma once
#include "Pch.h"
enum EnemyType
{
    TypeSlime = 0, TypeSnowBall
};

class NPC :
    public Player
{
protected:

    PC* m_player;
    bool m_discovery = false;
    bool m_result = false;
    bool m_onGroundFlag;
    bool m_directionFlg = false;
    bool m_emyMoveFlg = false;
    bool m_snowBallFlg = false;
    int m_discoveryDistance = 200;
    int m_discoveryCoolTime = 30;
    static const int m_hitHpCoolTime = 20;
    int m_hitCooltime = m_hitHpCoolTime;
    std::vector<TerrainObject>* m_allTerrain;
    std::vector<TerrainObject*> m_terrain;
    std::vector<DirectX::BoundingBox> m_box;
    std::vector<DirectX::BoundingSphere> m_sphere;
    DirectX::XMVECTOR Normalize;
    std::vector<bool> m_terrainBool;
    std::vector<Block>* m_blockBuff;
    //m_terrain.GetBlockTypeSize();
    //DirectX::BoundingBox m_box[];

public:
    
    NPC(std::pair<float, float> pos, std::pair<float, float>speed, KdTexture* texture);
    NPC();
    //void Init(std::pair<float, float>pos, int Type, KdTexture* texture);
    void AIUpdate();
    void BotUpdate();
    bool MovePossible();
    int GetDirection();
    std::pair<float,float> GetEnemyPos();
    float GetDistance();
    bool Discovery();
    void FindTerrainObject();
    void InitTO(std::vector<TerrainObject> &terrain);
    void InitPlayer(PC*player);
    void InitTrreainObject(std::vector<TerrainObject>* terrain);
    void SetOnGroundFlag(bool flag);
    void Hit();
};