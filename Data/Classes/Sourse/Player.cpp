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
	float _delta = float(M_PI) / 6.0f;
	if((radian<_delta)||((radian>	(float(M_PI) -_delta)	)&&(radian<float(M_PI) +_delta)	)||(radian> float(M_PI) *2.0f-_delta))
		_result = true;
	return _result;
}
void Player::Update()
{
	m_stopFlag = false;
	m_scale = { 1,1 };
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
					if ((m_collisionData[i].pos.first < _comparePos.first)|| (m_collisionData[i].collisionValue > m_collisionData[index].collisionValue))
					{
						index = i;
						_comparePos = m_collisionData[i].pos;
					}
					break;
				case Right:
					if ((m_collisionData[i].pos.first > _comparePos.first)||(m_collisionData[i].collisionValue > m_collisionData[index].collisionValue))
					{
						index = i;
						_comparePos = m_collisionData[i].pos;
					}
					break;
				}
			}
			for (int i = 0; i < m_collisionData.size(); i++)
			{
				if (IsPossibleAngle(m_collisionData[i].rad))
				{
					if (index == i)
					{
						m_stopFlag = false;
					}
				}
			}

		}
		m_rad = m_collisionData[index].rad;
		if (IsPossibleAngle(m_rad))
		{
			m_groundFlag = true;
		}

		m_sideRad = m_collisionData[index].sideRad;
		m_currentCollisionValue = m_collisionData[index].collisionValue;
		if (IsPossibleAngle(fmod(m_collisionData[index].rad, float(M_PI) * 2.0f)))
		{

			m_pos.first += m_collisionData[index].dPos.first;
			m_pos.second += m_collisionData[index].dPos.second;
		}
		else
		{
			std::pair<float, float> __futurePos = m_pos;
			__futurePos.first += m_currentSpeed.first;
			__futurePos.second += m_currentSpeed.second;
			m_pos.first += m_collisionData[index].dPos.first;
			m_pos.second += m_collisionData[index].dPos.second;
			//m_stopFlag = true;
		}
		if (m_rad < 0)
		{
			m_rad += 2.0f * float(M_PI);
		}
		m_rad = fmod(m_rad, 2.0f * float(M_PI));
	}
	if (m_groundFlag)
	{
		m_speed.second = 0;

	}
	else
	{

		m_rad = 0;
		m_speed.second = m_speedBase.second;
		m_sideRad = -1.0f;
		m_currentCollisionValue = -1.0f;
	}
	float _drawRad = m_rad;


	if (m_rad > float(M_PI))
	{
		m_scale.first *= -1;
	}
	if (m_sideRad != -1)
	{
		switch (m_direction)
		{
		case Left:
			_drawRad = fmod(_drawRad + 0.0001, 1.0f * float(M_PI));
			if (_drawRad >= float(M_PI) * 0.5f)
			{
				_drawRad += float(M_PI) * 1.0f;
			}
			m_mRotation = Math::Matrix::CreateRotationZ(_drawRad + float(M_PI) * 0.5f);
			m_mScale = Math::Matrix::CreateScale(-1, 1, 1);
			break;
		case Right:
			_drawRad = fmod(_drawRad + 0.0001, 1.0f * float(M_PI));
			if (_drawRad >= float(M_PI) * 0.5f)
			{
				_drawRad += float(M_PI) * 1.0f;
			}
			m_mRotation = Math::Matrix::CreateRotationZ(_drawRad + float(M_PI) * 1.5f);
			m_mScale = Math::Matrix::CreateScale(1, 1, 1);
			break;
		}

	}
	else
	{
		switch (m_direction)
		{
		case Right:
			m_mRotation = Math::Matrix::CreateRotationZ(-float(M_PI) / 2.0f);
			m_mScale = Math::Matrix::CreateScale(1, 1, 1);
			break;
		case Left:
			m_mRotation = Math::Matrix::CreateRotationZ(float(M_PI) / 2.0f);
			m_mScale = Math::Matrix::CreateScale(-1, 1, 1);
		}

	}

	switch (m_direction)
	{
	case Stand:
		m_stopFlag = true;
		m_currentSpeed.second = m_speed.second;
		break;
	}
	if (m_rad + 0.0001 > 2.0f * float(M_PI))
	{
		m_rad = fmod(m_rad + 0.0001, 2.0f * float(M_PI));
	}
	if ((m_rad + 0.0001) >= float(M_PI) && (m_rad<float(M_PI)))
	{
		m_rad = float(M_PI);
	}


	if(!m_stopFlag)
	{
		float _moveRad = fmod(m_rad + 0.0001, float(M_PI));
		switch (m_direction)
		{
		case Right:
			if (m_groundFlag == true)
			{
				m_currentSpeed.first = m_speed.first * abs(cos(_moveRad)) + m_speed.second * sin(_moveRad);
			}
			else
			{
				m_currentSpeed.first = m_speed.first * cos(_moveRad) - m_speed.second * sin(_moveRad);
			}
			m_currentSpeed.second = m_speed.first * sin(m_rad) + m_speed.second * cos(m_rad);
			
			break;
		case Left:
			if (m_groundFlag == true)
			{
				m_currentSpeed.first = m_speed.first * (-abs(cos(_moveRad))) + m_speed.second * sin(_moveRad);
			}
			else
			{
				m_currentSpeed.first = m_speed.first * cos(_moveRad + float(M_PI)) - m_speed.second * sin(_moveRad + float(M_PI));
			}
			
			m_currentSpeed.second = m_speed.first * sin(m_rad) + m_speed.second * cos(m_rad);
			break;
		}
	}
	else
	{
		m_currentSpeed.first = 0;
	}
	
	m_pos.first += m_currentSpeed.first;
	m_pos.second += m_currentSpeed.second;
	m_matrix = m_mScale * m_mRotation * m_mTrans;
	m_mTrans = Math::Matrix::CreateTranslation(m_pos.first, m_pos.second, 0);
	switch(m_direction)
	{
	case Left:
		break;
	case Right:
		if (m_sideRad != -1)
		{
			//m_rad -= M_PI;
			//if (m_rad < 0)
				//m_rad += M_PI * 2;
		}
		break;
	}
}
/*
void Player::Update()
{
	m_stopFlag = false;
	bool _movePossible = true;
	m_scale = { 1,1 };
	int index;
	if (!m_collisionData.empty())
	{
		std::pair<float, float> _comparePos = { m_collisionData[0].pos };
		index = 0;
		if (m_collisionData.size() > 1)
		{
			_movePossible = false;
			for (int i = 1; i < m_collisionData.size(); i++)
			{
				switch (m_direction)
				{
				case Left:
					if (m_collisionData[i].pos.first < _comparePos.first)
					{
						index = i;
						_comparePos = m_collisionData[i].pos;
					}
					break;
				case Right:
					if (m_collisionData[i].pos.first > _comparePos.first)
					{
						index = i;
						_comparePos = m_collisionData[i].pos;
					}
					break;
				}
			}
			for (int i = 0; i < m_collisionData.size(); i++)
			{
				if (IsPossibleAngle(m_collisionData[i].rad))
				{
					if (index == i)
					{
						m_stopFlag = false;
					}
				}
			}
			
		}
		m_rad = m_collisionData[index].rad;
		if (IsPossibleAngle(m_rad))
		{
			m_groundFlag = true;
		}
		
		m_sideRad = m_collisionData[index].sideRad;
		m_currentCollisionValue = m_collisionData[index].collisionValue;
		if (IsPossibleAngle(fmod(m_collisionData[index].rad,float(M_PI)*2.0f)))
		{
			
			m_pos.first += m_collisionData[index].dPos.first;
			m_pos.second += m_collisionData[index].dPos.second;
		}
		else
		{
			std::pair<float, float> __futurePos = m_pos;
			__futurePos.first += m_currentSpeed.first;
			__futurePos.second += m_currentSpeed.second;
			m_pos.first += m_collisionData[index].dPos.first;
			m_pos.second += m_collisionData[index].dPos.second;
			//m_stopFlag = true;
		}
		if (m_rad < 0)
		{
			m_rad += 2.0f* float(M_PI);
		}
		m_rad = fmod(m_rad, 2.0f * float(M_PI));
	}
	if (m_groundFlag)
	{
		m_speed.second = 0;

	}
	else
	{
		
		m_rad = 0;
		m_speed.second = m_speedBase.second;
		m_sideRad = -1.0f;
		m_currentCollisionValue = -1.0f;
	}
	float _drawRad = m_rad;
	
	
	if(m_rad> float(M_PI))
	{
		m_scale.first *= -1;
	}
	if (m_sideRad != -1)
	{
		switch (m_direction)
		{
		case Left:
			_drawRad = fmod(_drawRad+0.0001, 1.0f * float(M_PI));
			if (_drawRad >= float(M_PI) * 0.5f)
			{
				_drawRad += float(M_PI) * 1.0f;
			}
			m_mRotation = Math::Matrix::CreateRotationZ(_drawRad+ float(M_PI) *0.5f);
			m_mScale = Math::Matrix::CreateScale(-1, 1, 1);
			break;
		case Right:
			_drawRad = fmod(_drawRad + 0.0001, 1.0f * float(M_PI));
			if (_drawRad >= float(M_PI) * 0.5f)
			{
				_drawRad += float(M_PI) * 1.0f;
			}
			//_drawRad = fmod(_drawRad + float(M_PI) * 1.5f, float(M_PI)*2.0f);
			m_mRotation = Math::Matrix::CreateRotationZ(_drawRad);
			m_mScale = Math::Matrix::CreateScale(1, 1, 1);
			break;
		}
		
	}
	else
	{
		switch(m_direction)
		{
		case Right:
			m_mRotation = Math::Matrix::CreateRotationZ(-float(M_PI) / 2.0f);
			m_mScale = Math::Matrix::CreateScale(1, 1, 1);
			break;
		case Left:
			m_mRotation = Math::Matrix::CreateRotationZ(float(M_PI) / 2.0f);
			m_mScale = Math::Matrix::CreateScale(-1, 1, 1);
		}
		
	}
	
	switch (m_direction)
	{
	case Left:
			m_scale.first = -1;
		break;
	case Right:
			m_scale.first = 1;
		break;
		case Stand:
			m_stopFlag = true;
			m_currentSpeed.second = m_speed.second;
			break;
	}
	if (m_rad > 2.0f * float(M_PI))
	{
		m_rad = fmod(m_rad, 2.0f * float(M_PI));
	}
	/*
	if (_movePossible)
	{
		m_speed.first = m_speedBase.first;

	}
	else
	{
		m_speed.first = 0;
	}
	
	if(!m_stopFlag)
	{
		m_currentSpeed.first = m_scale.first * abs(m_speed.first * cos(m_rad) - m_speed.second * sin(m_rad));
	}
	else
	{
		m_currentSpeed.first = 0;
	}
	switch (m_direction)
	{
	case Right:
		m_currentSpeed.second = m_speed.first * sin(m_rad) + m_speed.second * cos(m_rad);
		break;
	case Left:
		m_currentSpeed.second = m_speed.first * sin(-m_rad) + m_speed.second * cos(-m_rad);
		break;
	}
	m_pos.first += m_currentSpeed.first;
	m_pos.second += m_currentSpeed.second;
	m_matrix = m_mScale * m_mRotation * m_mTrans;
	m_mTrans = Math::Matrix::CreateTranslation(m_pos.first, m_pos.second, 0);
	switch(m_direction)
	{
	case Left:
		break;
	case Right:
		if (m_sideRad != -1)
		{
			//m_rad -= M_PI;
			//if (m_rad < 0)
				//m_rad += M_PI * 2;
		}
		break;
	}
}
*/
bool Player::CollisionToBlock(Block block)
{
	bool _result = false;
	std::pair<float, float> _bPos = block.GetGPos();
	std::pair<float, float> _bSize = block.GetSize();
	std::pair<float, float> _position;
	DirectX::BoundingSphere _sphere;
	DirectX::BoundingBox _box;
	float _sideAngle = 0.0f;
	float _dX = 0.0f, _dY = 0.0f;
	float _bRad = block.GetRad();
	_position.first = m_pos.first - _bPos.first;
	_position.second = m_pos.second - _bPos.second;
	_bPos = { 0,0 };
	std::pair<float, float>__buffer = { _position.first,_position.second };
	_position.first = _position.first * cos(_bRad) - sin(_bRad) * _position.second;
	_position.second = __buffer.first * sin(_bRad) + cos(_bRad) * __buffer.second;

	_sphere = DirectX::BoundingSphere(Math::Vector3(_position.first, _position.second, 0), 16.0f);
	_box = DirectX::BoundingBox(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(_bSize.first / 2.0f, _bSize.second / 2.0f, 0));
	std::array<DirectX::XMVECTOR, 4> _bOriginVector;
	std::array<DirectX::XMVECTOR, 4> _bNorVector;
	std::array<bool, 4> _intersectVector;
	std::array< float, 4> _absDelta;
	_bOriginVector[0] = { -_bSize.first / 2.0f,_bSize.second / 2.0f,0 };
	_bOriginVector[1] = { -_bSize.first/2.0f,_bSize.second / 2.0f,0 };
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
		_intersectNum++;
		_absDelta[1] = abs(abs(_sphere.Center.x) - 32.0f)+abs(abs(_sphere.Center.y)-32.0f);
	}

	if (_intersectVector[3])
	{
		_sideAngle = float(M_PI) * 1.5f;
		_intersectNum++;
		_absDelta[3] = abs(abs(_sphere.Center.x) - 32.0f) + abs(abs(_sphere.Center.y) - 32.0f);
	}
	if (_intersectVector[0])
	{
		_sideAngle = 0;
		_intersectNum++;
		_absDelta[0] = abs(abs(_sphere.Center.x) - 32.0f) + abs(abs(_sphere.Center.y) - 32.0f);
	}
	if (_intersectVector[2])
	{
		_sideAngle = float(M_PI);
		_intersectNum++;
		_absDelta[2] = abs(abs(_sphere.Center.x) - 32.0f) + abs(abs(_sphere.Center.y) - 32.0f);
	}
	if (_result)
	{
		if (_intersectNum > 1)
		{
			float _left;
			float _right;
			switch (m_direction)
			{
			case Right:
				for (int i = 0; i < 4; i++)
					/*
					if (i > 0)
					{
						
						if (_intersectVector[i] && _intersectVector[i-1])
						{
							_left = (i) * float(M_PI) * 0.5f - _bRad;
							if (IsPossibleAngle(_left)&&_absDelta[i]<_absDelta[i-1])
							{
								_sideAngle = (i) * float(M_PI) * 0.5f;
							}
							else if (IsPossibleAngle((i) * float(M_PI) * 0.5f - _bRad))
							{
								_sideAngle = (i-1) * float(M_PI) * 0.5f;
							}
						}
					}
					else
						if (_intersectVector[0] && _intersectVector[3])
						{
							_left = 0 * float(M_PI) * 0.5f - _bRad;
							if (IsPossibleAngle(3 * float(M_PI) * 0.5f - _bRad))
							{
								_sideAngle = 3 * float(M_PI) * 0.5f;
							} else
							if (IsPossibleAngle(_left) && _absDelta[0] < _absDelta[3])
							{
								_sideAngle = 0 * float(M_PI) * 0.5f;
							}
						}
						*/
					if (i > 0)
					{

						if (_intersectVector[i] && _intersectVector[i - 1])
						{
							_left = (i) * float(M_PI) * 0.5f - _bRad;
							if (IsPossibleAngle(_left) && _absDelta[i] < _absDelta[i - 1])
							{
								_sideAngle = (i) * float(M_PI) * 0.5f;
							}
							else if (IsPossibleAngle((i) * float(M_PI) * 0.5f - _bRad))
							{
								_sideAngle = (i - 1) * float(M_PI) * 0.5f;
							}
						}
					}
					else
						if (_intersectVector[0] && _intersectVector[3])
						{
							_left = 0 * float(M_PI) * 0.5f - _bRad;
							if (IsPossibleAngle(3 * float(M_PI) * 0.5f - _bRad))
							{
								_sideAngle = 3 * float(M_PI) * 0.5f;
							}
							else
								if (IsPossibleAngle(_left) && _absDelta[0] < _absDelta[3])
								{
									_sideAngle = 0 * float(M_PI) * 0.5f;
								}
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
				break;
			case Left:
				for (int i = 0; i < 4; i++)
					if (i < 3)
					{

						if (_intersectVector[i + 1] && _intersectVector[i])
						{
							_left = -(i + 1) * float(M_PI) * 0.5f - _bRad;
							if (IsPossibleAngle(_left) && _absDelta[i + 1] < _absDelta[i])
							{
								_sideAngle = (i + 1) * float(M_PI) * 0.5f;
							}
							else if (IsPossibleAngle(-(i) * float(M_PI) * 0.5f - _bRad))
							{
								_sideAngle = i * float(M_PI) * 0.5f;
							}
							else
							{
								//_sideAngle = i + 1 * float(M_PI) * 0.5f;
							}
						}
					}
					else
						if (_intersectVector[0] && _intersectVector[3])
						{
							_left = 0 * float(M_PI) * 0.5f - _bRad;
							if (IsPossibleAngle(_left) && _absDelta[0] < _absDelta[3])
							{
								_sideAngle = 0 * float(M_PI) * 0.5f;
							}
							else if (IsPossibleAngle(3 * float(M_PI) * 0.5f - _bRad))
							{
								_sideAngle = i * float(M_PI) * 0.5f;
							}
							else
							{
								//_sideAngle = 0 * float(M_PI) * 0.5f;
							}
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
				break;
			}

		}


		switch (m_direction)
		{
		case Left:
			_bRad = _bRad + float(M_PI);
			break;
		case Right:
			_bRad = _bRad + float(M_PI);
			break;
		case Stand:
			m_stopFlag = true;
			break;
		};
		m_collisionData.push_back({ (_bRad + _sideAngle),_sideAngle,_bRad,{block.GetGPos()} ,{_dX,_dY} });

	}
	return _result;
}
/*
bool Player::CollisionToBlock(Block block)
{
	bool _result = false;
	std::pair<float, float> _bPos = block.GetGPos();
	std::pair<float, float> _bSize = block.GetSize();
	std::pair<float, float> _position;
	DirectX::BoundingSphere _sphere;
	DirectX::BoundingBox _box;
	float _sideAngle = 0.0f;
	float _dX=0.0f, _dY=0.0f;
	float _bRad = block.GetRad();
	_position.first = m_pos.first - _bPos.first;
	_position.second = m_pos.second - _bPos.second;
	_bPos = { 0,0 };
	std::pair<float, float>__buffer = { _position.first,_position.second };
	_position.first = _position.first * cos(_bRad) - sin(_bRad) * _position.second;
	_position.second = __buffer.first * sin(_bRad) + cos(_bRad) * __buffer.second;
	
	_sphere = DirectX::BoundingSphere(Math::Vector3(_position.first, _position.second, 0), 16.0f);
	_box = DirectX::BoundingBox(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(_bSize.first/2.0f, _bSize.second/2.0f, 0));
	std::array<DirectX::XMVECTOR,4> _bOriginVector;
	std::array<DirectX::XMVECTOR, 4> _bNorVector;
	std::array<bool, 4> _intersectVector;
	_bOriginVector[0] = { -_bSize.first/2.0f,_bSize.second / 2.0f,0 };
	_bOriginVector[1] = { -_bSize.first,_bSize.second / 2.0f,0 };
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
		if (_distanceBuf < _distance&& _intersectVector[i])
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
		_intersectNum++;
	}
	
	if (_intersectVector[3])
	{
		_sideAngle = float(M_PI) * 1.5f;
		_intersectNum++;
	}
	if (_intersectVector[0])
	{
		_sideAngle = 0;
		_intersectNum++;
	}
	if (_intersectVector[2])
	{
		_sideAngle = float(M_PI);
		_intersectNum++;
	}
	if (_result)
	{
		if (_intersectNum > 1)
		{
			float _left;
			float _right;
			switch (m_direction)
			{
			case Right:
				for (int i = 3; i > 0; i--)
				{


					if (_intersectVector[i] && _intersectVector[i - 1])
					{
						_right = (i - 1) * float(M_PI) * 0.5f + _bRad;
						if (IsPossibleAngle(_right))
						{
							_sideAngle = i - 1 * float(M_PI) * 0.5f;
						}
						else
							if (IsPossibleAngle((i) * float(M_PI) * 0.5f + _bRad))
							{
								_sideAngle = i * float(M_PI) * 0.5f;
							}
					}

				}
				{
					if (_intersectVector[0] && _intersectVector[3])
					{
						_right = 3 * float(M_PI) * 0.5f + _bRad;
						if (IsPossibleAngle(_right))
						{
							_sideAngle = 3 * float(M_PI) * 0.5f;
							}
							else if (IsPossibleAngle(0 * float(M_PI) * 0.5f + _bRad))
							{
								_sideAngle = 0 * float(M_PI) * 0.5f;
							}
							else
							{
								//_sideAngle = 3 * float(M_PI) * 0.5f;
								//_sideAngle = 3 * float(M_PI) * 0.5f;
							}
						}
					}
				_bRad += float( M_PI);
				//_bRad = fmod(_bRad, 2.0f * float(M_PI));
				if (_sideAngle == float(M_PI))
				{
					if ((_sphere.Center.y - 16.0f) < 16.0f)
					{
						_dY = 16.0f - (_sphere.Center.y - 16.0f);
						_dX = _dY * sin(_bRad);
						_dY *= cos(_bRad);
					}
				}
				if (_sideAngle == 0)
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
				if (_sideAngle == float(M_PI) * 1.5f   )
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
				for (int i = 0; i < 4; i++)
					if (i < 3)
					{
						if (_intersectVector[i + 1] && _intersectVector[i])
						{
							_left = -(i + 1) * float(M_PI) * 0.5f - _bRad;
							if (IsPossibleAngle(_left))
							{
								_sideAngle = i + 1 * float(M_PI) * 0.5f;
							}
							else if (IsPossibleAngle(-(i) * float(M_PI) * 0.5f - _bRad))
							{
								_sideAngle = i * float(M_PI) * 0.5f;
							}
							else
							{
								//_sideAngle = i + 1 * float(M_PI) * 0.5f;
							}
						}
					}
						else
							if (_intersectVector[0] && _intersectVector[3])
							{
								_left = 0 * float(M_PI) * 0.5f - _bRad;
								if (IsPossibleAngle(_left))
								{
									_sideAngle = 0 * float(M_PI) * 0.5f;
								}
								else if(IsPossibleAngle( 3 * float(M_PI) * 0.5f - _bRad))
								{
									_sideAngle = i * float(M_PI) * 0.5f;
								}
								else
								{
									//_sideAngle = 0 * float(M_PI) * 0.5f;
								}
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
				break;
			}

		}
		
		
		switch (m_direction)
		{
		case Left:
			_bRad = _bRad + float(M_PI);
			break;
		case Stand:
			m_stopFlag = true;
			break;
		};
		m_collisionData.push_back({ (_bRad + _sideAngle),_sideAngle,_bRad,{block.GetGPos()} ,{_dX,_dY} });
		
	}
	return _result;
}
*/
/*
bool Player::CollisionToBlock(Block block)
{
	bool _result = false;
	std::pair<float, float> _bPos = block.GetGPos();
	std::pair<float, float> _bSize = block.GetSize();
	std::pair<float, float> _position;
	DirectX::BoundingBox _pBox;
	DirectX::BoundingBox _box;
	DirectX::BoundingBox _boxSecond;
	float _sideAngle = 0.0f;
	DirectX::XMFLOAT3 _nearPoint;
	DirectX::XMFLOAT3 _delta;
	float _bRad = block.GetRad();
	_position.first = m_pos.first - _bPos.first;
	_position.second = m_pos.second - _bPos.second;
	_bPos = { 0,0 };
	std::pair<float, float>__buffer = { _position.first,_position.second };
	_position.first = _position.first * cos(-_bRad) - sin(-_bRad) * _position.second;
	_position.second = __buffer.first * sin(-_bRad) + cos(-_bRad) * __buffer.second;

	_pBox = DirectX::BoundingBox(DirectX::XMFLOAT3(m_pos.first, m_pos.second, 0), DirectX::XMFLOAT3(_bSize.first / 4.0f, _bSize.second / 4.0f, 0));
	_box = DirectX::BoundingBox(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(_bSize.first / 4.0f, _bSize.second / 4.0f, 0));
	if (abs(_pBox.Center.x - _box.Center.x) <= abs(_pBox.Center.y - _box.Center.y))
	{
		if (_pBox.Center.x - _box.Center.x <= -16.0f)
		{
			_nearPoint = { -16.0f,0,0 };
		}
		else
		{
			_nearPoint = { 16.0f,0,0 };
		}
	}
	else
	{
		if (_pBox.Center.y - _box.Center.y <= -16.0f)
		{
			_nearPoint = { 0. - 16.0f,0,0 };
		}
		else
		{
			_nearPoint = { 0,16.0f,0 };
		}
	}
	_result = _pBox.Intersects(_box);
	if (!_result)
	{
		//_result = _pBox.Intersects(_boxSecond);
	}
	_delta = { _pBox.Center.x - _nearPoint.x,_pBox.Center.y - _nearPoint.y,0 };
	if (_result)
	{
		float __absX = std::abs(_nearPoint.x);
		float __absY = std::abs(_nearPoint.y);
		if (__absX >= _bSize.first / 2 - 0.15f)
		{
			if (_nearPoint.x > 0)
				_sideAngle = 0;
			else
				_sideAngle = M_PI;
		}
		else
		{
			if (_nearPoint.y > 0)
				_sideAngle = M_PI * 1.5f;
				
			else
				_sideAngle = M_PI / 2.0f;
				
		}
	}

	if (_result)
	{
		if (m_currentCollisionValue != _bRad);
		{
			if (m_sideRad == -1.0f)
			{
				m_rad = _bRad + _sideAngle + M_PI * 0.5f;
				if (m_rad >= M_PI * 2.0f)
					m_rad -= M_PI * 2.0f;
				if (m_rad < 0)
					m_rad += M_PI * 2.0f;
				m_sideRad = _sideAngle;
				m_currentCollisionValue = _bRad;
			}
		}
	}


	return _result;
}
*/
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

void Player::Move()
{
	m_pos.first = m_pos.first + m_speed.first * cos(m_rad);
	m_pos.second = m_pos.second + m_speed.second * sin(m_rad);
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
