#include "Data/Classes/Header/SnowBall.h"

SnowBall::SnowBall(KdTexture* texture, std::pair<float, float> pos, std::pair<float, float> speed)
{
	m_gPos = pos;
	m_pos.first = m_gPos.first - m_scroll->first;
	m_pos.second = m_gPos.second - m_scroll->second;
	m_speedBase = speed;
	m_speed = m_speedBase;
	m_texture = texture;
}

void SnowBall::Update()
{
	m_snowBallFlg = true;
	if (m_aliveFlg)
	{
		auto _angle = GetAngle();
		//��������̍₾�ƍ��ɐi��
		if ((_angle >= 44) && (_angle <= 46))
		{
			m_leftFlg = true;
			if (m_leftFlg && m_rightFlg)
			{
				m_leftCoolTime--;	
				Player::SetDirection(Right);	//�����̊ԉE�ɐi��
			}
			if (m_leftCoolTime < 0)
			{
				m_rightFlg = false;
				m_leftCoolTime = m_directionCoolTime;
			}
		}
		//�E������̍₾�ƉE�ɐi��
		if ((_angle >= 134) && (_angle <= 136))
		{
			m_rightFlg = true;

			if (m_leftFlg && m_rightFlg)
			{
				m_rightCoolTime--;	
				Player::SetDirection(Left);		//�����̊ԍ��ɐi��
			}
			if (m_rightCoolTime < 0)
			{
				m_leftFlg = false;
				m_rightCoolTime = m_directionCoolTime;
			}
		}
			if (m_leftFlg && !m_rightFlg)Player::SetDirection(Left);
			if (m_rightFlg && !m_leftFlg)Player::SetDirection(Right);

			//�ǂɂԂ���Ɖ��邽��
			if (m_moveBlock[1] || m_moveBlock[3])
			{
				m_hp -= 10;
			}
	
	}
	else
	{
		if (m_regenerationCoolTime-- < 0)
		{
			m_regenerationCoolTime = m_regenerationTime;
			m_aliveFlg = true;
		}
	}
		BotUpdate();
}