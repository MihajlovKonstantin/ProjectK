#include "Pch.h"
#include <utility>
#include "Data/Classes/Header/Player.h"

Player::~Player()
{
}

bool Player::IsPossibleAngle(float radian)
{
	bool _result = false;
	if (radian < 0)
	{
		radian += float(M_PI) * 2.0f;
	}
	radian = fmod(radian, 2.0f * float(M_PI));
	//radian -= float(M_PI) / 2.0f;
	float _delta = float(M_PI) *0.25f;
	if((radian<=_delta)||((radian>=	(float(M_PI) -_delta)	)&&(radian<=float(M_PI) +_delta)	)||(radian>= float(M_PI) *2.0f-_delta))
		_result = true;
	return _result;
}
Math::Rectangle Player::GetRect()
{
	return m_rectangle;
}
Math::Rectangle Player::GetHpRect()
{
	return m_hpRectangle;
}
void Player::Update()
{
	__test = m_collisionData.size();

	int index;
	if (!m_collisionData.empty())
	{
		std::pair<float, float> _comparePos = { m_collisionData[0].pos };
		OnLadderBlockFlag = m_collisionData[0].OnladerFlag;
		if(!OnLavaBlockFlag)OnLavaBlockFlag = m_collisionData[0].OnLavaFlag;
		
		index = 0;
		if (m_collisionData.size() > 1)
		{
			
			for (int i = 1; i < m_collisionData.size(); i++)
			{
				if (m_collisionData[i].BackStage)
				{
					if (m_collisionData[i].OnladerFlag)
					{
						OnLadderBlockFlag = true;
					}
				}
				if (m_collisionData[i].OnLavaFlag)
				{
					OnLavaBlockFlag = m_collisionData[i].OnLavaFlag;
				}
				switch (m_direction)
				{
				case Left:
					if (m_collisionData[index].BackStage)
					{
						index = i;
					}
					if (m_collisionData[i].pos.first <= _comparePos.first)
					{
						if (!(m_collisionData[i].sideRad == float(M_PI) * 1.5f))
						{
							if (!(m_collisionData[index].rad > m_collisionData[i].rad)&&!(m_collisionData[index].rad== m_collisionData[i].rad==0))
							{
								index = i;
								_comparePos = m_collisionData[i].pos;
							}
							
						}
					}
					break;
				case Right:
					if (m_collisionData[index].BackStage)
					{
						index = i;
					}
					if (m_collisionData[i].pos.first >= _comparePos.first)
					{
						if (!(m_collisionData[i].sideRad == float(M_PI) * 0.5f))
						{
							if (!(m_collisionData[index].rad > m_collisionData[i].rad))
							{
								index = i;
								_comparePos = m_collisionData[i].pos;
							}
							
						}
					}
					break;
				}
			}
			

		}
		if (!m_collisionData.empty())
		{
			m_collision = true;
			if (m_rad!=-1&&(!((m_rad == 0) || (m_rad == float(M_PI) * 2.0f) || (m_rad == float(M_PI)))))
			{
				m_groundFlag = true;
			}
			else
			{
				if (m_jumpPower == 0)
				{
					if (m_moveBlock[0])
					{
						m_groundFlag = true;
					}
					else
					{
						m_groundFlag = false;
					}
				}
			}
			
			if (m_collisionData.size() == 1)
			{
				m_rad = m_collisionData[0].rad;
				if (m_rad > 0 && m_rad<float(M_PI) * 0.5f)
				{
					m_rad = float(M_PI) * 0.25f;
				}
				if (m_rad > float(M_PI) * 0.5f && m_rad<float(M_PI) * 1.0f)
				{
					m_rad = float(M_PI) * 0.75f;
				}
			}
		}
		if (m_collision && (m_rad != m_collisionData[index].rad))
		{
			switch (m_direction)
			{
			case Direction::Left:
				if (fmod(m_collisionData[index].rad, 1.0f * float(M_PI)) < float(M_PI) * 0.5f)
				{
					if (m_collisionData[0].rad != m_collisionData[1].rad)
					{
						Move(-16 * sqrt(2) * 0.5, 16 * sqrt(2) * 0.5);
					}

				}
				break;
			case Direction::Right:
				if (fmod(m_collisionData[index].rad, 1.0f * float(M_PI)) > float(M_PI) * 0.5f)
				{
					if (m_collisionData[0].rad != m_collisionData[1].rad)
					{
						Move(16 * sqrt(2) * 0.5, 16 * sqrt(2) * 0.5);
					}

				}
				break;
			}


		}
		m_rad = m_collisionData[index].rad;
		m_sideRad = m_collisionData[index].sideRad;
		OnIceBlockFlag = m_collisionData[index].OnIceFlag;
		OnSnowBlockFlag = m_collisionData[index].OnSnowFlag;


		if (m_rad < 0)
		{
			m_rad += 2.0f * float(M_PI);
		}
		if (m_rad > 0 && m_rad<float(M_PI) * 0.5f)
		{
			m_rad = float(M_PI) * 0.25f;
		}
		if (m_rad > float(M_PI) * 0.5f && m_rad<float(M_PI) * 1.0f)
		{
			m_rad = float(M_PI) * 0.75f;
		}
		m_rad = fmod(m_rad, 2.0f * float(M_PI));
	}
	if (abs(m_rad-m_sideRad)<float(M_PI)&&!m_collisionData.empty())
	{
		m_speed.second = 0;
	}
	else if((!m_collisionData.empty()))
	{
		{
			if (m_moveBlock[2])
			{
 				m_jumpPower = 0.0f;
			}
		}
		
		m_speed.second = m_speedBase.second;
	}
	else
	{
		if (m_collisionData.empty())
		{
			m_rad = 0;
			m_speed.second = m_speedBase.second + m_jumpPower;
			m_sideRad = -1.0f;
			m_groundFlag = false;
			OnLadderBlockFlag = false; 
			if ((m_direction == Direction::Up) || (m_direction == Direction::Down))
			{
				m_direction = Direction::Stand;
			}
		}
		
	}
	float _drawRad = m_rad;


	if (_drawRad >= float(M_PI))
	{
		_drawRad = fmod(_drawRad, float(M_PI));
	}
	if (_drawRad >= float(M_PI)*0.5f)
	{
		_drawRad -= float(M_PI);
	}
	
	if (m_sideRad != -1)
	{
		switch (m_direction)
		{
		case Left:
			animation++;
			m_rectangle = Math::Rectangle{ 0,97,32,32 };
			if (animation > 30)
			{
				m_rectangle = Math::Rectangle{ 33,97,32,32 };
			}
			if (animation > 60)
			{
				m_rectangle = Math::Rectangle{ 65,97,32,32 };
			}
			if (animation > 90)
			{
				animation = 0;
			}
			m_mRotation = Math::Matrix::CreateRotationZ(_drawRad);
			m_hpRotation = Math::Matrix::CreateRotationZ(_drawRad);
			break;
		case Right:
			animation++;
			m_rectangle = Math::Rectangle{ 0,33,32,32 };
			if (animation > 30)
			{
				m_rectangle = Math::Rectangle{ 33,33,32,32 };
			}
			if (animation > 60)
			{
				m_rectangle = Math::Rectangle{ 65,33,32,32 };
			}
			if (animation > 90)
			{
				animation = 0;
			}
			m_mRotation = Math::Matrix::CreateRotationZ(_drawRad);
			m_hpRotation = Math::Matrix::CreateRotationZ(_drawRad);
			break;
		default:
			animation = 0;
			m_mRotation = Math::Matrix::CreateRotationZ(_drawRad);
			m_hpRotation = Math::Matrix::CreateRotationZ(_drawRad);
			m_rectangle = Math::Rectangle{ 0,65,32,32 };
			break;
		}

	}
	else
	{
		m_mRotation = Math::Matrix::CreateRotationZ(_drawRad);
		m_hpRotation = Math::Matrix::CreateRotationZ(_drawRad);
		switch (m_direction)
		{
		case Right:
			m_rectangle = Math::Rectangle{ 0,33,32,32 };
			break;
		case Left:
			m_rectangle = Math::Rectangle{ 0,97,32,32 };
		}

	}

	switch (m_direction)
	{
	case Stand:
		m_currentSpeed.first = 0;
		m_currentSpeed.second = m_speed.second;
		break;
	}
	if (m_rad + 0.0001 > 2.0f * float(M_PI))
	{
		//m_rad = fmod(m_rad + 0.0001, 2.0f * float(M_PI));
	}
	if ((m_rad + 0.0001) >= float(M_PI) && (m_rad<float(M_PI)))
	{
		m_rad = float(M_PI);
	}


	float _moveRad = fmod(m_rad + 0.0001, float(M_PI));
	if (_moveRad == 0.0001f)
	{
		_moveRad = 0;
	}
	if (m_rad > float(M_PI))
	{
		m_groundFlag = false;
		m_currentSpeed.second = m_speedBase.second;
	}
	m_speed.first = m_speedBase.first;
	if (OnIceBlockFlag)
	{
		m_speed.first *= 0.7f;
		m_speed.second *= 1;
	}
	if (OnSnowBlockFlag)
	{
		m_speed.first *= 1.8f;
		m_speed.second *= 1;
	}
	if (OnLavaBlockFlag)
	{
 		m_hp -= 5;
		if(m_hp < 0)m_hp = 0;
	}
	if (OnLadderBlockFlag)
	{
		m_groundFlag = true;
		m_currentSpeed.second = 0;
		m_speed.second = 0;
	}
	switch (m_direction)
		{
			case Right:
				
				m_currentSpeed.first = 0;
				if (m_groundFlag == true)
				{
					m_currentSpeed.first = m_speed.first * abs(cos(_moveRad)) - m_speed.second * sin(_moveRad);
					m_currentSpeed.second = m_speed.first * (sin(_moveRad)) + m_speed.second * cos(_moveRad);
					if ((abs(m_currentSpeed.first) != abs(m_currentSpeed.second)) && (m_rad != 0))
						{
							m_currentSpeed.first = m_currentSpeed.second;
						}
				}
				else
					{
						m_currentSpeed.first = m_speed.first * cos(_moveRad) - m_speed.second * sin(_moveRad);
						if (m_jumpPower <= 0)
						{
							m_currentSpeed.second = m_speed.first * (sin(_moveRad)) + m_speed.second * cos(_moveRad);
						}
						else
						{
							m_currentSpeed.second = 0;
						}
					}
			
			break;
		case Left:
				m_currentSpeed.first = 0;
				if (m_groundFlag == true)
				{
					m_currentSpeed.first = m_speed.first * (-abs(cos(_moveRad))) - m_speed.second * sin(_moveRad);
					m_currentSpeed.second = m_speed.first * (sin(_moveRad)) + m_speed.second * cos(_moveRad);
					if ((abs(m_currentSpeed.first) != abs(m_currentSpeed.second)) && (m_rad != 0))
					{
						m_currentSpeed.first = -m_currentSpeed.second;
					}
				}
				else
					{
						m_currentSpeed.first = m_speed.first * cos(_moveRad + float(M_PI)) - m_speed.second * sin(_moveRad + float(M_PI));
						if (m_jumpPower <= 0)
						{
							m_currentSpeed.second = m_speed.first * (sin(_moveRad)) + m_speed.second * cos(_moveRad);
						}
						else
						{
							m_currentSpeed.second = 0;
						}
						
					}
			break;
		case Up:
			m_groundFlag = true;
			m_currentSpeed.first = 0;
			m_currentSpeed.second = 2;
			break;

		case Down:
			m_groundFlag = true;
			m_currentSpeed.first = 0;
			if (m_moveBlock[0])
			{
				m_currentSpeed.second = 0;
			}
			else
			{
				m_currentSpeed.second = - 2;
			}
			break;
		case Stand:
			m_currentSpeed.first = 0;
			m_currentSpeed.second = m_speed.second;
			break;
		}

	if (m_rad == 0||(m_rad ==float(M_PI)*0.5f)|| (m_rad == float(M_PI) * 1.0f)|| (m_rad == float(M_PI) * 1.5f))
	{
		if (m_speed.second < 0)
		{
			if (!m_moveBlock[0])
			{
				//m_currentSpeed.second = m_speed.first * sin(m_rad) + m_speed.second * cos(m_rad);
			}
			else
			{
	 			m_currentSpeed.second = 0.0f;
			}
		}
		else
		{
			if (!m_moveBlock[2])
			{
				//m_currentSpeed.second = m_speed.first * sin(m_rad) + m_speed.second * cos(m_rad);
			}
			else
			{
				m_currentSpeed.second = 0.0f;
			}
		}
		if (m_currentSpeed.first > 0)
		{
			//if (m_moveBlock[1] && ((m_rad == 0) || (m_rad == float(M_PI) * 0.5f) || (m_rad == float(M_PI) * 1.0f) || (m_rad == float(M_PI) * 1.5f)))
			if (m_moveBlock[1])
			{
				m_currentSpeed.first = 0;
			}
		}
		else
		{
			//if (m_moveBlock[3] && ((m_rad == 0) || (m_rad == float(M_PI) * 0.5f) || (m_rad == float(M_PI) * 1.0f) || (m_rad == float(M_PI) * 1.5f)))
			if(m_moveBlock[3])
			{
				m_currentSpeed.first = 0;
			}
		}
	}
	else
	{
		if (m_direction != Stand)
		{
			switch (m_direction)
			{
			case Left:
				if ((_moveRad<float(M_PI) * 0.5f) && (_moveRad > 0))
				{
					m_currentSpeed.second = -(m_speed.first * (sin(_moveRad)) + m_speed.second * cos(_moveRad));
				}
				if (((_moveRad > float(M_PI) * 0.5f) && (_moveRad < float(M_PI))))
				{
					m_currentSpeed.second = (m_speed.first * (sin(_moveRad)) + m_speed.second * cos(_moveRad));
				}
				break;
			case Right:
				if ((_moveRad<float(M_PI) * 0.5f) && (_moveRad > 0))
				{
					m_currentSpeed.second = (m_speed.first * (sin(_moveRad)) + m_speed.second * cos(_moveRad));
				}
				if (((_moveRad > float(M_PI) * 0.5f) && (_moveRad < float(M_PI))))
				{
					m_currentSpeed.second = -(m_speed.first * (sin(_moveRad)) + m_speed.second * cos(_moveRad));
				}
				break;
			}
		}
	}
	if ((!m_groundFlag)&&(!(m_jumpPower>0)))
	{
		m_currentSpeed.second = m_speedBase.second;
	}
	m_gPos.first += m_currentSpeed.first;
	m_gPos.second += m_currentSpeed.second+m_jumpPower;
	m_pos.first = m_gPos.first - m_scroll->first;
	m_pos.second = m_gPos.second - m_scroll->second;
	m_mTrans = Math::Matrix::CreateTranslation(m_pos.first, m_pos.second, 0);
	m_hpTrans = Math::Matrix::CreateTranslation(m_pos.first, m_pos.second + m_hpY, 0);
	
	if (m_rad < 0)
	{
		m_rad += 2.0f * float(M_PI);
	}
	if (m_rad > float(M_PI))
	{
		//m_rad -= float(M_PI);
	}
	if (m_rad+0.0001 >= float(M_PI) * 0.25f)
	{
		m_mTrans = Math::Matrix::CreateTranslation(m_pos.first+ 16.0f * sqrt(2)*0.5f, m_pos.second- 16.0f * sqrt(2) * 0.5f, 0);
		m_hpTrans = Math::Matrix::CreateTranslation(m_pos.first+ 16.0f * sqrt(2)*0.5f, m_pos.second- 16.0f + m_hpY * sqrt(2) * 0.5f, 0);
	}
	if (m_rad + 0.0001 >= float(M_PI) * 0.75f)
	{
		m_mTrans = Math::Matrix::CreateTranslation(m_pos.first - 16.0f * sqrt(2) * 0.5f, m_pos.second - 16.0f * sqrt(2) * 0.5f, 0);
		m_hpTrans = Math::Matrix::CreateTranslation(m_pos.first - 16.0f * sqrt(2) * 0.5f, m_pos.second - 16.0f + m_hpY * sqrt(2) * 0.5f, 0);
	}
	if (m_rad + 0.0001 >= float(M_PI) * 1.25f)
	{
		m_mTrans = Math::Matrix::CreateTranslation(m_pos.first - 16.0f * sqrt(2) * 0.5f, m_pos.second + 16.0f * sqrt(2) * 0.5f, 0);
		m_hpTrans = Math::Matrix::CreateTranslation(m_pos.first - 16.0f * sqrt(2) * 0.5f, m_pos.second + 16.0f + m_hpY * sqrt(2) * 0.5f, 0);
	}
	if (m_rad + 0.0001 >= float(M_PI) * 1.75f)
	{
		m_mTrans = Math::Matrix::CreateTranslation(m_pos.first + 16.0f * sqrt(2) * 0.5f, m_pos.second + 16.0f * sqrt(2) * 0.5f, 0);
		m_hpTrans = Math::Matrix::CreateTranslation(m_pos.first + 16.0f * sqrt(2) * 0.5f, m_pos.second + 16.0f + m_hpY * sqrt(2) * 0.5f, 0);
	}
	if (m_rad == 0 || (m_rad == float(M_PI) * 0.5f) || (m_rad == float(M_PI) * 1.0f) || (m_rad == float(M_PI) * 1.5f))
	{
		m_mTrans = Math::Matrix::CreateTranslation(m_pos.first, m_pos.second, 0);
		m_hpTrans = Math::Matrix::CreateTranslation(m_pos.first, m_pos.second + m_hpY, 0);
	}
	
	m_matrix = m_mRotation * m_mTrans;
	m_hpMatrix = m_hpRotation * m_hpTrans;
	for (int i = 0; i < 4; i++)
	{
		m_moveBlockBuff[i] = m_moveBlock[i];
		m_moveBlock[i] = false;
	}
	if (m_jumpPower > 0)
	{
		m_jumpPower -= 0.1f;
	} else
	if (m_jumpPower < 0)
	{
		m_jumpPower = 0;
	}
	if (m_jumpPower >= m_jumpSpeed * 2)
	{
		int i = 0;
	}
	
	if (OnSnowBlockFlag == true)
	{
		OnSnowBlockFlag = false;
	}
	
	if (OnIceBlockFlag == true)
	{
		OnIceBlockFlag = false;
	}

	if (OnLavaBlockFlag == true)
	{
		OnLavaBlockFlag = false;
	}

	switch ((int)m_hp)
	{
	case 100:
		m_hpRectangle = Math::Rectangle(0, 0, 34, 20);
		break;
	case 90:
		m_hpRectangle = Math::Rectangle(34, 0, 34, 20);
		break;
	case 80:
		m_hpRectangle = Math::Rectangle(68, 0, 34, 20);
		break;
	case 70:
		m_hpRectangle = Math::Rectangle(102, 0, 34, 20);
		break;
	case 60:
		m_hpRectangle = Math::Rectangle(136, 0, 34, 20);
		break;
	case 50:
		m_hpRectangle = Math::Rectangle(170, 0, 34, 20);
		break;
	case 40:
		m_hpRectangle = Math::Rectangle(0, 20, 34, 20);
		break;
	case 30:
		m_hpRectangle = Math::Rectangle(34, 20, 34, 20);
		break;
	case 20:
		m_hpRectangle = Math::Rectangle(68, 20, 34, 20);
		break;
	case 10:
		m_hpRectangle = Math::Rectangle(102, 20, 34, 20);
		break;
	case 0:
		m_hpRectangle = Math::Rectangle(136, 20, 34, 20);
		break;
	}

	m_collisionData.clear();
}

