#include "Data/Classes/Header/TerrainObject.h"

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
 	for (int i = 0;i<m_block.size()&&(!m_block.empty());i++)
	{
 		auto _data1 = block.GetGPos();
		auto _data2 = m_block[i].GetGPos();
		if (_data1.first == _data2.first)
		{
			if (_data1.second == _data2.second)
			{
				m_block[i].SetDeleteState(true);
				m_dirty = true;
			}
		}

	}
}

void TerrainObject::ClearReplace()
{
	auto _it = m_block.begin();
	int j =0;
	for (size_t i = 0; (!m_block.empty())&&(j<m_blockType.size())&&(i<m_block.size());)
	{
		while (j<m_blockType.size())
		{
			if ((m_blockType[j] == 0))
			{
				j++;
			}
			else
			{
				break;
			}
		}
		if (m_block.at(i).GetDeleteState())
		{
			if (!m_block.empty())
			{
				_it = m_block.begin() + i;
			}
			m_block.erase(_it);
			i--;
			if ((j < m_blockType.size()))
			{
				m_blockType[j] = 0;
			}
			m_dirty = true;
		}
		else
		{
			i++;
		}
		j++;
	}
}

void TerrainObject::FoundBorder()
{
	if (!m_block.empty())
	{
		auto data1 = m_block[0].GetGPos();
		auto data2 = m_block[m_block.size() - 1].GetGPos();
		if (data1.first > data2.first)
		{
			m_xBorder.first = data2.first - 100;
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
}

void TerrainObject::Update()
{
	auto _xLock = m_localPos.first;
	auto _yLock = m_localPos.second;
	m_localPos.first = m_globalPos.first - m_scroll->first;
	m_localPos.second = m_globalPos.second - m_scroll->second;
	if ((_xLock != m_localPos.first) || (_yLock != m_localPos.second))
	{
		m_dirty = true;
	}
	ClearReplace();
	if (m_dirty)
	{
		
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

TerrainObject::TerrainObject(std::pair<float, float> pos, int type, std::vector<int> blockType, std::vector<int> blockVar,std::array<std::vector<std::array<KdTexture*, 5>>, 6>* textLib)
{
	m_globalPos = pos;
	m_texture = textLib;
	m_type = type;
	m_blockType = blockType;
	m_blockVar = blockVar;
	KdTexture* _currentTex;
	auto test = *m_texture;
	bool _anglePossible = true;
	int _texIndex;
	switch (m_type)
	{
	case 1:
		_texIndex = 2;
		break;
	case 3:
		_texIndex = 1;
		break;
	case 5:
		_texIndex = 4;
		break;
	case 7:
		_texIndex = 3;
		break;
	default:
		_texIndex = 0;
		break;
	}
	for (int i = 0; i < m_blockType.size(); i++)
	{
		
		switch (m_blockType[i])
		{
		default:
			if (m_blockType[i] != 0)
			{
				_currentTex = test[m_blockType[i]][m_blockVar[i]][_texIndex];
			}
			
			break;
		case BlockEditerSelect::Ladder:
			_anglePossible = false;
			_currentTex = test[m_blockType[i]][m_blockVar[i]][0];
			break;
		}
	}

	for (int j = 0; j < m_blockType.size(); j++)
	{
		if (_anglePossible&&(m_blockType[j] != 0))
		{
			switch (m_type)
			{
			case 0:
				m_block.push_back(Block(m_globalPos.first + (j- 0) * 32.0f, m_globalPos.second, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 1:
				m_block.push_back(Block(m_globalPos.first + (j - 0) * 32.0f, m_globalPos.second + (j- 0) * 32.0f, 32.0f, 32.0f, _currentTex, false, float(M_PI) * 0.25f));
				break;
			case 2:
				m_block.push_back(Block(m_globalPos.first, m_globalPos.second + (j - 0) * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 3:
				m_block.push_back(Block(m_globalPos.first - (j - 0) * 32.0f, m_globalPos.second + (j - 0) * 32.0f, 32.0f, 32.0f, _currentTex, false, float(M_PI) * 0.75f));
				break;
			case 4:
				m_block.push_back(Block(m_globalPos.first - (j - 0) * 32.0f, m_globalPos.second, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 5:
				m_block.push_back(Block(m_globalPos.first - (j - 0) * 32.0f, m_globalPos.second - (j - 0) * 32.0f, 32.0f, 32.0f, _currentTex, false, float(M_PI) * 1.25f));
				break;
			case 6:
				m_block.push_back(Block(m_globalPos.first, m_globalPos.second - (j - 0) * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 7:
				m_block.push_back(Block(m_globalPos.first + (j - 0) * 32.0f, m_globalPos.second - (j - 0) * 32.0f, 32.0f, 32.0f, _currentTex, false, float(M_PI) * 1.75f));
				break;
			case 9:
				m_block.push_back(Block(m_globalPos.first + (j - 0) * 32.0f, m_globalPos.second + (j - 1) * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 11:
				m_block.push_back(Block(m_globalPos.first - (j - 0) * 32.0f, m_globalPos.second + (j - 1) * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 13:
				m_block.push_back(Block(m_globalPos.first - (j - 0) * 32.0f, m_globalPos.second - (j - 1) * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 15:
				m_block.push_back(Block(m_globalPos.first + (j - 0) * 32.0f, m_globalPos.second - (j - 1) * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			}
			switch (m_blockType[j])
			{
			case BlockEditerSelect::Ice:
				m_block[m_block.size() - 1].m_iceBlock = true;
				break;
			case BlockEditerSelect::IceWater:
				m_block[m_block.size() - 1].m_snowBlock = true;
				break;
			case BlockEditerSelect::Ladder:
				m_block[m_block.size() - 1].m_backStage = true;
				m_block[m_block.size() - 1].m_laderBlock = true;
				break;
			case BlockEditerSelect::Lava:
				m_block[m_block.size() - 1].m_lavaBlock = true;
				break;
			}
		}
		else
		{
			if (m_blockType[j] != 0)
			{
				m_type = m_type / 2 * 2;
				switch (m_type)
				{
				case 0:
					m_block.push_back(Block(m_globalPos.first + (j - 0) * 32.0f, m_globalPos.second, 32.0f, 32.0f, _currentTex, false, 0));
					break;
				case 2:
					m_block.push_back(Block(m_globalPos.first, m_globalPos.second + (j - 0) * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
					break;
				case 4:
					m_block.push_back(Block(m_globalPos.first - (j - 0) * 32.0f, m_globalPos.second, 32.0f, 32.0f, _currentTex, false, 0));
					break;
				case 6:
					m_block.push_back(Block(m_globalPos.first, m_globalPos.second - (j - 0) * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
					break;
				}
				switch (m_blockType[j])
				{
				case BlockEditerSelect::Ice:
					m_block[m_block.size() - 1].m_iceBlock = true;
					break;
				case BlockEditerSelect::IceWater:
					m_block[m_block.size() - 1].m_snowBlock = true;
					break;
				case BlockEditerSelect::Ladder:
					m_block[m_block.size() - 1].m_backStage = true;
					m_block[m_block.size() - 1].m_laderBlock = true;
					break;
				case BlockEditerSelect::Lava:
					m_block[m_block.size() - 1].m_lavaBlock = true;
					break;
				}
			}
		}
	}


	for (int i = 0;i < m_blockType.size();i++)
	{
		switch (m_blockType[i])
		{
		case BlockEditerSelect::Ice:
			m_block[m_block.size() - 1].m_iceBlock = true;
			break;
		case BlockEditerSelect::IceWater:
			m_block[m_block.size() - 1].m_snowBlock = true;
			break;
		case BlockEditerSelect::Ladder:
			m_block[m_block.size() - 1].m_backStage = true;
			m_block[m_block.size() - 1].m_laderBlock = true;
			break;
		case BlockEditerSelect::Lava:
			m_block[m_block.size() - 1].m_lavaBlock = true;
			break;
		}
		
	}
}
TerrainObject::TerrainObject(std::pair<float, float> pos, int type, std::vector<int> blockType, std::vector<int>blockVar,std::vector<Block> block)
{
	m_globalPos = pos;
	m_type = type;
	m_block = block;
	m_blockType = blockType;
	m_blockVar = blockVar;
	FoundBorder();
}

TerrainObject::TerrainObject(const TerrainObject& object)
{

	m_globalPos = object.m_globalPos;
	m_type = object.m_type;
	m_block = object.m_block;
	m_blockType = object.m_blockType;
	m_blockVar = object.m_blockVar;
	FoundBorder();
}

bool TerrainObject::IsContain()
{
	return !m_block.empty();
}

std::vector<int> TerrainObject::GetTypeBlock()
{
	return m_blockType;
}

std::pair<float, float> TerrainObject::GetGPOS()
{
	return m_globalPos;
}

std::vector<int> TerrainObject::GetVarBlock()
{
	return m_blockVar;
}

int TerrainObject::GetAngle()
{
	return m_type;
}

std::pair<float, float> TerrainObject::GetBorderX()
{
	return m_xBorder;
}

std::pair<float, float> TerrainObject::GetBorderY()
{
	return m_yBorder;
}
void TerrainObject::SetScroll(std::pair<int, int>* scroll)
{
	m_scroll = scroll;
	for (int i = 0; i < m_block.size(); i++)
	{
		m_block[i].SetScroll(m_scroll);
	}
}

size_t TerrainObject::GetTypeBlockSize()
{
	return m_blockType.size();
}

