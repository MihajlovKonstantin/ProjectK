#include "main.h"
#define MenuSHADER KdShaderManager::GetInstance()
#include "Scene.h"
#pragma comment(lib, "Shlwapi.lib")
//===================================================================
// ���C��
//===================================================================
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)
{
	// ���������[�N��m�点��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// COM������
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	// mbstowcs_s�֐��œ��{��Ή��ɂ��邽�߂ɌĂ�
	setlocale(LC_ALL, "japanese");

	//===================================================================
	// ���s
	//===================================================================
	APP.Execute();

	// COM���
	CoUninitialize();

	return 0;
}


// �A�v���P�[�V���������ݒ�
bool Application::Init(int w, int h)
{

	//===================================================================
	// �E�B���h�E�쐬
	//===================================================================
	if (m_window.Create(w, h, "�_���W�������[�J�[", "Window") == false) {
		MessageBoxA(nullptr, "�E�B���h�E�쐬�Ɏ��s", "�G���[", MB_OK);
		return false;
	}

	//===================================================================
	// �t���X�N���[���m�F
	//===================================================================
	bool bFullScreen = false;
	/*if (MessageBoxA(m_window.GetWndHandle(), "�t���X�N���[���ɂ��܂����H", "�m�F", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
		bFullScreen = true;
	}*/


	//===================================================================
	// Direct3D
	//===================================================================

	// �f�o�C�X�̃f�o�b�O���[�h��L���ɂ���
	bool deviceDebugMode = false;
	#ifdef _DEBUG
	deviceDebugMode = true;
	#endif

	// Direct3D������
	std::string errorMsg;
	if (D3D.Init(m_window.GetWndHandle(), w, h, deviceDebugMode, errorMsg) == false) {
		MessageBoxA(m_window.GetWndHandle(), errorMsg.c_str(), "Direct3D���������s", MB_OK | MB_ICONSTOP);
		return false;
	}

	// �t���X�N���[���ݒ�
	if (bFullScreen) {
		D3D.GetSwapChain()->SetFullscreenState(TRUE, 0);
	}

	// �V�F�[�_�[������
	SHADER.Init();

	//===================================================================
	// XAudio2
	//===================================================================
	if (AUDIO.Init() == false)
	{
		MessageBoxA(m_window.GetWndHandle(), errorMsg.c_str(), "�T�E���h���������s", MB_OK | MB_ICONSTOP);
		return false;
	}

	//===================================================================
	// imgui�����ݒ�
	//===================================================================
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Dear ImGui style
	ImGui::StyleColorsClassic();
	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(m_window.GetWndHandle());
	ImGui_ImplDX11_Init(D3D.GetDev(), D3D.GetDevContext());
	m_backGround.Load("Texture/BackGround/Title.png");
	{
		// ���{��Ή�
		#include "imgui/ja_glyph_ranges.h"
		ImFontConfig config;
		config.MergeMode = true;
		io.Fonts->AddFontDefault();
		io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msgothic.ttc", 13.0f, &config, glyphRangesJapanese);
	}
	spriteBatch = new DirectX::SpriteBatch(D3D.GetDevContext());
	spriteFont = new DirectX::SpriteFont(D3D.GetDev(), L"SpriteFont.dat");
	CreateDataPath();
	return true;
}

void Application::InitDataFile()
{
	mainMenu.InitMainMenu();
	settingMenu.InitSetting();
	WindowsData.Init();
}
void Application::MakeDataLink()
{
	mainMenu.AddData(WindowsData);
	settingMenu.AddData(WindowsData);
}