void Player::Jump()
{
	if (m_groundFlag)
	{
		m_jumpPower += m_jumpSpeed;
		
		m_secondJumpFlg = false;
		m_notJumpFlg = true;
		m_groundFlag = false;
		if (!m_groundFlag)m_secondJumpFlg = true;
	}
	else
	{
		if (m_secondJumpFlg && m_notJumpFlg)
		{
			m_jumpPower = 0;
			m_jumpPower += m_secondJumpSpeed;
			m_notJumpFlg = false;
		}
	}
	
	
}

bool Player::CollisionToBlock(Block block)
{
	//result of function
	bool _result = false;

	//block Collision data
	DirectX::BoundingBox _box;
	std::pair<float, float> _bPos = block.GetGPos();
	std::pair<float, float> _bSize = block.GetSize();
	float _sideAngle = 0.0f;
	float _bRad = block.GetRad();
	float _dX = 0.0f, _dY = 0.0f;

	//player collision data
	DirectX::BoundingBox _playerBox;
	std::pair<float, float> _position;

	//position after normalize with block without angle
	_position.first = m_gPos.first - _bPos.first;
	_position.second = m_gPos.second - _bPos.second;

	//after angle normalizing
	std::pair<float, float>__buffer = { _position.first,_position.second };
	_position.first = _position.first * cos(_bRad) - sin(_bRad) * _position.second;
	_position.second = __buffer.first * sin(_bRad) + cos(_bRad) * __buffer.second;

	//normalize block pos
	_bPos = { 0,0 };
	
	//create collizion box
	_playerBox = DirectX::BoundingBox(DirectX::XMFLOAT3(_position.first, _position.second, 0), DirectX::XMFLOAT3(_bSize.first / 2.0f, _bSize.second / 2.0f, 0));
	_box = DirectX::BoundingBox(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(_bSize.first / 2.0f, _bSize.second / 2.0f, 0));

	//Vector creating
	std::array<DirectX::XMVECTOR, 4> _bOriginVector;
	std::array<DirectX::XMVECTOR, 4> _bNorVector;
	std::array<bool, 4> _intersectVector;
	std::array< float, 4> _absDelta;


	_bOriginVector[0] = { -_bSize.first / 2.0f,_bSize.second / 2.0f,0 };
	_bOriginVector[1] = { -_bSize.first / 2.0f,_bSize.second / 2.0f,0 };
	_bOriginVector[2] = { _bSize.first / 2.0f,-_bSize.second / 2.0f,0 };
	_bOriginVector[3] = { _bSize.first / 2.0f,-_bSize.second / 2.0f,0 };

	_bNorVector[0] = DirectX::XMVector3Normalize({ _bSize.first,0,0 });
	_bNorVector[1] = DirectX::XMVector3Normalize({ 0,-_bSize.second,0 });
	_bNorVector[2] = DirectX::XMVector3Normalize({ -_bSize.first,0,0 });
	_bNorVector[3] = DirectX::XMVector3Normalize({ 0,_bSize.second,0 });

	float _distanceBuf = FLT_MAX;
	float _distance = _distanceBuf;

	for (int i = 0; i < 4; i++)
	{
		_intersectVector[i] = _playerBox.Intersects(_bOriginVector[i], _bNorVector[i], _distanceBuf);
		if ((_distanceBuf < _distance) && (_intersectVector[i]))
		{
			_distance = _distanceBuf;
		}
	}
	_result = _playerBox.Intersects(_box);
	if (_result)
	{
		if (block.GetBackStage())
		{
			m_groundFlag = true;
		}
		if ((_bRad<float(M_PI)) && !((_bRad == 0) || (_bRad == float(M_PI) * 2.0f) || (_bRad == float(M_PI))))
		{
			m_groundFlag = true;
		}
	}
	/*
	if (!_result)
	{
		if (_distance <= 0)
		{
			_result = true;
		}
	}
	*/

	int _intersectNum = 0;
	if (_intersectVector[1])
	{
		_sideAngle = float(M_PI) * 0.5f;
		if (_position.second + 1.5f > 32.0f)
		{
			_position.second = 32.0f;
		}
		if ((_position.second < (_bPos.second + _bSize.second)) && (_position.second > _bPos.second - _bSize.second))
		{
			if ((_bRad == 0) || (_bRad == float(M_PI) * 2.0f)||(_bRad==float(M_PI)))
			{
				if (!block.m_backStage)
				{
					m_moveBlock[1] = true;
				}
				
			}
			
		}
		_intersectNum++;
		_absDelta[1] = abs(abs(_playerBox.Center.x) - 32.0f) + abs(abs(_playerBox.Center.y) - 32.0f);
	}

	if (_intersectVector[3])
	{
		if (_position.second + 1.5f > 32.0f)
		{
			_position.second = 32.0f;
		}
		_sideAngle = float(M_PI) * 1.5f;
		bool _first, _second;
		_first = _position.second < _bPos.second + _bSize.second;
		_second = _position.second > _bPos.second - _bSize.second;
		if ((_first) && (_second))
		{
			if ((_bRad == 0) || (_bRad == float(M_PI) * 2.0f) || (_bRad == float(M_PI)))
			{
				if (!block.m_backStage)
				{
					m_moveBlock[3] = true;
				}
			}
			
		}
		_intersectNum++;
		_absDelta[3] = abs(abs(_playerBox.Center.x) - 32.0f) + abs(abs(_playerBox.Center.y) - 32.0f);
	}
	if (_intersectVector[0])
	{
		_sideAngle = 0;
		if ((_position.first < _bPos.first + _bSize.first - 3.5f) && (_position.first > _bPos.first - _bSize.first + 3.5f))
		{
			
			if ((_bRad == 0) || (_bRad == float(M_PI) * 2.0f) || (_bRad == float(M_PI)))
			{
				if (!block.m_backStage)
				{
					m_moveBlock[0] = true;
				}
			}
		}
		_intersectNum++;
		_absDelta[0] = abs(abs(_playerBox.Center.x) - 32.0f) + abs(abs(_playerBox.Center.y) - 32.0f);
	}
	if (_intersectVector[2])
	{
		_sideAngle = float(M_PI);
		if ((_position.first < _bPos.first + _bSize.first)  && (_position.first > _bPos.first - _bSize.first))
		{
			if ((_bRad == 0) || (_bRad == float(M_PI) * 2.0f) || (_bRad == float(M_PI)))
			{
				if (!block.m_backStage)
				{
					m_moveBlock[2] = true;
				}
			}
		}
		_intersectNum++;
		_absDelta[2] = abs(abs(_playerBox.Center.x) - 32.0f) + abs(abs(_playerBox.Center.y) - 32.0f);
	}
	if (m_direction == Direction::Right)
	{
		//_bRad += float(M_PI);
	}
	if ((_bRad == m_rad)&&(m_sideRad!=-1))
	{
		_sideAngle = m_sideRad;
	}
	if (_result)
	{
		
		if (_intersectNum > 1)
		{
			_sideAngle = -1;
			if ((_position.second >= (_bPos.second + _bSize.second * 0.5f)) && ((_position.first > (_bPos.first - _bSize.first)) && (_position.first < (_bPos.first + _bSize.first))))
			{
				_sideAngle = 0;
			}
			if ((_position.second <= (_bPos.second - _bSize.second * 0.5f)) && ((_position.first >= (_bPos.first - _bSize.first)) && (_position.first <= (_bPos.first + _bSize.first))))
			{
				_sideAngle = float(M_PI);
			}
			if (_sideAngle < 0)
			{
				if (_intersectVector[1])
				{
					_sideAngle = float(M_PI) * 0.5f;
				}
				else
				{
					_sideAngle = float(M_PI) * 1.5f;
				}
			}
			if ((_bRad == m_rad) && (m_sideRad != -1))
			{
				_sideAngle = m_sideRad;
			}
			auto test = float(M_PI);
			if (!block.GetBackStage()&& ((_bRad == 0) || (_bRad == float(M_PI) * 2.0f) || (_bRad == float(M_PI))))
			{
				if (abs(_position.first) > abs(_position.second))
				{
					if (_position.first > 0)
					{
						Move(32.0f - _position.first, 0);
					}
					else
					{
						Move(-(_position.first + 32.0f), 0);
					}
				}
				else
				{
					if (_position.second > 0)
					{
						Move(0, 32.0f - _position.second);
					}
					else
					{
						Move(0, -(_position.second + 32.0f));
					}
				}
			}
		}
		

		if (_bRad <float(M_PI))
		{
			//m_groundFlag = true;
		}
		m_collisionData.push_back({ (_bRad),_sideAngle,{block.GetGPos()},block.m_backStage,block.m_iceBlock,block.m_snowBlock ,block.m_laderBlock,block.m_lavaBlock } );

	}
	return _result;
}

