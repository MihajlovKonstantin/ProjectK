#pragma once
#include "Pch.h"

class Scene
{
private:
	// テクスチャ ・・・ 画像データ
	KdTexture m_charaTex;
	KdTexture tmpTex;
	Math::Rectangle charaRect;
	// 行列 ・・・ 座標などの情報
	Math::Matrix matrix;
	
	std::string str;
	const char* charStr = str.c_str();
	Menu m_inGameSetting;

	//DrawButton 変数
	std::array<float, 2> size;
	std::array<float, 2>position;
	std::string message;
	const char* text = message.c_str();
	DirectX::SpriteBatch* spriteBatch;
	DirectX::SpriteFont* spriteFont;
	//Mouse 管理
	POINT mouse;
	WindowsControlData* WC;
	SceneControlData* SC;
	bool m_controlButtonClick = false;
	//test
	std::vector<KdTexture> m_asset;
	//std::vector<std::unique_ptr<
	PC m_player = PC({ 2,400 }, { 0,-1 },&m_charaTex);
	Block m_block = Block(0, 0, 32, 32, & m_charaTex, false, 1 );
	//test
	bool test;
	
public:
	enum Direction
	{
		Up,
		Right,
		Down,
		Left
	};
	// 初期設定
	void Init(WindowsControlData* WCInput);
	// 解放
	void Release();

	// 更新処理
	void Update();
	void UpdateMainMenu();
	// 描画処理
	void Draw2D();
	void DrawButton(Button inputButton);
	void DrawButtonText(Button inputButton);
	// GUI処理
	void ImGuiUpdate();
	bool ClickButton(POINT inputMouse,Button inputButton);
	void DrawString(float _x, float _y, const char _text[], const Math::Vector4& _color,float scale);
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
