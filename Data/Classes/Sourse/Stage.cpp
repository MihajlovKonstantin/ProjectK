#include "Pch.h"
#include "Data/Classes/Header/Stage.h"

void Stage::SetRT(KdTexture* backRT, KdTexture* middleRT)
{
	m_backRT = backRT;
	m_middleRT = middleRT;
}

KdTexture* Stage::GetBackRT()
{
	return nullptr;
}

KdTexture* Stage::GetMiddleRT()
{
	return nullptr;
}

void Stage::Draw()
{
	m_backRT->ClearRenerTarget(Math::Color(1, 1, 1, 1));
	m_backRT->SetRenderTarget();
	//Back Draw
	{

	}
	m_middleRT->ClearRenerTarget(Math::Color(1, 1, 1, 1));
	m_middleRT->SetRenderTarget();
	//Middle Draw
	{

	}
}

void Stage::Init() //Stage Init Preset

{
}

void Stage::Update()
{
}

void Stage::Release()
{
}
