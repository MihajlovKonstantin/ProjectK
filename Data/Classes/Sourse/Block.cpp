#include "Pch.h"
#include "Data/Classes/Header/Block.h"


void Block::SetLocalPos(float xPos, float yPos)
{
	m_localPos.first = xPos;
	m_localPos.second = yPos;
}
void Block::Update()
{
	FoundCE();
	m_mTrans = Math::Matrix::CreateTranslation(m_globalPos.first, m_globalPos.second, 0);
	m_rectangle = Math::Rectangle{ 0,0,long(m_size.first),long(m_size.second) };
}
void Block::FoundCE()
{
	for (int i = 0; i < 4; i++)
	{
		float _radian = m_tangen + DirectX::XMConvertToRadians(90 * (i + 1));
		m_centerEdge[i] = { m_localPos.first + cos(_radian) * m_radius,m_localPos.second + sin(_radian) * m_radius };
	}
}

void Block::SetSize(float width, float height)
{
	m_size.first = width;
	m_size.second = height;
	m_radiusABS = sqrt((width * width) + (height * height));
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
	return m_mTrans*Math::Matrix::CreateRotationZ(m_angle);
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

void Block::SetTangen(float tangen)
{
	m_tangen = tangen;
	if(tangen==0)
	{
		m_angle = 0;
	}
	else
	{
		m_angle = atan(tangen);
	}
}

float Block::GetTan()
{
	return m_tangen;
}

float Block::GetAngle()
{
	return m_angle;
}

Block::Block(float x, float y, float width, float height, KdTexture* texture, bool backStage,float tangen)
{
	SetLocalPos(x, y);
	SetSize(width, height);
	SetGlobalPos();
	SetTexture(texture);
	SetBackStage(backStage);
	SetTangen(tangen);
}
