#pragma once
#include "Pch.h"
class SnowBall :
    public NPC
{
private:

    static const int m_directionCoolTime = 10;
    int m_leftCoolTime = 0;
    int m_rightCoolTime = 0;
    static const int m_regenerationTime = 60 * 3;
    int m_regenerationCoolTime = m_regenerationTime;
    bool m_onlyFlg = false;
    bool m_rightFlg = false;
    bool m_leftFlg = true;

public:

    SnowBall(KdTexture* texture, std::pair<float, float> pos, std::pair<float, float>speed = {1.5,-2 });
    ~SnowBall() {};

    void Update();

};

