#include "Pch.h"

void SnowBall::Update()
{
	if (m_aliveFlg)
	{
		if (!m_onlyFlg)
		{
			Player::SetDirection(Left);
			if (GetAngle() == 45 || m_leftCoolTime <= m_directionCoolTime)
			{
				if (m_leftCoolTime-- < 0)
				{
					m_rightCoolTime = m_directionCoolTime;
					m_onlyFlg = true;
				}
			}
			if (GetAngle() == 135 || m_rightCoolTime <= m_directionCoolTime)
			{
				if (m_rightCoolTime-- < 0)
				{
					m_leftCoolTime = m_directionCoolTime;
					m_onlyFlg = true;
				}
			}
		}

		//左下がりの坂だと左に進む
		if (GetAngle() == 45 || m_leftCoolTime <= m_directionCoolTime)
		{
			if (m_leftCoolTime-- < 0)	//少しの間右に進む
			{
				m_rightCoolTime = m_directionCoolTime;
				Player::SetDirection(Left);
			}
		}
		//右下がりの坂だと右に進む
		if (GetAngle() == 135 || m_rightCoolTime <= m_directionCoolTime)
		{
			if (m_rightCoolTime-- < 0)	//少しの間左に進む
			{
				m_leftCoolTime = m_directionCoolTime;
				Player::SetDirection(Right);
			}
		}

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
}