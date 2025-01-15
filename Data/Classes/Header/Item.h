#pragma once
#include"Pch.h"
class Item
{
private:
	std::pair<float, float> m_pos;
	std::pair<float, float> m_gPos;
	std::pair<float, float> m_scroll;
	KdTexture* m_texture;
	Math::Matrix m_tranMat;
	Math::Matrix m_matrix;
	int m_index;
	bool m_dirty = false;
	bool m_destruct = false;
	Math::Rectangle m_rectangle;
public:
	Item(std::pair<float, float> pos, KdTexture* texture, int index);
	Item();
	bool IsDestruct();
	void Destruct();
	void Update(std::pair<float,float> scroll);
	KdTexture* GetTexture();
	Math::Matrix GetMatrix();
	Math::Rectangle GetRect();
	int GetIndex();
	std::pair<float, float> GetPos();
};

