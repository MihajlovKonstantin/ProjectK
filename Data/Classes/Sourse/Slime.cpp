#include "Data/Classes/Header/Slime.h"

Slime::Slime(KdTexture* texture, std::pair<float, float> pos, std::pair<float, float>speed)
{
	m_jumpSpeed *= 0.85;
	m_gPos = pos;
	m_pos.first = m_gPos.first-m_scroll->first;
	m_pos.second = m_gPos.second - m_scroll->second;

	m_speedBase = speed;
	m_speed = m_speedBase;
	m_texture = texture;
}

Slime::~Slime()
{
}

void Slime::Update()
{
	Discovery();
	if (m_discovery)	//ƒvƒŒƒCƒ„[”­Œ©”»’è
	{
		if (m_jumpCoolTime-- < 0)
		{
			Jump();
			m_onGroundFlag = false;
			m_groundFlag = false;
			m_jumpCoolTime = m_slimeJumpCoolTime;
		}
		if (OnLadderBlockFlag) m_emyMoveFlg = true;
	}
	
	NPC::AIUpdate();
		
;
}