// �A�v���P�[�V�����I��
void Application::Release()
{
	D3D.GetSwapChain()->SetFullscreenState(FALSE, 0);

	// imgui���
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	// �V�F�[�_���
	SHADER.Release();

	// Direct3D���
	D3D.Release();

	// XAudio2���
	AUDIO.Release();

	// �E�B���h�E�폜
	m_window.Release();

}
void Application::CreateExtensions()
{
	HKEY _hkey;
	LONG _result;
	const std::wstring _extensionMenu = L".menu";
	const std::wstring _fileType = L"Menu";
	_result = RegCreateKeyEx(HKEY_CLASSES_ROOT, _extensionMenu.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &_hkey, NULL);
	if (_result == ERROR_SUCCESS)
	{
		RegSetValueEx(_hkey, NULL, 0, REG_SZ, (BYTE*)_fileType.c_str(), (_fileType.length()) * sizeof(wchar_t) + 1);
		RegCloseKey(_hkey);
	}
	_result = RegCreateKeyEx(HKEY_CLASSES_ROOT, _fileType.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &_hkey, NULL);
	if (_result == ERROR_SUCCESS)
	{
		const char* _description = "Menu_Data";
		RegSetValueEx(_hkey, NULL, 0, REG_SZ, (BYTE*)_description, strlen(_description) + 1);
		RegCloseKey(_hkey);
	}
}
//�`��֐�
void Application::DrawButton(Button inputButton)
{
	size = inputButton.GetSize();
	position = inputButton.GetPosition();
	SHADER.m_spriteShader.DrawBox(position[0], position[1], size[0], size[1], &Math::Color(0.6, 0.6, 1, 1), true);
}
void Application::DrawButtonText(Button inputButton)
{
	position = inputButton.GetPosition();
	message = inputButton.GetText();
	float scale = inputButton.GetScale();
	size = inputButton.GetSize();
	DrawString(position[0] - size[0], position[1] + size[1] / 2, text, Math::Vector4(1, 0, 1, 1), scale);
}
void Application::DrawString(float _x, float _y, const char _text[], const Math::Vector4& _color, float scale)
{
	//���C�h������ɕϊ�����K�v������
	WCHAR* _wtext = new WCHAR[strlen(_text) + 1];
	mbstowcs_s(nullptr, _wtext, strlen(_text) + 1, _text, _TRUNCATE);

	//Begin�O��BlendState���擾
	ID3D11BlendState* oldBlendState = 0;
	float oldFactor[4];
	UINT oldMask = 0;
	D3D.GetDevContext()->OMGetBlendState(&oldBlendState, oldFactor, &oldMask);

	//BlendState�������p����Begin
	spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, oldBlendState);
	spriteFont->DrawString(spriteBatch, _wtext, Math::Vector2(_x + 640, -_y + 360), _color, 0.0f, { 0,0 }, scale);
	spriteBatch->End();

	//Begin�O��BlendState�𕜌�
	D3D.GetDevContext()->OMSetBlendState(oldBlendState, oldFactor, oldMask);

	//�ꎞ�擾����BlendState����� (������Ȃ��ƎQ�ƃJ�E���g������Ȃ�)
	KdSafeRelease(oldBlendState);

	delete[] _wtext;
}
//Mouse/Button �Ǘ�
bool Application::ClickButton(POINT inputMouse, Button inputButton)
{
	size = inputButton.GetSize();
	position = inputButton.GetPosition();
	if ((inputMouse.x - 640) >= (position[0] - size[0]) && (inputMouse.x - 640) <= (position[0] + size[0] * 1.05))
	{
		if ((360 - inputMouse.y) <= (position[1] + size[1] / 2) && (360 - inputMouse.y) >= (position[1] - size[1] * 2))
		{
			SHADER.m_spriteShader.DrawString(mouse.x - 640, 360 - mouse.y, "CLICK", Math::Vector4(1, 1, 1, 1));
			return true;
		}
	}
	return false;
}
void Application::MenuExecute(Menu inputMenu)
{
	m_endFlagWindows = false;
	int _startWindow = WindowsData.GetWindow();
	if (m_endFlag)
	{
		m_endFlagWindows = true;
	}

	//=========================================
	//
	// �E�B���h�E�֌W�̏���
	//
	//=========================================

	// �E�B���h�E�̃��b�Z�[�W����������
	m_window.ProcessMessage();

	// �E�B���h�E���j������Ă�Ȃ烋�[�v�I��
	if (m_window.IsCreated() == false)
	{
		m_endFlag = true;
		m_endFlagWindows = true;
	}
	AUDIO.Update();

	
	
	SHADER.m_spriteShader.Begin();
	// Menu�`�揈��
	MenuDraw(inputMenu);

	// MenuUpdate����

	MenuUpdate(inputMenu);
	SHADER.m_spriteShader.End();


	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	// GUI�`����s
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	D3D.GetSwapChain()->Present(0, 0);
	if (WindowsData.GetWindow() != _startWindow)
	{
		m_endFlagWindows = true;
	}
}
void Application::MenuUpdate(Menu inputMenu)
{
	GetCursorPos(&mouse);
	ScreenToClient(APP.m_window.GetWndHandle(), &mouse);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		int _buttonCNT = inputMenu.GetButtonsCNT();
		for (int i = 0; i < _buttonCNT; i++)
		{
			if (inputMenu.GetButton(i).GetActive())
			{
				if (ClickButton(mouse, inputMenu.GetButton(i)) == true)
				{
					inputMenu.EventClick(inputMenu.GetButton(i).SendClickData());
				}
			}
		}

	}
}
void Application::MenuDraw(Menu inputMenu)
{
	int _buttonCNT = inputMenu.GetButtonsCNT();
	for (int i = 0; i < _buttonCNT; i++)
	{
		if(inputMenu.GetButton(i).GetVisable())
			DrawButton(inputMenu.GetButton(i));

	}
	for (int i = 0; i < _buttonCNT; i++)
	{
		if (inputMenu.GetButton(i).GetVisable())
			DrawButtonText(inputMenu.GetButton(i));

	}
}

