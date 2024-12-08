#pragma once
#include "Player.h"
class NPC :
    public Player
{
protected:
    bool m_onGroundFlag;
    int m_enemyIndex;
    int m_enemyType;
    int m_enemyInterval;
    int m_enemyNum;
public:
    NPC(int index, std::pair<float, float>pos, int enemyType, int interval = 0, int num = 0);
    NPC(std::pair<float, float> pos, std::pair<float, float>speed, KdTexture* texture);
    NPC();
    void Init(std::pair<float, float>pos, int Type, KdTexture* texture);
    void Update();
    void Stop();
    void SetOnGroundFlag(bool flag);
    bool MovePossible();
    int GetDirection();
};