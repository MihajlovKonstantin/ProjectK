#include "Pch.h"


void Slime::Update()
{
	NPC::Update();
	if (NPC::GetDistance() >= 10)
	{
		if (m_jumpCoolTime-- < 0)
		{
			
			m_jumpCoolTime = m_SlimeJumpCoolTime;
		}
	}
}
