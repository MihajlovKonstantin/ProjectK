#include "Pch.h"

Slime::Slime()
{
	m_jumpSpeed *= 0.85;
}

void Slime::Update()
{
	if (m_type != TypeSlime)return;

	NPC::AIUpdate();
	if (Discovery())	//プレイヤー発見判定
	{
		if (m_jumpCoolTime-- < 0)
		{
			Jump();
			
			m_jumpCoolTime = m_SlimeJumpCoolTime;
		}
	}
	else Player::SetDirection(Stand);
}
