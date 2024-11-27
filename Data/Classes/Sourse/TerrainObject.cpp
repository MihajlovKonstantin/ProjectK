#include "Pch.h"

bool TerrainObject::OnCollisionRange(std::pair<float, float> pos)
{
	bool _result = false;
	if ((pos.first >= m_xBorder.first) && (pos.first <= m_xBorder.second))
	{
		if ((pos.second >= m_yBorder.first) && (pos.second <= m_yBorder.second))
		{
			_result = true;
		}
	}
	return _result;
}

void TerrainObject::Replace(Block block)
{
	for (auto _block : m_block)
	{
		auto _data1 = block.GetGPos();
		auto _data2 = _block.GetGPos();
		if (_data1.first == _data2.first)
		{
			if (_data1.second == _data2.second)
			{
				_block.SetDeleteState(true);
			}
		}

	}
}

void TerrainObject::ClearReplace()
{
	auto _it = m_block.begin();
	for (size_t i = 0; i < m_block.size();)
	{

		if (m_block.at(i).GetDeleteState())
		{
			m_block.erase(_it);
			m_dirty - true;
		}
		else
		{
			i++;
			_it++;
		}
	}
}

void TerrainObject::FoundBorder()
{
	auto data1 = m_block[0].GetGPos();
	auto data2 = m_block[m_block.size() - 1].GetGPos();
	if (data1.first > data2.first)
	{
		m_xBorder.first = data2.first-100;
		m_xBorder.second = data1.first + 100;
	}
	else
	{
		m_xBorder.first = data1.first - 100;
		m_xBorder.second = data2.first + 100;
	}
	if (data1.second > data2.second)
	{
		m_yBorder.first = data2.second - 100;
		m_yBorder.second = data1.second + 100;
	}
	else
	{
		m_yBorder.first = data1.second - 100;
		m_yBorder.second = data2.second + 100;
	}
}

void TerrainObject::Update()
{
	if (m_dirty)
	{
		ClearReplace();
		FoundBorder();
	}
	for (int i = 0;i<m_block.size();i++)
	{
		m_block[i].Update();
	}
}

std::vector<Block>* TerrainObject::GetBlocks()
{
	return &m_block;
}

TerrainObject::TerrainObject(std::pair<float, float> pos, int type, std::vector<int> blockType)
{
	m_globalPos = pos;
	m_type = type;
	m_blockType = blockType;
	int j = 0;
	for (auto _block : m_blockType)
	{
		switch (_block)
		{
		case 0:
			break;
		case 1:
			switch (m_type)
			{
			case 0:
				m_block.push_back(Block(m_globalPos.first + j * 32.0f, m_globalPos.second, 32.0f, 32.0f, &m_firstBlockTex, false, 0));
				break;
			case 1:
				m_block.push_back(Block(m_globalPos.first + j * 32.0, m_globalPos.second + j * 32.0f, 32.0f, 32.0f, &m_firstBlockTex, false, 0));
				break;
			case 2:
				m_block.push_back(Block(m_globalPos.first, m_globalPos.second + j * 32.0f, 32.0f, 32.0f, &m_firstBlockTex, false, 0));
				break;
			case 3:
				m_block.push_back(Block(m_globalPos.first - j * 32.0f, m_globalPos.second + j * 32.0f, 32.0f, 32.0f, &m_firstBlockTex, false, 0));
				break;
			case 4:
				m_block.push_back(Block(m_globalPos.first - j * 32.0f, m_globalPos.second, 32.0f, 32.0f, &m_firstBlockTex, false, 0));
				break;
			case 5:
				m_block.push_back(Block(m_globalPos.first - j * 32.0f, m_globalPos.second - j * 32.0f, 32.0f, 32.0f, &m_firstBlockTex, false, 0));
				break;
			case 6:
				m_block.push_back(Block(m_globalPos.first, m_globalPos.second - j * 32.0f, 32.0f, 32.0f, &m_firstBlockTex, false, 0));
				break;
			case 7:
				m_block.push_back(Block(m_globalPos.first + j * 32.0f, m_globalPos.second - j * 32.0f, 32.0f, 32.0f, &m_firstBlockTex, false, 0));
				break;
			case 8:
				m_block.push_back(Block(m_globalPos.first + j * 32.0f, m_globalPos.second, 32.0f, 32.0f, &m_firstBlockTex, false, 0));
				break;
			}
		}
		j++;
	}
}
TerrainObject::TerrainObject(std::pair<float, float> pos, int type, std::vector<int> blockType, std::vector<Block> block)
{
	m_globalPos = pos;
	m_type = type;
	m_block = block;
	m_blockType = blockType;
	FoundBorder();
}

TerrainObject::TerrainObject(const TerrainObject& object)
{

	m_globalPos = object.m_globalPos;
	m_type = object.m_type;
	m_block = object.m_block;
	m_blockType = object.m_blockType;
	FoundBorder();
}

std::vector<int> TerrainObject::GetTypeBlock()
{
	return m_blockType;
}

std::pair<float, float> TerrainObject::GetGPOS()
{
	return m_globalPos;
}

int TerrainObject::GetAngle()
{
	return m_type;
}

