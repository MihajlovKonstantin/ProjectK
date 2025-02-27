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
	enum SpawnerSelect { COUNTSS = 4, VoidSS = 0, Player, Enemy, Enemys };
	enum EditerSelect { COUNTES = 5, BlockMenu = 0, CharaMenu, ItemMenu, StageTypeMenu, InfoPanelMenu};
	enum IceBlockSelect { COUNTIBS = 2, Surface = 0, Inside };
	enum EnemySelect { COUNTENS = 2, Slime = 0, SnowBall };
	enum KeySelect { COUNTKS = 3, Yellow = 0, Red, Blue };
	enum ItemSelect { COUNTIS = 2,VoidIS = 0, Key };
	enum BlockEditerSelect { COUNTBES = 7, VoidBES = 0, Ground, Ice, IceWater, Ladder, Lava, Crate };
	enum StageTypeSelect {COUNTSTS = 2, Base = 0, KeyCollect};
	enum InfoPanelEnun { COUNTIPE = 7,VoidIPE = 0, Move, Jump, EditerMode, Draw, LavaInf, LadderInfo };
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
	std::array<KdTexture, 5> m_crateTex;
	KdTexture m_voidTex;
	//InformPanelVector
	std::vector<InformPanel> m_inform;
	//OtherTex
	KdTexture m_blockTex;
	KdTexture m_playerTex;
	KdTexture m_playerHpTex;
	KdTexture tmpTex;
	KdTexture m_backGround;
	KdTexture m_stageBaseTex;
	KdTexture m_slimeTex;
	KdTexture m_snowBallTex;
	KdTexture m_snowBallSpawnerTex, m_slimeSpawnerTex;
	KdTexture m_editerBaseTex;
	KdTexture m_noTex;
	KdTexture m_frame;
	//BlockLib
	static const int m_typeBlockNum = 7;
	std::array<std::vector<std::array<KdTexture*, 5>>, 7> m_blockLiblary;
	//EnemyLib
	static const int m_enemyNum = COUNTENS;
	std::array<std::vector<KdTexture*>, 2> m_enemylibrary;
	//ItemLib
	std::vector<KdTexture*> m_itemLibrary;
	//Editer
	std::pair<float, float> SpawnPos;
	Item _lastItem;
	int m_baseControlCoolTime = 25;
	int m_controlCoolTime = m_baseControlCoolTime;
	//Draw
	Math::Rectangle charaRect;
	Math::Rectangle m_editerRect;
	Math::Matrix matrix;
	Math::Matrix m_scaleMat;
	Math::Matrix m_transMat;
	Math::Matrix m_mat;
	std::array<POINT, 2> m_point;
	std::string str;
	const char* charStr = str.c_str();
	std::string m_message;
	Math::Rectangle spawnerRectangle = Math::Rectangle(0,0,64,64);
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
	bool m_sKey;
	bool m_aKey;
	bool _tKey = false;
	bool m_leftFlg;
	bool m_rightFlg;
	bool m_upFlg;
	bool m_downFlg;
	bool m_testCollision = false;
	bool m_jumpFlg = false;
	bool m_drawStartBool;
	bool CLEARFLAG = false;

	int RELEASE = 0;

	int currentCD = 0, MaxCD = 30;
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

	int m_baseClearCoolTime = 60 * 2;
	int m_clearCooltime = m_baseClearCoolTime;
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
	void DeleteItem();
	void SaveStage();
	void LoadStage();
	void UpdateGameScene();
	void UpdateEditScene();
	int MaxTypeBlock(int index);
	int MaxTypeItem();
	void SaveSpawn();
	void SaveItem();
	void LoadSpawn();
	void CreateSpawn();
	void DeleteSpawn();
	void StopMusic();
	int MaxTypeEnemy();
	void CreateDataPatch();
	void InitMap(std::string mapName);
	void SaveMap();
	void LoadMap();
	int GetClearFlag();
	KdTexture* GetBlockTex();
	void CreateInformPanel();
	void DeleteInformPanel();
	void SaveInformPanel();
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
