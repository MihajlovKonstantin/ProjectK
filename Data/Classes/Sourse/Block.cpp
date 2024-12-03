#include "Pch.h"
#include "Data/Classes/Header/Block.h"


void Block::SetDeleteState(bool state)
{
	m_deleteState = state;
}

bool Block::GetDeleteState()
{
	return m_deleteState;
}

void Block::SetPos(float xPos, float yPos)
{
	m_globalPos.first = xPos;
	m_globalPos.second = yPos;
	m_localPos.first = m_globalPos.first;
	m_localPos.second = m_globalPos.second;
	
}
void Block::Update()
{
	m_mTrans = Math::Matrix::CreateTranslation(m_localPos.first, m_localPos.second, 0);
	m_mRotation = Math::Matrix::CreateRotationZ(0);
	m_matrix =  m_mRotation*m_mTrans;
	m_rectangle = Math::Rectangle{ 0,0,long(m_size.first),long(m_size.second) };
}
void Block::SetSize(float width, float height)
{
	m_size.first = width;
	m_size.second = height;
	m_radius = width / 2;
}

void Block::SetTexture(KdTexture* texture)
{
	m_texture = texture;
}

void Block::SetSpeed(std::pair<float, float> speed)
{
	m_speed = speed;
}

void Block::SetMoveBorder(std::array<std::pair<float, float>, 2> moveBorder)
{
	m_moveBorder = moveBorder;
}
void Block::SetMoveBorder(std::array<float, 2> moveBorderDelta)
{
	m_moveBorder[0] = { moveBorderDelta[0],-moveBorderDelta[0] };
	m_moveBorder[1] = { moveBorderDelta[1], -moveBorderDelta[1] };
}

KdTexture* Block::GetTexture()
{
	return m_texture;
}

float Block::GetXPos()
{
	return m_localPos.first;
}

float Block::GetYPos()
{
	return m_localPos.second;
}

std::pair<float, float> Block::GetSize()
{
	return m_size;
}

void Block::SetBackStage(bool backStage)
{
	m_backStage = backStage;
}

bool Block::GetBackStage()
{
	return m_backStage;
}
std::pair<float, float> Block::GetGPos()
{
	return m_globalPos;
}
Math::Matrix Block::GetMatrix()
{
	return m_matrix;
}
Math::Rectangle Block::GetRectangle()
{
	return m_rectangle;
}
void Block::SetGlobalPos()
{
	m_globalPos.first = m_localPos.first;
	m_globalPos.second = m_localPos.second;
}

void Block::SetRadian(float radian)
{
	m_rad = radian;
}

float Block::GetRad()
{
	return m_rad;
}


Block::Block(float x, float y, float width, float height, KdTexture* texture, bool backStage, float radian)
{
	SetPos(x, y);
	SetSize(width, height);
	SetGlobalPos();
	SetTexture(texture);
	SetBackStage(backStage);
	SetRadian(radian);
}