void Application::Game()
{
	DWORD st = timeGetTime();
	m_endFlagWindows = false;
	int _startWindow = WindowsData.GetWindow();
	if (m_endFlag)
	{
		m_endFlagWindows = true;
	}

	//=========================================
	//
	// �E�B���h�E�֌W�̏���
	//
	//=========================================

	// �E�B���h�E�̃��b�Z�[�W����������
	m_window.ProcessMessage();

	// �E�B���h�E���j������Ă�Ȃ烋�[�v�I��
	if (m_window.IsCreated() == false)
	{
		m_endFlag = true;
		m_endFlagWindows = true;
	}
	AUDIO.Update();

	D3D.GetDevContext()->ClearRenderTargetView(D3D.GetBackBuffer(), Math::Color(0.3f, 0.3f, 0.5f, 1));
	D3D.GetDevContext()->ClearDepthStencilView(D3D.GetZBuffer(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);

	SHADER.m_spriteShader.Begin();

	SCENE.Update();
	SHADER.m_cb7_Camera.Write();
	SCENE.DynamicDraw2D();
	SCENE.Draw2D();
	
	
	
	SHADER.m_spriteShader.End();
	

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	SCENE.ImGuiUpdate();
	// GUI�`����s
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
	D3D.GetSwapChain()->Present(0, 0);
	if (WindowsData.GetWindow() != _startWindow)
	{
		SCENE.StopMusic();
		m_endFlagWindows = true;
	}
	DWORD et = timeGetTime();
	// Fps����
	DWORD ms = 1000 / m_maxFps;
	if (et - st < ms)
	{
		Sleep(ms - (et - st));	// ����������҂�
	}

	// FPS�v��
	count++;
	if (st - baseTime >= 1000)
	{
		m_fps = (count * 1000) / (st - baseTime);
		baseTime = st;
		count = 0;
	}
	
}
void Application::CreateDataPath()
{
	const char* _homePath = std::getenv("USERPROFILE");
	if (!_homePath)
	{
		std::cerr << "�A�N�Z�X���o���܂���ł���";
		return;
	}
	char _documentPath[512];
	std::strcpy(_documentPath, _homePath);
	std::strcat(_documentPath, "\\Documents");

	char _result[512];
	std::strcpy(_result, _documentPath);
	std::strcat(_result, "\\Fault - another story");

	if (!PathFileExistsA(_result)) {
		// �D�y���u�{�������y�� �~�u �������u�����r���u��, �����x�t�p�u�} �u�v
		if (SHCreateDirectoryExA(NULL, _result, NULL) != ERROR_SUCCESS) {
			std::cerr << "Unable to create directory." << std::endl;
			return;
		}
	}
	dataFolderPath = _result;
	int i = 0;
}

// �A�v���P�[�V�������s
void Application::Execute()
{
	//===================================================================
	// �����ݒ�(�E�B���h�E�쐬�ADirect3D�������Ȃ�)
	//===================================================================
	if (APP.Init(1280, 720) == false) {
		return;
	}
	mainMenu.SetTexture(&m_backGround);
	CreateDataPath();//Create the Path to users data
	InitDataFile();//Inicialize menu and e.t.c
	MakeDataLink();//Data �Ɓ@Menu Class object �ڑ�����
	CreateExtensions();
	{
		std::ofstream outFile("example.menu");
		if (outFile.is_open()) {
			outFile << "Hello, this is a test file with custom extension.\n";
			outFile.close();
		}
		else {
			std::cerr << "Unable to open file for writing.\n";
		}
	}
	{
		std::ifstream inFile("example.menu");
		if (inFile.is_open()) {
			std::string line;
			getline(inFile, line, '\n');
			inFile.close();
		}
		else {
			std::cerr << "Unable to open file for reading.\n";
		}
	}
	
	AUDIO.Init();
	if (soundEffect->Load("Sound/57ac0ae7.wav")) {
		soundInstance = soundEffect->CreateInstance(true);

		soundInstance->Play3D(Math::Vector3(0, 0, 0), true, true);
		soundInstance->SetVolume(WindowsData.GetMusicVolume());
	}

	
	do//GameLoop
	{
		switch (WindowsData.GetWindow())
		{
		case WindowsControl::MainMenu:

			do
			{
				soundInstance->SetVolume(WindowsData.GetMusicVolume());
				mainMenu.Update();
				SHADER.m_spriteShader.SetMatrix(mainMenu.GetMatrix());
				SHADER.m_spriteShader.DrawTex(mainMenu.GetTexture(), mainMenu.GetRect());
				SHADER.m_spriteShader.SetMatrix(Math::Matrix::CreateTranslation(0, 0, 0));
				SHADER.m_spriteShader.DrawString(-200, 300, "�_���W�������[�J�[", { 1,0,0,1 });
				MenuExecute(mainMenu);
				
				
			} while ((m_endFlagWindows!=true));
				break;
		case WindowsControl::GameScene:
			soundInstance->Stop();
			if (gameSoundEffect->Load("Sound/maou_game_field02.wav")) {
				gameSoundInstance = gameSoundEffect->CreateInstance(true);
				gameSoundInstance->SetVolume(WindowsData.GetMusicVolume());
				gameSoundInstance->Play3D(Math::Vector3(0, 0, 0), true, true);
			}
			
			if(WindowsData.IsStarted()== false)
			{
				SCENE.Init(&WindowsData);
				WindowsData.StartGame();
				gameSoundInstance->SetVolume(WindowsData.GetMusicVolume());
			}
			else
			{
				gameSoundInstance->SetVolume(WindowsData.GetMusicVolume());
				SCENE.SetResumeWindows();
			}
			baseTime = timeGetTime();
			count = 0;
			do
			{
				gameSoundInstance->SetVolume(WindowsData.GetMusicVolume());
				Game();
			}while ((m_endFlagWindows != true));
			gameSoundInstance->Stop();
			soundInstance->Resume();
			break;
		case WindowsControl::Setting:
			do
			{
				soundInstance->SetVolume(WindowsData.GetMusicVolume());
				settingMenu.Update();
				MenuExecute(settingMenu);
			} while ((m_endFlagWindows != true));
			break;
		case WindowsControl::Records:
			break;
		default:
			break;
		}
		if(!soundInstance->IsPlay())
			{
					//RandomMusic();
					soundInstance->Play();
			 }
	} while (m_endFlag!=true);
	/*SCENE.Init();

	DWORD baseTime = timeGetTime();
	int count = 0;

	while (1)
	{

		// �����J�n����Get
		DWORD st = timeGetTime();

		// �Q�[���I���w�肪����Ƃ��̓��[�v�I��
		if (m_endFlag)
		{ 
			break;
		}

		//=========================================
		//
		// �E�B���h�E�֌W�̏���
		//
		//=========================================

		// �E�B���h�E�̃��b�Z�[�W����������
		m_window.ProcessMessage();

		// �E�B���h�E���j������Ă�Ȃ烋�[�v�I��
		if (m_window.IsCreated() == false)
		{
			break;
		}

		//=========================================
		//
		// �I�[�f�B�I����
		//
		//=========================================
		AUDIO.Update();

		//=========================================
		//
		// �Q�[������
		//
		//=========================================

		// �o�b�N�o�b�t�@�N���A
		D3D.GetDevContext()->ClearRenderTargetView(D3D.GetBackBuffer(), Math::Color(0.3f, 0.3f, 0.5f, 1));
		// Z�o�b�t�@�N���A
		D3D.GetDevContext()->ClearDepthStencilView(D3D.GetZBuffer(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);

		// �Q�[���X�V����
		SCENE.Update(&currentWindow);

		// �Q�[���`�揈��
		SHADER.m_spriteShader.Begin();
		SCENE.Draw2D();
		SHADER.m_spriteShader.End();


		//�����[�X����ImGui�̕����͒ʂ�Ȃ��悤�ɂ���
		// ImGui�J�n
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		// ImGui����
		SCENE.ImGuiUpdate();
		// GUI�`����s
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		//---------------------


		// BackBuffer -> FrontBuffer
		D3D.GetSwapChain()->Present(0, 0);


		//=========================================
		//
		// �t���[�����[�g����
		//
		//=========================================
		// �����I������Get
		DWORD et = timeGetTime();
		// Fps����
		DWORD ms = 1000 / m_maxFps;
		if (et - st < ms)
		{
			Sleep(ms - (et - st));	// ����������҂�
		}

		// FPS�v��
		count++;
		if (st - baseTime >= 1000)
		{
			m_fps = (count * 1000) / (st - baseTime);
			baseTime = st;
			count = 0;
		}

	}

	// �Q�[�����
	
	*/

	//===================================================================
	// �A�v���P�[�V�������
	//===================================================================
	SCENE.Release();
	Release();
}