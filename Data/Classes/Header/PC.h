#pragma once
#include "Player.h"
class PC :
    public Player
{
protected :
    std::pair<float, float> InitPos;
public:
    PC(std::pair<float, float>pos, std::pair<float, float>speed, KdTexture* texture, KdTexture* hpTexture);
    PC();
    std::pair<float, float> GetPos();
    void Init(std::pair<float, float>);
    void Update();
    bool MovePossible();
    int GetDirection();
    std::pair<float, float> GetPlayerPos();
    void SetPlayerPos(std::pair<float, float>pos);
    bool GetMoveBlock(int index);
};

