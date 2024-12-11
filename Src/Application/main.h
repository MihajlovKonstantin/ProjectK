#pragma once
#include "Pch.h"

//============================================================
// アプリケーションクラス
//	APP.～ でどこからでもアクセス可能
//============================================================
class Application
{
// メンバ
private:
	POINT mouse;
	//Windows管理
	enum WindowsControl
	{
		MainMenu = 1,
		GameScene,
		Setting,
		Records
	};
	//Dataの読み込み
	char* dataFolderPath;
	WindowsControlData WindowsData;
	KeyEvent event;
	std::shared_ptr<KdSoundEffect> soundEffect = std::make_shared<KdSoundEffect>();
	std::shared_ptr<KdSoundInstance> soundInstance;
	std::shared_ptr<KdSoundEffect> gameSoundEffect = std::make_shared<KdSoundEffect>();
	std::shared_ptr<KdSoundInstance> gameSoundInstance;
	//SpriteFont
	DirectX::SpriteBatch* spriteBatch;
	DirectX::SpriteFont* spriteFont;
	//DrawButton 変数
	std::array<float, 2> size;
	std::array<float, 2>position;
	std::string message;
	const char* text = message.c_str();
	//Menu
	Menu mainMenu;
	Menu settingMenu;
	Menu recordMenu;
	KdTexture m_backGround;
	// FPS計測
	DWORD baseTime;
	int count;
public:

	// アプリケーション実行
	void Execute();

	// アプリケーション終了
	void End() { m_endFlag = true; }


	//=====================================================
	// グローバルデータ
	//=====================================================

	// ゲームウィンドウクラス
	KdGameWindow		m_window;

	// FPS制御
	int				m_fps = 0;					// 現在のFPS値
	int				m_maxFps = 60;				// 最大FPS


private:

	// アプリケーション初期化
	bool Init(int w, int h);
	void InitDataFile();
	void MakeDataLink();
	// アプリケーション解放
	void Release();
	
	// ゲーム終了フラグ trueで終了する
	bool		m_endFlag = false;
	bool m_endFlagWindows = false;
	//描画関数
	void DrawButton(Button inputButton);
	void DrawButtonText(Button inputButton);
	void DrawString(float _x, float _y, const char _text[], const Math::Vector4& _color, float scale);
	//Menu管理関数
	void MenuUpdate(Menu inputMenu);
	void MenuDraw(Menu inputMenu);
	bool ClickButton(POINT inputMouse, Button inputButton);
	void MenuExecute(Menu inputMenu);
	//GameLoop
	void Game();
	//Init処理/dataの読み込み
	void CreateDataPath();
	void CreateExtensions();
//=====================================================
// シングルトンパターン
//=====================================================
private:
	// 
	Application() {}

public:
	static Application &GetInstance(){
		static Application Instance;
		return Instance;
	}
};

// 簡単にアクセスできるようにするためのマクロ
#define APP Application::GetInstance()
