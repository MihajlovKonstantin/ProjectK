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
	enum EditerSelect { COUNTES = 3, BlockMenu = 0, CharaMenu, ItemMenu };
	enum EnemySelect { COUNTENS = 2, Slime = 0, IceBall };
	enum KeySelect{COUNTKS = 3,Yellow=0,Red,Blue};
	enum ItemSelect{COUNTIS = 1,Key = 0};
	enum IceBlockSelect { COUNTIBS = 2, Surface = 0, Inside };
	enum BlockEditerSelect { COUNTBES = 4, Ground = 1, Ice, IceWater };
	//ObjectVector
	std::vector<Item> m_item;
	std::vector <Spawner> m_spawner;
	std::vector<Block> m_blocks;
	std::vector<TerrainObject> m_terrain;
	//ItemTexture
	std::array<KdTexture, 3> m_keyTexture;
	//BlockTexture]
	std::array<KdTexture, 5> m_groundTex;
	std::array<KdTexture, 5> m_iceSurfaceTex;
	std::array<KdTexture, 5> m_iceInsideTex;
	std::array<KdTexture, 5> m_iceWaterBlockTex;
	KdTexture m_backGround;
	static const int m_typeBlockNum = 4;

	std::array<std::vector<std::array<KdTexture*, 5>>, 4> m_blockLiblary;
	//Start	Data
	std::pair<float, float> SpawnPos = { 200,100 };

	Item _lastItem;
	
	int m_clearState[2];
	std::string m_clearStateString;
	const char* m_clearExpress = m_clearStateString.c_str();
	bool CLEARFLAG = false;
		//m_terrain
	
	std::array<bool, 3> m_keyFlag;
	KdTexture m_BlockTex;
	KdTexture m_playerTex;
	KdTexture tmpTex;
	Math::Rectangle charaRect;
	// �s�� �E�E�E ���W�Ȃǂ̏��
	Math::Matrix matrix;
	//int test;
	std::array<POINT, 2> m_point;
	POINT m_mouse;
	bool m_drawStartBool;
	std::string str;
	const char* charStr = str.c_str();
	Menu m_inGameSetting;
	Stage m_stage;
	//DrawButton 
	std::array<float, 2> size;
	std::array<float, 2>position;
	std::string message;
	//test
	DirectX::SpriteBatch* spriteBatch;
	DirectX::SpriteFont* spriteFont;
	//Mouse 
	POINT mouse;
	WindowsControlData* WC;
	SceneControlData* SC;
	bool m_controlButtonClick = false;
	std::vector<KdTexture> m_asset;
	PC m_player = PC({ 0,0 }, { +2.0f,-1 }, &m_playerTex);
	float num = 6.5f / 3.0f;
	float m_rad = float(M_PI)*0.0f;
	bool m_testCollision = false;
	bool _tKey = false;
	int m_stageType = 0;
	//キー制御用
	bool m_lKey;
	bool m_pKey;
	//ジャンプ用
	bool m_jumpFlg = false;
public:
	// �����00
	void Init(WindowsControlData* WCInput);
	// ���
	void Release();

	// �X�V����
	void Update();
	void UpdateMainMenu();
	// �`�揈��
	void Draw2D();
	void DrawButton(Button inputButton);
	void DrawButtonText(Button inputButton);
	// GUI����
	void ImGuiUpdate();
	bool ClickButton(POINT inputMouse, Button inputButton);
	void DrawString(float _x, float _y, const char _text[], const Math::Vector4& _color, float scale);
	void DrawGraph();
	void DrawTexts();
	void DrawMainScene(Math::Color inputColor);
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
