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
	Player::Update();
}


void PC::Stop()
{
	m_speed = { 0,0 };
}
