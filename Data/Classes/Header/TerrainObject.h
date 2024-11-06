#pragma once
#include "Pch.h"
class TerrainObject
{
	std::pair<int, int> m_localPos;
	std::pair<int, int> m_globalPos;
	std::pair<int, int> m_roomIndex;
	std::vector<Block> m_block;
public:
	void CreateRoomBorder(std::pair<int,int> openState);
	void CreateRoomBorder(int dirrection);

};

