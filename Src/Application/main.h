#pragma once
#include "Pch.h"
#include <algorithm>
#include <sstream>
//extern "C"
//{
//	#include "Windows.h"
//}

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
		StartScreen,
		SelectPlayebleMapMenu,
		SelectEditerMapMenu,
		CampainMenu,
		Help
	};
	//Data�̓ǂݍ���
	std::string dataFolderPath;
	std::string mapFolderPath;
	//std::string currentMapPath;
	std::string editerMapFolderPath;
	std::string programmPath;
	std::string lastSelectedPath;
	std::vector<std::string> playebleMapList;
	std::vector<std::string> editerMapList;
	std::vector<std::string> campainMap;
	std::vector<int> campainVisable;

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
	Menu selectPlaybleMapMenu;
	Menu selectEditerMapMenu;
	Menu campainMenu;
	Menu startScreen;
	Menu helpMenu;
	//Texture
	KdTexture m_mainMenuBackGround;
	KdTexture m_titleLogo;
	KdTexture m_frame;
	KdTexture m_settingBack1;
	KdTexture m_settingBack2;
	KdTexture m_editorBack;
	KdTexture m_playBack1;
	KdTexture m_playBack2;
	KdTexture m_compainBack;
	KdTexture m_startScreenBack;

	Campain m_campain;
	
	Math::Matrix m_scaleMat;
	Math::Matrix m_transMat;
	Math::Matrix m_mat;
	//�N���b�N�֌W
	bool m_settingFlg = false;
	bool m_lButtonFlg = false;
	int m_musicCnt = 0;
	// FPS�v��
	DWORD baseTime;
	int count;

	//Test
	string __text;
	const char* _convText = __text.c_str();
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
	KdGameWindow		m_nameSelectWindow;
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
	void MenuUpdate(Menu &inputMenu);
	void MenuDraw(Menu& inputMenu);
	bool ClickButton(POINT inputMouse, Button inputButton);
	void MenuExecute(Menu& inputMenu);
	//GameLoop
	void Game();
	//Init����/data�̓ǂݍ���
	void CreateDataPath();
	void CreateExtensions();
	void LoadMapList();
	void LoadCampain();
	int ExtractNumber(const string& s);
	void BubbleSort(vector<string>& strings);
	void SaveCampain();
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
