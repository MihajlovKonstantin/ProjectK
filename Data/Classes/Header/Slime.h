#pragma once
#include "Pch.h"
class Slime :
    public NPC
{
private:
    int _coolTime = 10;
    int _coolTimeMax = 10;
    static const int m_slimeJumpCoolTime = 60;
    int m_jumpCoolTime = m_slimeJumpCoolTime;

public:
    Slime() {};
    Slime(KdTexture* texture,std::pair<float, float> pos, std::pair<float, float>speed ={1.5,-2});
    ~Slime();

   void Update();

};

