#pragma once
#include "Pch.h"

#include "Src/Application/BlockEnum.h"
class TerrainObject
{
	std::pair<float, float> m_localPos;
	std::pair<float, float> m_globalPos;//position
	std::pair<float, float> m_xBorder;
	std::pair<float, float> m_yBorder;
	std::array<std::vector<std::array<KdTexture*, 5>>, 4>* m_texture;
	int m_type;							//angle
	std::vector<Block> m_block;
	std::vector<int> m_blockType;//type
	std::vector<int> m_blockVar;
	bool m_dirty = false;
	KdTexture* m_firstBlockTex;
	
public:
	bool OnCollisionRange(std::pair<float, float>pos);
	void Replace(Block block);
	void ClearReplace();
	void FoundBorder();
	void Update();
	void EarthBlock(int type,int j);
	void IceBlock(int type, int j,int typeblock);
	std::vector<Block>* GetBlocks();
	TerrainObject(std::pair<float, float> pos, int type, std::vector<int> blockType,std::vector<int>blockVar, std::array<std::vector<std::array<KdTexture*,5>>,4>* textLib);
	TerrainObject(std::pair<float, float> pos, int type, std::vector<int> blockType,std::vector<int>blockVar,std::vector<Block> block);
	TerrainObject(const TerrainObject& object);
	bool IsContain();
	//enemyspaw(int x,int y,int inter=0,int num=1)
	//dosomthink(int a,float j =0.0f)
	std::vector<int> GetTypeBlock();		//type getter
	std::pair<float, float> GetGPOS();		//position getter
	std::vector<int> GetVarBlock();			//var getter
	int GetAngle();							//angle getter
};

