#pragma once
#include "Pch.h"

//============================================================
// �A�v���P�[�V�����N���X
//	APP.�` �łǂ�����ł��A�N�Z�X�\
//============================================================
class Application
{
// �����o
private:
	POINT mouse;
	//Windows�Ǘ�
	enum WindowsControl
	{
		MainMenu = 1,
		GameScene,
		Setting,
		Records
	};
	//Data�̓ǂݍ���
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
	//DrawButton �ϐ�
	std::array<float, 2> size;
	std::array<float, 2>position;
	std::string message;
	const char* text = message.c_str();
	//Menu
	Menu mainMenu;
	Menu settingMenu;
	Menu recordMenu;
	KdTexture m_backGround;
	// FPS�v��
	DWORD baseTime;
	int count;
public:

	// �A�v���P�[�V�������s
	void Execute();

	// �A�v���P�[�V�����I��
	void End() { m_endFlag = true; }


	//=====================================================
	// �O���[�o���f�[�^
	//=====================================================

	// �Q�[���E�B���h�E�N���X
	KdGameWindow		m_window;

	// FPS����
	int				m_fps = 0;					// ���݂�FPS�l
	int				m_maxFps = 60;				// �ő�FPS


private:

	// �A�v���P�[�V����������
	bool Init(int w, int h);
	void InitDataFile();
	void MakeDataLink();
	// �A�v���P�[�V�������
	void Release();
	
	// �Q�[���I���t���O true�ŏI������
	bool		m_endFlag = false;
	bool m_endFlagWindows = false;
	//�`��֐�
	void DrawButton(Button inputButton);
	void DrawButtonText(Button inputButton);
	void DrawString(float _x, float _y, const char _text[], const Math::Vector4& _color, float scale);
	//Menu�Ǘ��֐�
	void MenuUpdate(Menu inputMenu);
	void MenuDraw(Menu inputMenu);
	bool ClickButton(POINT inputMouse, Button inputButton);
	void MenuExecute(Menu inputMenu);
	//GameLoop
	void Game();
	//Init����/data�̓ǂݍ���
	void CreateDataPath();
	void CreateExtensions();
//=====================================================
// �V���O���g���p�^�[��
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

// �ȒP�ɃA�N�Z�X�ł���悤�ɂ��邽�߂̃}�N��
#define APP Application::GetInstance()