bool Player::CollisionToItem(Item* item)
{
	bool _result = false;
	DirectX::BoundingBox _playerBox = DirectX::BoundingBox({ m_pos.first,m_pos.second,0 }, { 16.0f, 16.0f, 0 });
	std::pair<float, float> _itemPos = item->GetPos();
	DirectX::BoundingBox _itemBox = DirectX::BoundingBox({_itemPos.first,_itemPos.second,0}, {16.0f,16.0f,0});
	_result= _playerBox.Intersects(_itemBox);
	if (_result)
	{
		item->Destruct();
	}
	return _result;
}

void Player::Move(float x, float y)
{
	m_gPos.first += x;
	m_gPos.second += y;
}

Math::Matrix Player::GetMatrix()
{
	return m_matrix;
}

Math::Matrix Player::GetHpMatrix()
{
	return m_hpMatrix;
}

KdTexture* Player::GetTexture()
{
	return m_texture;
}

KdTexture* Player::GetHpTexture()
{
	return m_hpTexture;
}

float Player::GetAngle()
{
	if (m_rad)
	{
		return DirectX::XMConvertToDegrees(m_rad);
	}
	return DirectX::XMConvertToDegrees(m_rad);
}

void Player::SetDirection(Direction direction)
{
	m_direction = direction;
}

