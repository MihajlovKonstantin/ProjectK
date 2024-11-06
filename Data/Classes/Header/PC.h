#pragma once
#include "Player.h"
class PC :
    public Player
{
public:
    PC(std::pair<float,float>pos,std::pair<float,float>speed, KdTexture* texture);
    PC();
    std::pair<float, float> GetPos();
    void Update()override;
    KdTexture* GetTexture();
    Math::Matrix GetMatrix();
    void Stop();
};

