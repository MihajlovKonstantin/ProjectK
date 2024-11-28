#pragma once
#include "Pch.h"
class TerrainObject
{
	std::pair<float, float> m_localPos;
	std::pair<float, float> m_globalPos;//position
	std::pair<float, float> m_xBorder;
	std::pair<float, float> m_yBorder;
	int m_type;							//angle
	std::vector<Block> m_block;
	std::vector<int> m_blockType;		//type
	bool m_dirty = false;
	KdTexture* m_firstBlockTex;
	
public:
	bool OnCollisionRange(std::pair<float, float>pos);
	void Replace(Block block);
	void ClearReplace();
	void FoundBorder();
	void Update();
	std::vector<Block>* GetBlocks();
	TerrainObject(std::pair<float, float> pos, int type, std::vector<int> blockType,KdTexture& tex);
	TerrainObject(std::pair<float, float> pos, int type, std::vector<int> blockType, std::vector<Block> block);
	TerrainObject(const TerrainObject& object);
	std::vector<int> GetTypeBlock();		//type getter
	std::pair<float, float> GetGPOS();		//position getter
	int GetAngle();							//angle getter
};

