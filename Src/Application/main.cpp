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
	system("dir >temp.txt");
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
		D3D.GetSwapChain()->SetFullscreenState(true, 0);
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
	m_mainMenuBackGround1.Load("Texture/BackGround/Title.png");
	m_mainMenuBackGround2.Load("Texture/BackGround/Title2.png");
	m_titleLogo.Load("Texture/BackGround/titleLogo.png");
	m_frame.Load("Texture/BackGround/frame.png");
	m_settingBack1.Load("Texture/BackGround/setting.png");
	m_settingBack2.Load("Texture/BackGround/backSetting.png");
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
	mainMenu.InitMainMenu(dataFolderPath);
	settingMenu.InitSetting();
	WindowsData.Init();
	selectPlaybleMapMenu.InitSelectMapPlayeble(playebleMapList, mapFolderPath, dataFolderPath);
	selectEditerMapMenu.InitSelectEditingMap(editerMapList, editerMapFolderPath, dataFolderPath);
}
void Application::MakeDataLink()
{
	mainMenu.AddData(WindowsData);
	settingMenu.AddData(WindowsData);
	selectPlaybleMapMenu.AddData(WindowsData);
	selectEditerMapMenu.AddData(WindowsData);
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
	const std::wstring _extensionMap = L".map";
	const std::wstring _fileTypeMap = L"Map";
	_result = RegCreateKeyEx(HKEY_CLASSES_ROOT, _extensionMap.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &_hkey, NULL);
	if (_result == ERROR_SUCCESS)
	{
		RegSetValueEx(_hkey, NULL, 0, REG_SZ, (BYTE*)_fileTypeMap.c_str(), (_fileTypeMap.length()) * sizeof(wchar_t) + 1);
		RegCloseKey(_hkey);
	}
	_result = RegCreateKeyEx(HKEY_CLASSES_ROOT, _fileTypeMap.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &_hkey, NULL);
	if (_result == ERROR_SUCCESS)
	{
		const char* _description = "Map_Data";
		RegSetValueEx(_hkey, NULL, 0, REG_SZ, (BYTE*)_description, strlen(_description) + 1);
		RegCloseKey(_hkey);
	}
}
void Application::LoadMapList()
{
	string _path = "";
	_path+= dataFolderPath;
	_path += "\\Map";
	mapFolderPath = _path;
	if (!PathFileExistsA(_path.c_str()))
	{
		if (SHCreateDirectoryExA(NULL, _path.c_str(), NULL) != ERROR_SUCCESS) {
			std::cerr << "Unable to create directory." << std::endl;
			return;
		}
	}

	playebleMapList.clear();
	std::string _dirFinder = "dir \"" + _path + "\" *.map /b  > temp1.txt";
	system(_dirFinder.c_str());
	std::ifstream inFile("temp1.txt");
	{
		if (inFile.is_open())
		{
			std::string line;
			while (std::getline(inFile, line, '\n'))
			{
				playebleMapList.push_back(line);
			}
		}
	}
	inFile.close();
	selectPlaybleMapMenu.InitSelectMapPlayeble(playebleMapList, _path,dataFolderPath);

	editerMapList.clear();
	_path = "";
	_path += dataFolderPath;
	_path += "\\EditMap";
	editerMapFolderPath = _path;

	if (!PathFileExistsA(_path.c_str()))
	{
		if (SHCreateDirectoryExA(NULL, _path.c_str(), NULL) != ERROR_SUCCESS) {
			std::cerr << "Unable to create directory." << std::endl;
			return;
		}
	}

	_dirFinder = "dir \"" + _path + "\" *.map /b  > temp2.txt";
	system(_dirFinder.c_str());
	inFile = std::ifstream("temp2.txt");
	{
		if (inFile.is_open())
		{
			std::string line;
			while (std::getline(inFile, line, '\n'))
			{
				editerMapList.push_back(line);
			}
		}
	}
	inFile.close();

	
}

void Application::InitSelectMapMenu()
{

}

