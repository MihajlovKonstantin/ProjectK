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
		//最初は左に動く
		/*if (!m_onlyFlg)
		{
			Player::SetDirection(Left);
			auto test = GetAngle();
			if (GetAngle() == 45 || m_leftCoolTime < m_directionCoolTime)
			{
				if (m_leftCoolTime-- < 0)
				{

					m_onlyFlg = true;
				}
			}
			if (GetAngle() == 135 || m_rightCoolTime < m_directionCoolTime)
			{
				if (m_rightCoolTime-- < 0)
				{

					m_onlyFlg = true;
				}
			}
		}*/

		auto test = GetAngle();
		//左下がりの坂だと左に進む
		if (GetAngle() == 45)
		{
			m_leftFlg = true;
			if (m_leftFlg && m_rightFlg)
			{
				m_leftCoolTime--;	
				Player::SetDirection(Right);	//少しの間右に進む
			}
			if (m_leftCoolTime < 0)
			{
				m_rightFlg = false;
				m_leftCoolTime = m_directionCoolTime;
			}
		}
		//右下がりの坂だと右に進む
		if (GetAngle() == 135)
		{
			m_rightFlg = true;

			if (m_leftFlg && m_rightFlg)
			{
				m_rightCoolTime--;	
				Player::SetDirection(Left);		//少しの間左に進む
			}
			if (m_rightCoolTime < 0)
			{
				m_leftFlg = false;
				m_rightCoolTime = m_directionCoolTime;
			}
		}
			if (m_leftFlg && !m_rightFlg)Player::SetDirection(Left);
			if (m_rightFlg && !m_leftFlg)Player::SetDirection(Right);

			if (m_stopFlag)m_aliveFlg = false;
	
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