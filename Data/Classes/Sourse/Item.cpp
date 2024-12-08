#include "Pch.h"
#include "Data/Classes/Header/Item.h"

Item::Item(std::pair<float, float> pos, KdTexture* texture, int index)
{
	m_pos = pos;
	m_texture = texture;
	m_index = index;
	m_dirty = true;
}

Item::Item()
{
}

bool Item::IsDestruct()
{
	return m_destruct;
}

void Item::Destruct()
{
	m_destruct = true;
}

void Item::Update()
{
	if (m_dirty)
	{
		m_tranMat = Math::Matrix::CreateTranslation(m_pos.first, m_pos.second, 0);
		m_matrix = m_tranMat;
		m_rectangle = Math::Rectangle(0, 0, 32.0f, 32.0f);
		m_dirty = false;
	}
}

KdTexture* Item::GetTexture()
{
	return m_texture;
}

Math::Matrix Item::GetMatrix()
{
	return m_matrix;
}

Math::Rectangle Item::GetRect()
{
	return m_rectangle;
}

int Item::GetIndex()
{
	return m_index;
}

std::pair<float, float> Item::GetPos()
{
	return m_pos;
}