void Player::CollisionClear()
{
	m_collisionData.clear();
}

bool Player::GetOnGroundFlag()
{
	return m_groundFlag;
}
bool Player::GetOnLadderFlag()
{
	return OnLadderBlockFlag;
}
void Player::SetScroll(std::pair<int, int>* scroll)
{
	m_scroll = scroll;
}

std::pair<float, float> Player::GetGPos()
{
	return m_gPos;
}

void Player::SetHp(float hp)
{
	m_hp = hp;
}

float Player::GetHp()
{
	return m_hp;
}

void Player::UpdateTransMat()
{
	m_mTrans = Math::Matrix::CreateTranslation(m_gPos.first - m_scroll->first, m_gPos.second - m_scroll->second, 0.0f);
	m_matrix = m_mRotation * m_mTrans;
	m_hpTrans = Math::Matrix::CreateTranslation(m_gPos.first - m_scroll->first, m_gPos.second + m_hpY - m_scroll->second, 0.0f);
	m_hpMatrix = m_hpRotation * m_hpTrans;
}

int Player::GetColissionDataSize()
{
	return __test;
}

bool Player::GetHpAlpha()
{
	return m_hpAlphaFlg;
}

void Player::SetHpAlpha(bool hpAlpha)
{
	m_hpAlphaFlg = hpAlpha ;
}
