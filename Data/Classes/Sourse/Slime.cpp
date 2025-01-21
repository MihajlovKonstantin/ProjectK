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
	if (m_discovery)	//�v���C���[��������
	{
		int _coolTime = 10;
		int _coolTimeMax = 10;
		if (m_jumpCoolTime-- < 0)
		{
			Jump();
			m_onGroundFlag = false;
			m_groundFlag = false;
			m_jumpCoolTime = m_slimeJumpCoolTime;
			_coolTime = 0;
		}
		else
		{
			_coolTime++;
		}
		//�X���C���̓W�����v���̂ݓ����Ăق���
		if (_coolTime >= _coolTimeMax)
		{
			(m_groundFlag) ? m_emyMoveFlg = false : m_emyMoveFlg = true;
		}
		if (OnLadderBlockFlag) m_emyMoveFlg = true;
	}
	
	NPC::AIUpdate();
}
