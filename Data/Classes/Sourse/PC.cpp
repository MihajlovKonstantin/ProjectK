#include "Pch.h"
#include "Data/Classes/Header/PC.h"

PC::PC(std::pair<float, float> pos, std::pair<float, float>speed, KdTexture* texture)
{
	m_pos = pos;
	m_texture = texture;
	m_speed = speed;
}

std::pair<float, float> PC::GetPos()
{
	return m_pos;
}


void PC::Update()
{
	m_pos.first += m_speed.first;
	m_pos.second += m_speed.second;
	m_mTrans = Math::Matrix::CreateTranslation(m_pos.first, m_pos.second, 0);
	switch (m_direction)
	{
	case Direction::Up:
		break;
	case Direction::Down:
		break;
	case Direction::Left:
		break;
	case Direction::Right:
		break;
	}
}

KdTexture* PC::GetTexture()
{
	return m_texture;
}

Math::Matrix PC::GetMatrix()
{
	return m_mTrans;
}

void PC::Stop()
{
	m_speed = { 0,0 };
}
