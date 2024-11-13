#pragma once
#include "Pch.h"
class Stage
{
protected:
	KdTexture* m_backRT;
	KdTexture* m_middleRT;
public:
	void SetRT(KdTexture* backRT, KdTexture* middleRT);
	KdTexture* GetBackRT();
	KdTexture* GetMiddleRT();
	void Draw();
	void Init();
	void Update();
	void Release();
};

