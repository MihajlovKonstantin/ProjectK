#pragma once
#include "Pch.h"
class Slime :
    public NPC
{
private:

    static const int m_slimeJumpCoolTime = 60;
    int m_jumpCoolTime = m_slimeJumpCoolTime;

public:
    Slime() {};
    Slime(KdTexture* texture,std::pair<float, float> pos, std::pair<float, float>speed ={1.5,-2});
    ~Slime();

   void Update();

};

