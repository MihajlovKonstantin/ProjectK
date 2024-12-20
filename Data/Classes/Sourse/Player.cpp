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
void Player::Update()
{
	
	m_stopFlag = false;
	//m_scale = { 1,1 };
	
	int index;
	if (!m_collisionData.empty())
	{
		std::pair<float, float> _comparePos = { m_collisionData[0].pos };
		
		index = 0;
		if (m_collisionData.size() > 1)
		{
			for (int i = 1; i < m_collisionData.size(); i++)
			{
				switch (m_direction)
				{
				case Left:
					if (m_collisionData[i].pos.first <= _comparePos.first)
					{
						if (m_collisionData[i].sideRad == float(M_PI) * 1.5f)
						{
							m_stopFlag = true;
						}
						else
						{
							index = i;
							_comparePos = m_collisionData[i].pos;

							
						}
					}
					break;
				case Right:
					if (m_collisionData[i].pos.first >= _comparePos.first)
					{
						if (m_collisionData[i].sideRad == float(M_PI) * 0.5f)
						{
							m_stopFlag = true;
						}
						else
						{
							index = i;
							_comparePos = m_collisionData[i].pos;
						}
					}
					break;
				}
			}
			

		}
		if (!m_collisionData.empty())
		{
			m_collision = true;
			m_groundFlag = true;
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
		else
		{
			m_stopFlag = true;
		}
		
		if (m_collision&&(m_rad != m_collisionData[index].rad))
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
		m_currentCollisionValue = m_collisionData[index].collisionValue;
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
	else if(!m_collisionData.empty())
	{
		m_jumpPower = 0.0f;
		m_speed.second = m_speedBase.second;
	}
	else
	{
		if (m_collisionData.empty())
		{
			m_rad = 0;
			m_speed.second = m_speedBase.second + m_jumpPower;
			m_sideRad = -1.0f;
			m_currentCollisionValue = -1.0f;
			m_groundFlag = false;
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
			break;
		default:
			animation = 0;
			m_mRotation = Math::Matrix::CreateRotationZ(_drawRad);
			m_rectangle = Math::Rectangle{ 0,65,32,32 };
			break;
		}

	}
	else
	{
		m_mRotation = Math::Matrix::CreateRotationZ(_drawRad);
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
		m_stopFlag = true;
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
	switch (m_direction)
		{
			case Right:
				
				m_currentSpeed.first = 0;
				if (m_groundFlag == true)
					{
						m_currentSpeed.first = m_speed.first * abs(cos(_moveRad)) - m_speed.second * sin(_moveRad);
						m_currentSpeed.second = m_speed.first * (sin(_moveRad)) + m_speed.second*cos(_moveRad);
						if ((abs(m_currentSpeed.first) != abs(m_currentSpeed.second))&&(m_rad!=0))
						{
							m_currentSpeed.first = m_currentSpeed.second;
						}
					}
				else
					{
						m_currentSpeed.first = m_speed.first * cos(_moveRad) - m_speed.second * sin(_moveRad);
						m_currentSpeed.second = m_speed.first * (sin(_moveRad)) + m_speed.second * cos(_moveRad);
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
						m_currentSpeed.second = m_speed.first * (sin(_moveRad)) + m_speed.second * cos(_moveRad);
					}
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
	m_gPos.first += m_currentSpeed.first;
	m_gPos.second += m_currentSpeed.second+m_jumpPower;
	m_pos.first = m_gPos.first - m_scroll->first;
	m_pos.second = m_gPos.second - m_scroll->second;
	m_mTrans = Math::Matrix::CreateTranslation(m_pos.first, m_pos.second, 0);
	
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
	}
	if (m_rad + 0.0001 >= float(M_PI) * 0.75f)
	{
		m_mTrans = Math::Matrix::CreateTranslation(m_pos.first - 16.0f * sqrt(2) * 0.5f, m_pos.second - 16.0f * sqrt(2) * 0.5f, 0);
	}
	if (m_rad + 0.0001 >= float(M_PI) * 1.25f)
	{
		m_mTrans = Math::Matrix::CreateTranslation(m_pos.first - 16.0f * sqrt(2) * 0.5f, m_pos.second + 16.0f * sqrt(2) * 0.5f, 0);
	}
	if (m_rad + 0.0001 >= float(M_PI) * 1.75f)
	{
		m_mTrans = Math::Matrix::CreateTranslation(m_pos.first + 16.0f * sqrt(2) * 0.5f, m_pos.second + 16.0f * sqrt(2) * 0.5f, 0);
	}
	if (m_rad == 0 || (m_rad == float(M_PI) * 0.5f) || (m_rad == float(M_PI) * 1.0f) || (m_rad == float(M_PI) * 1.5f))
	{
		m_mTrans = Math::Matrix::CreateTranslation(m_pos.first, m_pos.second, 0);
	}
	
	m_matrix = m_mRotation * m_mTrans;
	for (int i = 0; i < 4; i++)
	{
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
	//デバッグ用true,falseキー制御
	if (GetAsyncKeyState('O'))OnSnowBlockFlag = true;
	if (GetAsyncKeyState('I'))OnSnowBlockFlag = false;
	if (OnSnowBlockFlag == true)//雪ブロックの上にいるとき足が遅くなる
	{
		m_speed.first = m_speed.first - 0.02;
		if (m_speed.first < 1.0f) 
		{
			m_speed.first = 1.0f;
		}
	}
	if (OnSnowBlockFlag == false)//雪ブロックの上じゃないとき普通の速度に戻る
	{
		m_speed.first = m_speed.first + 0.02;
		if (m_speed.first > 2.0f)
		{
			m_speed.first = 2.0f;
		}
	}
	if (OnIceBlockFlag == true)
	{
		
	}
	
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
	bool _result = false;
	std::pair<float, float> _bPos = block.GetGPos();
	std::pair<float, float> _bSize = block.GetSize();
	std::pair<float, float> _position;
	DirectX::BoundingBox _sphere;
	DirectX::BoundingBox _box;
	float _sideAngle = 0.0f;
	float _dX = 0.0f, _dY = 0.0f;
	float _bRad = block.GetRad();
	_position.first = m_gPos.first - _bPos.first;
	_position.second = m_gPos.second - _bPos.second;
	_bPos = { 0,0 };
	std::pair<float, float>__buffer = { _position.first,_position.second };
	_position.first = _position.first * cos(_bRad) - sin(_bRad) * _position.second;
	_position.second = __buffer.first * sin(_bRad) + cos(_bRad) * __buffer.second;

	_sphere = DirectX::BoundingBox(DirectX::XMFLOAT3(_position.first, _position.second, 0), DirectX::XMFLOAT3(_bSize.first / 2.0f, _bSize.second / 2.0f, 0));
	_box = DirectX::BoundingBox(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(_bSize.first / 2.0f, _bSize.second / 2.0f, 0));
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
		_intersectVector[i] = _sphere.Intersects(_bOriginVector[i], _bNorVector[i], _distanceBuf);
		if (_distanceBuf < _distance && _intersectVector[i])
		{
			_distance = _distanceBuf;
		}
	}
	_result = _sphere.Intersects(_box);
	if (!_result)
	{
		if (_distance <= 0)
		{
			_result = true;
		}
	}

	if (m_direction == Direction::Right)
	{
		_bRad += float(M_PI);
	}
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
				m_moveBlock[1] = true;
			}
			
		}
		_intersectNum++;
		_absDelta[1] = abs(abs(_sphere.Center.x) - 32.0f) + abs(abs(_sphere.Center.y) - 32.0f);
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
				m_moveBlock[3] = true;
			}
			
		}
		_intersectNum++;
		_absDelta[3] = abs(abs(_sphere.Center.x) - 32.0f) + abs(abs(_sphere.Center.y) - 32.0f);
	}
	if (_intersectVector[0])
	{
		_sideAngle = 0;
		if ((_position.first < _bPos.first + _bSize.first - 3.5f) && (_position.first > _bPos.first - _bSize.first + 3.5f))
		{
			
			if ((_bRad == 0) || (_bRad == float(M_PI) * 2.0f) || (_bRad == float(M_PI)))
			{
				m_moveBlock[0] = true;
			}
		}
		_intersectNum++;
		_absDelta[0] = abs(abs(_sphere.Center.x) - 32.0f) + abs(abs(_sphere.Center.y) - 32.0f);
	}
	if (_intersectVector[2])
	{
		_sideAngle = float(M_PI);
		if ((_position.first < _bPos.first + _bSize.first)  && (_position.first > _bPos.first - _bSize.first))
		{
			if ((_bRad == 0) || (_bRad == float(M_PI) * 2.0f) || (_bRad == float(M_PI)))
			{
				m_moveBlock[2] = true;
			}
		}
		_intersectNum++;
		_absDelta[2] = abs(abs(_sphere.Center.x) - 32.0f) + abs(abs(_sphere.Center.y) - 32.0f);
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
		}
			switch (m_direction)
			{
			case Right:
				
					
				if (_sideAngle == 0)
				{
					if ((_sphere.Center.y - 16.0f) < 16.0f)
					{
						_dY = 16.0f - (_sphere.Center.y - 16.0f);
						_dX = _dY * sin(_bRad);
						_dY *= cos(_bRad);
					}
				}
				if (_sideAngle == float(M_PI))
				{
					if ((_sphere.Center.y + 16.0f) > -16.0f)
					{
						_dY = -(16.0f - abs(_sphere.Center.y + 16.0f));
						_dX = _dY * sin(_bRad);
						_dY *= cos(_bRad);
					}
				}
				if (_sideAngle == float(M_PI) * 0.5f)
				{
					if ((_sphere.Center.x + 16.0f) > -16.0f)
					{
						_dX = -(16.0f - abs(_sphere.Center.x + 16.0f));
						_dY = -_dX * sin(_bRad);
						_dX *= cos(_bRad);
					}
				}
				if (_sideAngle == float(M_PI) * 1.5f)
				{
					if ((_sphere.Center.x - 16.0f) < 16.0f)
					{
						_dX = (16.0f - abs(_sphere.Center.x - 16.0f));
						_dY = -_dX * sin(_bRad);
						_dX *= cos(_bRad);
					}
				}
				break;
			case Left:
				
				if (_sideAngle == 0)
				{
					if ((_sphere.Center.y - 16.0f) < 16.0f)
					{
						_dY = 16.0f - (_sphere.Center.y - 16.0f);
						_dX = _dY * sin(_bRad);
						_dY *= cos(_bRad);
					}
				}
				if (_sideAngle == float(M_PI))
				{
					if ((_sphere.Center.y + 16.0f) > -16.0f)
					{
						_dY = -(16.0f - abs(_sphere.Center.y + 16.0f));
						_dX = _dY * sin(_bRad);
						_dY *= cos(_bRad);
					}
				}
				if (_sideAngle == float(M_PI) * 0.5f)
				{
					if ((_sphere.Center.x + 16.0f) > -16.0f)
					{
						_dX = -(16.0f - abs(_sphere.Center.x + 16.0f));
						_dY = -_dX * sin(_bRad);
						_dX *= cos(_bRad);
					}
				}
				if (_sideAngle == float(M_PI) * 1.5f)
				{
					if ((_sphere.Center.x - 16.0f) < 16.0f)
					{
						_dX = (16.0f - abs(_sphere.Center.x - 16.0f));
						_dY = -_dX * sin(_bRad);
						_dX *= cos(_bRad);
					}
				}
				break;
			}

			if (_sideAngle == 0)
			{
				if ((_sphere.Center.y - 16.0f) < 16.0f)
				{
					_dY = 16.0f - (_sphere.Center.y - 16.0f);
					_dX = _dY * sin(_bRad);
					_dY *= cos(_bRad);
				}
			}
			if (_sideAngle == float(M_PI))
			{
				if ((_sphere.Center.y + 16.0f) > -16.0f)
				{
					_dY = -(16.0f - abs(_sphere.Center.y + 16.0f));
					_dX = _dY * sin(_bRad);
					_dY *= cos(_bRad);
				}
			}
			if (_sideAngle == float(M_PI) * 0.5f)
			{
				if ((_sphere.Center.x + 16.0f) > -16.0f)
				{
					_dX = -(16.0f - abs(_sphere.Center.x + 16.0f));
					_dY = -_dX * sin(_bRad);
					_dX *= cos(_bRad);
				}
			}
			if (_sideAngle == float(M_PI) * 1.5f)
			{
				if ((_sphere.Center.x - 16.0f) < 16.0f)
				{
					_dX = (16.0f - abs(_sphere.Center.x - 16.0f));
					_dY = -_dX * sin(_bRad);
					_dX *= cos(_bRad);
				}
			}

		switch (m_direction)
		{
		case Left:
			//_bRad = _bRad + float(M_PI);
			break;
		case Right:
			_bRad = _bRad + float(M_PI);
			break;
		case Stand:
			m_stopFlag = true;
			break;
		};
		if (_bRad <float(M_PI))
		{
			m_groundFlag = true;
		}
		m_collisionData.push_back({ (_bRad),_sideAngle,_bRad,{block.GetGPos()} ,{_dX,_dY} });

	}
	return _result;
}
//
bool Player::CollisionToBlock(std::pair<float, float> b_pos, std::pair<float, float> b_size, float b_rad)
{
	bool _result = false;
	std::pair<float, float> _bPos = b_pos;
	std::pair<float, float> _bSize = b_size;
	std::pair<float, float> _position;
	DirectX::BoundingSphere _sphere;
	DirectX::BoundingBox _box;
	float _sideAngle = 0.0f;
	DirectX::XMFLOAT3 _nearPoint;
	DirectX::XMFLOAT3 _delta;
	float _bRad = b_rad;
	_position.first = m_pos.first - _bPos.first;
	_position.second = m_pos.second - _bPos.second;
	_bPos = { 0,0 };
	std::pair<float, float>__buffer = { _position.first,_position.second };
	_position.first = _position.first * cos(-_bRad) - sin(-_bRad) * _position.second;
	_position.second = __buffer.first * sin(-_bRad) + cos(-_bRad) * __buffer.second;

	_sphere = DirectX::BoundingSphere(Math::Vector3(_position.first, _position.second, 0), 16.0f);
	_box = DirectX::BoundingBox(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(16.0f, 16.0f, 0));
	{
		DirectX::XMFLOAT3 __minPoint
		{ _box.Center.x - _box.Extents.x,_box.Center.y - _box.Extents.y,0
		};
		DirectX::XMFLOAT3  __maxPoint
		{ _box.Center.x + _box.Extents.x,_box.Center.y + _box.Extents.y,0
		};
		float x;
		float y;
		float z = 0;
		float __distanceMin = FLT_MIN;
		float __distanceMax = FLT_MAX;
		for (float i = __minPoint.x; i <= __maxPoint.x; i += 0.1f)
			for (float j = __minPoint.y; j <= __maxPoint.y; j += 0.1f)
			{
				float __dX, __dY;
				__dX = i - _sphere.Center.x;
				__dY = j - _sphere.Center.y;
				if (__distanceMin == FLT_MIN)
				{
					x = i;
					y = j;
					__distanceMin = __dX * __dX + __dY * __dY;
				}
				else
					if (__dX * __dX + __dY * __dY < __distanceMin)
					{
						x = i;
						y = j;
						__distanceMin = __dX * __dX + __dY * __dY;
					}
			}

		_nearPoint = { x,y,z };
	}
	_result = _sphere.Intersects(_box);
	_delta = { _sphere.Center.x - _nearPoint.x,_sphere.Center.y - _nearPoint.y,0 };
	if (_result)
	{
		float __absX = std::abs(_nearPoint.x);
		float __absY = std::abs(_nearPoint.y);
		if (__absX >= _bSize.first / 2 - 0.15f)
		{
			if (_nearPoint.x > 0)
				_sideAngle = float(M_PI) * 1.5f;
			else
				_sideAngle = float(M_PI) / 2.0f;
		}
		else
		{
			if (_nearPoint.y > 0)
				_sideAngle = 0;
			else
				_sideAngle = float(M_PI);
		}
	}

	if (_result)
	{
		m_rad = _bRad + _sideAngle + float(M_PI) * 0.5f;
		if (m_rad >= float(M_PI) * 2.0f)
			m_rad -= float(M_PI) * 2.0f;
		if (m_rad < 0)
			m_rad += float(M_PI) * 2.0f;
		m_sideRad = _sideAngle;
	}
	else
	{
		m_sideRad = -1;
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

KdTexture* Player::GetTexture()
{
	return m_texture;
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
void Player::SetScroll(std::pair<int, int>* scroll)
{
	m_scroll = scroll;
}

std::pair<float, float> Player::GetGPos()
{
	return m_gPos;
}
