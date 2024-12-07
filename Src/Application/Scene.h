﻿#pragma once
#include "Pch.h"

class Scene
{
private:
	//test2
	// test
	int BlockKinds = 1;
	int EditerMenu = BlockMenu;
	int IceBlockMenu = Surface;
	enum EditerSelect {BlockMenu,EnemyMenu,ItemMenu};
	enum IceBlockSelect {Surface,Inside};
	std::vector<Item> m_item;
	Item _key;
	std::array<KdTexture,3> _texture;
	bool CLEARFLAG = false;
	std::vector<Block> m_blocks;
	std::vector<TerrainObject> m_terrain;	//m_terrain
	std::array<KdTexture, 5> m_groundTex;
	std::array<KdTexture, 5> m_iceSurfaceTex;
	std::array<KdTexture, 5> m_iceInsideTex;
	std::array<bool, 3> m_keyFlag;
	KdTexture m_IceSurfaceBlockTex;
	KdTexture m_IceInsideBlockTex;
	KdTexture m_BlockTex;
	KdTexture m_GroundBlockTex;
	KdTexture m_IceWaterBlockTex;
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
	//DrawButton �ϐ�
	std::array<float, 2> size;
	std::array<float, 2>position;
	std::string message;
	//test
	DirectX::SpriteBatch* spriteBatch;
	DirectX::SpriteFont* spriteFont;
	//Mouse �Ǘ�
	POINT mouse;
	WindowsControlData* WC;
	//DirectX::BoundingSphere;
	SceneControlData* SC;
	bool m_controlButtonClick = false;
	//test
	std::vector<KdTexture> m_asset;
	//std::vector<std::unique_ptr<
	PC m_player = PC({ 165,200 }, { +2.0f,-1 }, &m_playerTex);
	float num = 6.5f / 3.0f;
	float m_rad = float(M_PI)*0.0f;
	bool _test = false;
	bool _tKey = false;
	//test
	bool test;
	//キー制御用
	bool lKey;
	bool pKey;
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
	void SaveStage();
	void LoadStage();
	void UpdateGameScene();
	void UpdateEditScene();
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
