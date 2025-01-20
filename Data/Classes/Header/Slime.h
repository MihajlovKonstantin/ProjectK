#pragma once
#include "Pch.h"
class Slime :
    public NPC
{
private:
    static const int m_slimeJumpCoolTime = 60;
    int m_jumpCoolTime = m_slimeJumpCoolTime;

public:

    Slime();
    ~Slime() {};

   void Update();

};

