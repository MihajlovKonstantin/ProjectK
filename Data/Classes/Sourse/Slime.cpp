#include "Pch.h"

Slime::Slime()
{
	m_jumpSpeed *= 0.85;
}

void Slime::Update()
{
	NPC::AIUpdate();
	if (Discovery())	//プレイヤー発見判定
	{
		if (m_jumpCoolTime-- < 0)
		{
			Jump();

			m_jumpCoolTime = m_slimeJumpCoolTime;
		}
		
		if (m_onGroundFlag)m_emyMoveFlg = false;	//スライムはジャンプ中のみ動いてほしい
		else m_emyMoveFlg = true;
	}
}
