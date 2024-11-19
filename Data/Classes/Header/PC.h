#pragma once
#include "Player.h"
class PC :
    public Player
{
protected :
    bool m_onGroundFlag;
public:
    PC(std::pair<float, float>pos, std::pair<float, float>speed, KdTexture* texture);
    PC();
    std::pair<float, float> GetPos();
    void Update();
    void Stop();
    void SetOnGroundFlag(bool flag);
};

