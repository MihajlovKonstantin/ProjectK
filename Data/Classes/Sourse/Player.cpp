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
	m_mTrans = Math::Matrix::CreateTranslation(m_pos.first, m_pos.second, 0);
	m_mRotation = Math::Matrix::CreateRotationZ(m_rad);
	m_matrix = m_mTrans * m_mRotation;
}

bool Player::CollisionToBlock(Block block)
{
	bool _result = false;
	std::pair<float, float> _bPos = block.GetGPos();
	std::pair<float, float> _bSize = block.GetSize();
	std::pair<float, float> _position;
	std::pair<float, float> _nearPos;
	float _bRad = block.GetRad();
	_position.first = m_pos.first - _bPos.first;
	_position.second = m_pos.second - _bPos.second;
	_bPos = { 0,0 };
	std::pair<float, float>__buffer = { _position.first,_position.second };
	_position.first = _position.first * cos(_bRad) - sin(_bRad) * _position.second;
	_position.second = __buffer.first * sin(_bRad) + cos(_bRad) * __buffer.second;
	if (-(_bSize.first/2) > _position.first)
	{
		_nearPos.first = -(_bSize.first/2);
	}
	else if (_bSize.first/2 < _position.first)
	{
		_nearPos.first = _bSize.first/2;
	}
	else
	{
		_nearPos.first = _position.first;
	}

	if (-(_bSize.second/2) > _position.second)
	{
		_nearPos.second = -(_bSize.second/2);
	}
	else if (_bSize.second/2 < _position.second)
	{
		_nearPos.second = _bSize.second/2;
	}
	else
	{
		_nearPos.second = _position.second;
	}
	if (sqrt(pow(_nearPos.first - _position.first,2) + pow(_nearPos.second - _position.second,2)) <= m_collisionRadius)
	{
		_result = true;
		m_rad = _bRad-3.14/2;
	}
	if (sqrt(pow(_nearPos.first - _position.first, 2) + pow(_nearPos.second - _position.second, 2)) < m_collisionRadius)
	{
		float _delta = m_collisionRadius-sqrt(pow(_nearPos.first - _position.first, 2) + pow(_nearPos.second - _position.second, 2));
		//m_pos.first += (_delta / cos(_bRad));
		//m_pos.second += (_delta / sin(_bRad));

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
