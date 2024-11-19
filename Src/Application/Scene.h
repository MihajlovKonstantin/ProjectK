#pragma once
#include "Pch.h"

class Scene
{
private:
	//test2
	// test
	KdTexture m_charaTex;
	KdTexture tmpTex;
	Math::Rectangle charaRect;
	// �s�� �E�E�E ���W�Ȃǂ̏��
	Math::Matrix matrix;
	//int test;
	std::string str;
	const char* charStr = str.c_str();
	Menu m_inGameSetting;
	Stage m_stage;
	//DrawButton �ϐ�
	std::array<float, 2> size;
	std::array<float, 2>position;
	std::string message;
	
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
	PC m_player = PC({ 0,400 }, { +0.1f,-1 }, &m_charaTex);
	float num = 6.5f / 3.0f;
	float m_rad = M_PI*0.25f;
	Block m_block = Block(-64, 0, 32.0f, 32.0f, &m_charaTex, false, m_rad);
	Block m_blockSecond = Block(-32, 0, 32.0f, 32.0f, &m_charaTex, false, m_rad);
	bool _test = false;
	//test
	bool test;
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
