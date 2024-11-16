#include "Pch.h"
#include <utility>
#include "Data/Classes/Header/Player.h"

Player::~Player()
{
}

void Player::Update()
{
	m_pos.first += m_speed.first;
	m_pos.second += m_speed.second;
	m_currentSpeed.first = m_speed.first;
	m_currentSpeed.second = m_speed.second;
	float _drawRad = m_rad;
	bool _reverse = false;
	m_mTrans = Math::Matrix::CreateTranslation(m_pos.first, m_pos.second, 0);
	
	while (_drawRad >= M_PI)
	{
		_drawRad -= M_PI;
	}
	if(m_rad>M_PI)
	{
		m_mScale = Math::Matrix::CreateScale(-1, 1, 1);
		_reverse = true;
	}
	else
	{
		m_mScale = Math::Matrix::CreateScale(1, 1, 1);
	}
	if (_drawRad > M_PI / 2.0f)
	{
		_drawRad -= M_PI / 2.0f;
	}
	if (_reverse)
	{
		//_drawRad *= -1;
	}
	if (m_sideRad != -1)
	{
		if ((m_rad < M_PI  || (m_rad > M_PI * 2.0f)))
		{
			if (m_rad > M_PI / 2.0f)
			{
				_drawRad += M_PI / 2.0f;
			}
			m_mRotation = Math::Matrix::CreateRotationZ(_drawRad - M_PI);
		}
		else
		{
			if (m_rad > M_PI * 1.5f)
			{
				m_mRotation = Math::Matrix::CreateRotationZ(_drawRad - M_PI/2.0f);
			}
			else
			{
				m_mRotation = Math::Matrix::CreateRotationZ(_drawRad - M_PI);
			}
		}
	}
	else
	{
		m_mRotation = Math::Matrix::CreateRotationZ(-M_PI / 2.0f);
	}
	m_matrix =  m_mScale*m_mRotation*m_mTrans;
}

bool Player::CollisionToBlock(Block block, float* degree)
{
	bool _result = false;
	std::pair<float, float> _bPos = block.GetGPos();
	std::pair<float, float> _bSize = block.GetSize();
	std::pair<float, float> _position;
	DirectX::BoundingSphere _sphere;
	DirectX::BoundingBox _box;
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
	
	_sphere = DirectX::BoundingSphere(Math::Vector3(_position.first, _position.second, 0), 16.0f);
	_box = DirectX::BoundingBox(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(16.0f, 16.0f, 0));
	{
		DirectX::XMFLOAT3 __minPoint
		{_box.Center.x-_box.Extents.x,_box.Center.y-_box.Extents.y,0
		};
		DirectX::XMFLOAT3  __maxPoint
		{ _box.Center.x + _box.Extents.x,_box.Center.y + _box.Extents.y,0
		};
		float x;
		float y;
		float z = 0;
		float __distanceMin= FLT_MIN;
		float __distanceMax = FLT_MAX;
		for(float i = __minPoint.x;i<=__maxPoint.x;i+=0.1f)
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
				} else
				if (__dX*__dX + __dY*__dY < __distanceMin)
				{
					x = i;
					y = j;
					__distanceMin = __dX * __dX + __dY * __dY;
				}
			}
		
		_nearPoint = { x,y,z };
	}
	_result = _sphere.Intersects(_box);
	_delta = { _sphere.Center.x-_nearPoint.x,_sphere.Center.y - _nearPoint.y,0 };
	if(_result)
	{
		float __absX = std::abs(_nearPoint.x);
		float __absY = std::abs(_nearPoint.y);
		if (__absX >= _bSize.first / 2 - 0.15f)
		{
			if (_nearPoint.x > 0)
				_sideAngle =  M_PI * 1.5f;
			else
				_sideAngle =  M_PI / 2.0f;
		}
		else
		{
			if (_nearPoint.y > 0)
				_sideAngle = 0;
			else
				_sideAngle = M_PI;
		}
	}
	
	if (_result)
	{
		m_rad = _bRad +_sideAngle+M_PI*0.5f;
		if (m_rad >= M_PI * 2.0f)
			m_rad -= M_PI * 2.0f;
		if (m_rad < 0)
			m_rad += M_PI * 2.0f;
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