//描画関数
void Application::DrawButton(Button inputButton)
{
	size = inputButton.GetSize();
	position = inputButton.GetPosition();
	std::pair<float, float> _mouse(mouse.x - 640, 360 - mouse.y);

	//全画面かどうか検知する
	//if (GetAsyncKeyState('A'))D3D.GetSwapChain()->SetFullscreenState(TRUE, 0);
	//if (GetAsyncKeyState('D'))D3D.GetSwapChain()->SetFullscreenState(FALSE, 0);
	
	HWND hwnd = GetForegroundWindow();
	LONG style = GetWindowLong(hwnd, GWL_STYLE);
	auto _borderLess = (style & WS_CAPTION) != 0;
	//int a = 1;
	//GetConsoleWindow;
	HWND hWnd = GetConsoleWindow();
	if (IsZoomed(hWnd))
	{
		int a = 1;
	}

	//if (_borderLess)
	/*{
		if (_mouse.first >= (position[0] + 150 - size[0]) && _mouse.first <= (position[0] + 150 + size[0]))
		{
			if (_mouse.second <= (position[1] - 100 + size[1]) && _mouse.second >= (position[1] - 100 - size[1]))
			{
				if (size[0] > 100) m_scaleMat = Math::Matrix::CreateScale(2.5f, 1.5f, 0);
				else m_scaleMat = Math::Matrix::CreateScale(1.5f, 1.5f, 0);
				m_transMat = Math::Matrix::CreateTranslation(position[0], position[1], 0);
				m_mat = m_scaleMat * m_transMat;
				SHADER.m_spriteShader.SetMatrix(m_mat);
				SHADER.m_spriteShader.DrawTex(&m_frame, Math::Rectangle(0, 0, 100, 60), 1.0f);
			}
		}
	}*/
	//else
	{
		if (_mouse.first >= (position[0] - size[0]) && _mouse.first <= (position[0] + size[0]))
		{
			if (_mouse.second <= (position[1] + size[1]) && _mouse.second >= (position[1] - size[1]))
			{
				if (size[0] > 100) m_scaleMat = Math::Matrix::CreateScale(2.5f, 1.5f, 0);
				else m_scaleMat = Math::Matrix::CreateScale(1.5f, 1.5f, 0);
				m_transMat = Math::Matrix::CreateTranslation(position[0], position[1], 0);
				m_mat = m_scaleMat * m_transMat;
				SHADER.m_spriteShader.SetMatrix(m_mat);
				SHADER.m_spriteShader.DrawTex(&m_frame, Math::Rectangle(0, 0, 100, 60), 1.0f);
			}
		}
	}
	
	//SHADER.m_spriteShader.DrawBox(position[0], position[1], size[0], size[1], &Math::Color(0, 0, 0, 1), true);
}
void Application::DrawButtonText(Button inputButton)
{
	position = inputButton.GetPosition();
	message = inputButton.GetText();
	float scale = inputButton.GetScale();
	size = inputButton.GetSize();
	DrawString(position[0] - size[0], position[1] + size[1] / 2, text, Math::Vector4(1, 0, 1, 1), scale);
	//DrawString(position[0], position[1], text, Math::Vector4(1, 1, 1, 1), scale);
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
	std::pair<float, float> _mouse(inputMouse.x - 640, 360 - inputMouse.y);
	if (_mouse.first >= (position[0] - size[0]) && _mouse.first <= (position[0] + size[0]))
	{
		if (_mouse.second <= (position[1] + size[1]) && _mouse.second >= (position[1] - size[1]))
		{
			SHADER.m_spriteShader.DrawString(_mouse.first, _mouse.second, "CLICK", Math::Vector4(1, 1, 1, 1));
			return true;
		}
	}
	return false;
}
void Application::MenuExecute(Menu& inputMenu)
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
void Application::MenuUpdate(Menu &inputMenu)
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
					if (!inputMenu.IsCD())
					{
						if (m_settingFlg)
						{
							if (m_musicCnt++ < 35)
							{
								inputMenu.EventClick(inputMenu.GetButton(i).SendClickData());
								inputMenu.SetColdown(5);
							}
							else
							{
								inputMenu.EventClick(inputMenu.GetButton(i).SendClickData());
								inputMenu.SetColdown(1);
							}
						}
						else if (!m_lButtonFlg)
						{
							inputMenu.EventClick(inputMenu.GetButton(i).SendClickData());
							inputMenu.SetColdown(30);
						}
					}
				}
			}
		}
		m_lButtonFlg = true;
	}
	else
	{
		m_lButtonFlg = false;
		m_musicCnt = 0;
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
	//__text = to_string(APP.GetInstance().m_fps);
	//SHADER.m_spriteShader.DrawString(-600, 0, _convText, { 1,0,0,1 });
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
	char buffer[1024];
	if (getcwd(buffer, sizeof(buffer)) != nullptr) {
		std::string currentDir(buffer);
		std::string newDir = " dir \"" + currentDir + "\\Data\\Classes\\Header\" /b *.h > temp.txt";
		system(newDir.c_str());
	}
	
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
	std::strcat(_result, "\\Dungeon Meka");

	if (!PathFileExistsA(_result)) {
		// Директория не существует, создаем её
		if (SHCreateDirectoryExA(NULL, _result, NULL) != ERROR_SUCCESS) {
			std::cerr << "Unable to create directory." << std::endl;
			return;
		}
	}
	dataFolderPath = _result;
}

