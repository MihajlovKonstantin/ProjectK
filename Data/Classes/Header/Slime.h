#pragma once
#include "Pch.h"
class Slime :
    public NPC
{
private:

    static const int m_SlimeJumpCoolTime = 60;
    int m_jumpCoolTime = m_SlimeJumpCoolTime;

public:

   void Update();

};
