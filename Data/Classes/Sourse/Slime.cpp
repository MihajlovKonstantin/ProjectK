#include "Pch.h"

Slime::Slime()
{
	m_jumpSpeed *= 0.85;
}

void Slime::Update()
{
	NPC::AIUpdate();
	if (Discovery())	//�v���C���[��������
	{
		if (m_jumpCoolTime-- < 0)
		{
			Jump();

			m_jumpCoolTime = m_slimeJumpCoolTime;
		}
		
		if (m_onGroundFlag)m_emyMoveFlg = false;	//�X���C���̓W�����v���̂ݓ����Ăق���
		else m_emyMoveFlg = true;
	}
}
