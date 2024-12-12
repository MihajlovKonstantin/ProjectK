#include "main.h"
#define MenuSHADER KdShaderManager::GetInstance()
#include "Scene.h"
#pragma comment(lib, "Shlwapi.lib")
//===================================================================
// メイン
//===================================================================
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)
{
	// メモリリークを知らせる
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// COM初期化
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	// mbstowcs_s関数で日本語対応にするために呼ぶ
	setlocale(LC_ALL, "japanese");

	//===================================================================
	// 実行
	//===================================================================
	APP.Execute();

	// COM解放
	CoUninitialize();

	return 0;
}


// アプリケーション初期設定
bool Application::Init(int w, int h)
{

	//===================================================================
	// ウィンドウ作成
	//===================================================================
	if (m_window.Create(w, h, "ダンジョンメーカー", "Window") == false) {
		MessageBoxA(nullptr, "ウィンドウ作成に失敗", "エラー", MB_OK);
		return false;
	}

	//===================================================================
	// フルスクリーン確認
	//===================================================================
	bool bFullScreen = false;
	/*if (MessageBoxA(m_window.GetWndHandle(), "フルスクリーンにしますか？", "確認", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
		bFullScreen = true;
	}*/


	//===================================================================
	// Direct3D
	//===================================================================

	// デバイスのデバッグモードを有効にする
	bool deviceDebugMode = false;
	#ifdef _DEBUG
	deviceDebugMode = true;
	#endif

	// Direct3D初期化
	std::string errorMsg;
	if (D3D.Init(m_window.GetWndHandle(), w, h, deviceDebugMode, errorMsg) == false) {
		MessageBoxA(m_window.GetWndHandle(), errorMsg.c_str(), "Direct3D初期化失敗", MB_OK | MB_ICONSTOP);
		return false;
	}

	// フルスクリーン設定
	if (bFullScreen) {
		D3D.GetSwapChain()->SetFullscreenState(TRUE, 0);
	}

	// シェーダー初期化
	SHADER.Init();

	//===================================================================
	// XAudio2
	//===================================================================
	if (AUDIO.Init() == false)
	{
		MessageBoxA(m_window.GetWndHandle(), errorMsg.c_str(), "サウンド初期化失敗", MB_OK | MB_ICONSTOP);
		return false;
	}

	//===================================================================
	// imgui初期設定
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
		// 日本語対応
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

// アプリケーション終了
void Application::Release()
{
	D3D.GetSwapChain()->SetFullscreenState(FALSE, 0);

	// imgui解放
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	// シェーダ解放
	SHADER.Release();

	// Direct3D解放
	D3D.Release();

	// XAudio2解放
	AUDIO.Release();

	// ウィンドウ削除
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
//描画関数
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
	//ワイド文字列に変換する必要がある
	WCHAR* _wtext = new WCHAR[strlen(_text) + 1];
	mbstowcs_s(nullptr, _wtext, strlen(_text) + 1, _text, _TRUNCATE);

	//Begin前のBlendStateを取得
	ID3D11BlendState* oldBlendState = 0;
	float oldFactor[4];
	UINT oldMask = 0;
	D3D.GetDevContext()->OMGetBlendState(&oldBlendState, oldFactor, &oldMask);

	//BlendStateを引き継いでBegin
	spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, oldBlendState);
	spriteFont->DrawString(spriteBatch, _wtext, Math::Vector2(_x + 640, -_y + 360), _color, 0.0f, { 0,0 }, scale);
	spriteBatch->End();

	//Begin前のBlendStateを復元
	D3D.GetDevContext()->OMSetBlendState(oldBlendState, oldFactor, oldMask);

	//一時取得したBlendStateを解放 (解放しないと参照カウントが減らない)
	KdSafeRelease(oldBlendState);

	delete[] _wtext;
}
//Mouse/Button 管理
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
	// ウィンドウ関係の処理
	//
	//=========================================

	// ウィンドウのメッセージを処理する
	m_window.ProcessMessage();

	// ウィンドウが破棄されてるならループ終了
	if (m_window.IsCreated() == false)
	{
		m_endFlag = true;
		m_endFlagWindows = true;
	}
	AUDIO.Update();

	
	
	SHADER.m_spriteShader.Begin();
	// Menu描画処理
	MenuDraw(inputMenu);

	// MenuUpdate処理

	MenuUpdate(inputMenu);
	SHADER.m_spriteShader.End();


	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	// GUI描画実行
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
	// ウィンドウ関係の処理
	//
	//=========================================

	// ウィンドウのメッセージを処理する
	m_window.ProcessMessage();

	// ウィンドウが破棄されてるならループ終了
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
	// GUI描画実行
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
	D3D.GetSwapChain()->Present(0, 0);
	if (WindowsData.GetWindow() != _startWindow)
	{
		SCENE.StopMusic();
		m_endFlagWindows = true;
	}
	DWORD et = timeGetTime();
	// Fps制御
	DWORD ms = 1000 / m_maxFps;
	if (et - st < ms)
	{
		Sleep(ms - (et - st));	// 速すぎたら待つ
	}

	// FPS計測
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
		std::cerr << "アクセスが出来ませんでした";
		return;
	}
	char _documentPath[512];
	std::strcpy(_documentPath, _homePath);
	std::strcat(_documentPath, "\\Documents");

	char _result[512];
	std::strcpy(_result, _documentPath);
	std::strcat(_result, "\\Fault - another story");

	if (!PathFileExistsA(_result)) {
		// Директория не существует, создаем её
		if (SHCreateDirectoryExA(NULL, _result, NULL) != ERROR_SUCCESS) {
			std::cerr << "Unable to create directory." << std::endl;
			return;
		}
	}
	dataFolderPath = _result;
	int i = 0;
}

