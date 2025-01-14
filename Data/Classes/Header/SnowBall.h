#pragma once
#include "Pch.h"
class SnowBall :
    public NPC
{
private:

    SnowBall() {};
    ~SnowBall() {};

    int m_leftCoolTime = 20;
    int m_rightCoolTime = 20;
    static const int m_regenerationTime = 60 * 3;
    int m_regenerationCoolTime = m_regenerationTime;
    bool m_onlyFlg = false;

public:

    void Update();

};