// アプリケーション実行
void Application::Execute()
{
	
	std::vector<std::string> test;
	//===================================================================
	// 初期設定(ウィンドウ作成、Direct3D初期化など)
	//===================================================================
	if (APP.Init(1280, 720) == false) {
		return;
	}
	mainMenu.SetTexture(&m_mainMenuBackGround1);
	settingMenu.SetTexture(&m_settingBack2);
	CreateDataPath();//Create the Path to users data
	LoadMapList();
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
				m_settingFlg = false;
				DWORD st = timeGetTime();
				soundInstance->SetVolume(WindowsData.GetMusicVolume());
				mainMenu.Update();
				SHADER.m_spriteShader.SetMatrix(mainMenu.GetMatrix());
				SHADER.m_spriteShader.DrawTex(mainMenu.GetTexture(), mainMenu.GetRect());
				SHADER.m_spriteShader.SetMatrix(Math::Matrix::CreateTranslation(0, 0, 0));
				SHADER.m_spriteShader.DrawTex(&m_mainMenuBackGround2, Math::Rectangle(0, 0, 1280, 720), 1.0f);
				SHADER.m_spriteShader.SetMatrix(Math::Matrix::CreateTranslation(50, 170, 0));
				SHADER.m_spriteShader.DrawTex(&m_titleLogo, Math::Rectangle(0, 0, 510, 111), 1.0f);
				SHADER.m_spriteShader.SetMatrix(Math::Matrix::CreateTranslation(0, 0, 0));
				//SHADER.m_spriteShader.DrawString(-200, 300, "ダンジョンメーカー", { 1,0,0,1 });
				MenuExecute(mainMenu);
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
				
				SCENE.Init(&WindowsData,dataFolderPath,lastSelectedPath);
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
			SCENE.LoadMap();
			do
			{
				m_settingFlg = false;
				gameSoundInstance->SetVolume(WindowsData.GetMusicVolume());
				Game();
			}while ((m_endFlagWindows != true));
			gameSoundInstance->Stop();
			soundInstance->Resume();
			break;
		case WindowsControl::Setting:
			do
			{
				m_settingFlg = true;
				soundInstance->SetVolume(WindowsData.GetMusicVolume());
				settingMenu.Update();
				SHADER.m_spriteShader.SetMatrix(settingMenu.GetMatrix());
				SHADER.m_spriteShader.DrawTex(settingMenu.GetTexture(), settingMenu.GetRect());
				SHADER.m_spriteShader.SetMatrix(Math::Matrix::CreateTranslation(0, 0, 0));
				SHADER.m_spriteShader.DrawTex(&m_settingBack1, Math::Rectangle(0, 0, 1280, 720), 1.0f);
				MenuExecute(settingMenu);
			} while ((m_endFlagWindows != true));
			break;
		case WindowsControl::Records:
			break;
		case WindowsControl::SelectPlayebleMapMenu:
			lastSelectedPath = mapFolderPath;
			LoadMapList();
			selectPlaybleMapMenu.InitSelectMapPlayeble(playebleMapList, mapFolderPath, dataFolderPath);
			do
			{
				m_settingFlg = false;
				soundInstance->SetVolume(WindowsData.GetMusicVolume());
				selectPlaybleMapMenu.Update();
				MenuExecute(selectPlaybleMapMenu);
			} while ((m_endFlagWindows != true));
			break;
		case WindowsControl::SelectEditerMapMenu:
			lastSelectedPath = mapFolderPath;
			LoadMapList();
			selectEditerMapMenu.InitSelectEditingMap(editerMapList, editerMapFolderPath, dataFolderPath);
			do
			{
				m_settingFlg = false;
				soundInstance->SetVolume(WindowsData.GetMusicVolume());
				selectEditerMapMenu.Update();
				MenuExecute(selectEditerMapMenu);
			} while ((m_endFlagWindows != true));
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