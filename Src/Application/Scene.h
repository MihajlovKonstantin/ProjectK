#pragma once
#include "Pch.h"

class Scene
{
private:
	//ControlIndex
	int m_unitType = 1;
	int m_editerMenuIndex = 0;
	int m_selectedUnitVariant = 0;
	//enum
	enum SpawnerSelect { COUNTSS = 4, Player = 1, Enemy, Enemys };
	enum EditerSelect { COUNTES = 4, BlockMenu = 0, CharaMenu, ItemMenu,StageTypeMenu };
	enum IceBlockSelect { COUNTIBS = 2, Surface = 0, Inside };
	enum EnemySelect { COUNTENS = 2, Slime = 0, SnowBall };
	enum KeySelect{COUNTKS = 3,Yellow=0,Red,Blue};
	enum ItemSelect{COUNTIS = 1,Key = 0};
	enum BlockEditerSelect { COUNTBES = 6, Ground = 1, Ice, IceWater ,Ladder ,Lava};
	enum StageTypeSelect {COUNTSTS = 2, Base = 0, KeyCollect};
	//ObjectVector
	std::vector<Item> m_item;
	std::vector <Spawner> m_spawner;
	std::vector<Block> m_blocks;
	std::vector<TerrainObject> m_terrain;
	//ItemTexture
	std::array<KdTexture, 3> m_keyTexture;
	//BlockTexture
	std::array<KdTexture, 5> m_groundTex;
	std::array<KdTexture, 5> m_iceSurfaceTex;
	std::array<KdTexture, 5> m_iceInsideTex;
	std::array<KdTexture, 5> m_iceWaterBlockTex;
	std::array<KdTexture, 5> m_ladderTex;
	std::array<KdTexture, 5> m_lavaTex;
	//OtherTex
	KdTexture m_blockTex;
	KdTexture m_playerTex;
	KdTexture m_playerHpTex;
	KdTexture tmpTex;
	KdTexture m_backGround;
	KdTexture m_slimeTex;
	KdTexture m_snowBallTex;
	//BlockLib
	static const int m_typeBlockNum = 6;
	std::array<std::vector<std::array<KdTexture*, 5>>, 6> m_blockLiblary;
	//EnemyLib
	static const int m_enemyNum = COUNTENS;
	std::array<std::vector<KdTexture*>, 2> m_enemylibrary;
	//Editer
	std::pair<float, float> SpawnPos;
	Item _lastItem;
	bool m_drawStartBool;
	//Draw
	Math::Rectangle charaRect;
	Math::Matrix matrix;
	std::array<POINT, 2> m_point;
	std::string str;
	const char* charStr = str.c_str();
	//DrawButton 
	std::array<float, 2> size;
	std::array<float, 2>position;
	std::string message;
	//test
	DirectX::SpriteBatch* spriteBatch;
	DirectX::SpriteFont* spriteFont;
	//Mouse 
	POINT mouse;
	POINT m_mouse;
	//Configs
	WindowsControlData* WC;
	SceneControlData* SC;
	//Data
	std::string m_dataPath;
	std::string m_selectedPath;
	std::string m_selectedMap;
	//Scroll
	std::pair<int, int> m_scroll = { 0,0 };
	//Bool
	bool m_controlButtonClick = false;
	bool m_lKey;
	bool m_pKey;
	bool _tKey = false;
	bool m_leftFlg;
	bool m_rightFlg;
	bool m_upFlg;
	bool m_downFlg;
	bool m_testCollision = false;
	bool m_jumpFlg = false;
	int RELEASE = 0;

	std::array<bool, 3> m_keyFlag;
	//Player
	PC m_player = PC({ 0,0 }, { +2.0f,-1 }, &m_playerTex, &m_playerHpTex);
	//Stage
	int m_stageType = 0;
	int m_clearState[2];
	std::string m_clearStateString;
	const char* m_clearExpress = m_clearStateString.c_str();
	//hp関係
	std::string m_hpBar;
	const char* m_hpBarExpress = m_hpBar.c_str();
	float m_BaseHpAlphaCnt = 20.0f;
	float m_hpAlphaCnt = m_BaseHpAlphaCnt;
	float m_hpAlpha = 0;

	bool CLEARFLAG = false;
	Menu m_inGameSetting;
	Stage m_stage;
public:
	// �����00
	void Init(WindowsControlData* WCInput,std::string dataPath,std::string selectedPath);
	// ���
	void Release();

	// �X�V����
	void Update();
	// �`�揈��
	void Draw2D();
	void DrawButton(Button inputButton);
	void DrawButtonText(Button inputButton);
	// GUI����
	void ImGuiUpdate();
	bool ClickButton(POINT inputMouse, Button inputButton);
	void DrawString(float _x, float _y, const char _text[], const Math::Vector4& _color, float scale);
	void SetResumeWindows();
	void DynamicDraw2D();
	void CreateTerrainObject();
	void CreateItem();
	void SaveStage();
	void LoadStage();
	void UpdateGameScene();
	void UpdateEditScene();
	int MaxTypeBlock(int index);
	int MaxTypeItem();
	void SaveSpawn();
	void LoadSpawn();
	void CreateSpawn();
	void StopMusic();
	int MaxTypeEnemy();
	void CreateDataPatch();
	void InitMap(std::string mapName);
	void SaveMap();
	void LoadMap();
private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