// アプリケーション実行
void Application::Execute()
{
	//===================================================================
	// 初期設定(ウィンドウ作成、Direct3D初期化など)
	//===================================================================
	if (APP.Init(1280, 720) == false) {
		return;
	}
	mainMenu.SetTexture(&m_backGround);
	CreateDataPath();//Create the Path to users data
	InitDataFile();//Inicialize menu and e.t.c
	MakeDataLink();//Data と　Menu Class object 接続する
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
				SHADER.m_spriteShader.DrawString(-200, 300, "ダンジョンメーカー", { 1,0,0,1 });
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

		// 処理開始時間Get
		DWORD st = timeGetTime();

		// ゲーム終了指定があるときはループ終了
		if (m_endFlag)
		{ 
			break;
		}

		//=========================================
		//
		// ウィンドウ関係の処理
		//
		//=========================================

		// ウィンドウのメッセージを処理する
		m_window.ProcessMessage();

		// ウィンドウが破棄されてるならループ終了
		if (m_window.IsCreated() == false)
		{
			break;
		}

		//=========================================
		//
		// オーディオ処理
		//
		//=========================================
		AUDIO.Update();

		//=========================================
		//
		// ゲーム処理
		//
		//=========================================

		// バックバッファクリア
		D3D.GetDevContext()->ClearRenderTargetView(D3D.GetBackBuffer(), Math::Color(0.3f, 0.3f, 0.5f, 1));
		// Zバッファクリア
		D3D.GetDevContext()->ClearDepthStencilView(D3D.GetZBuffer(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);

		// ゲーム更新処理
		SCENE.Update(&currentWindow);

		// ゲーム描画処理
		SHADER.m_spriteShader.Begin();
		SCENE.Draw2D();
		SHADER.m_spriteShader.End();


		//リリース時はImGuiの部分は通らないようにする
		// ImGui開始
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		// ImGui処理
		SCENE.ImGuiUpdate();
		// GUI描画実行
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		//---------------------


		// BackBuffer -> FrontBuffer
		D3D.GetSwapChain()->Present(0, 0);


		//=========================================
		//
		// フレームレート制御
		//
		//=========================================
		// 処理終了時間Get
		DWORD et = timeGetTime();
		// Fps制御
		DWORD ms = 1000 / m_maxFps;
		if (et - st < ms)
		{
			Sleep(ms - (et - st));	// 速すぎたら待つ
		}

		// FPS計測
		count++;
		if (st - baseTime >= 1000)
		{
			m_fps = (count * 1000) / (st - baseTime);
			baseTime = st;
			count = 0;
		}

	}

	// ゲーム解放
	
	*/

	//===================================================================
	// アプリケーション解放
	//===================================================================
	SCENE.Release();
	Release();
}