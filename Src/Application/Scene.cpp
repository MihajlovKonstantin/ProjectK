#include "main.h"
#include "Scene.h"
#include "WindowsEnum.h"
void Scene::Draw2D()
{
	
	D3D.SetBackBuffer();
	SHADER.m_spriteShader.SetMatrix(matrix);
	SHADER.m_spriteShader.DrawTex(&tmpTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);
	
	if (WC->IsPause())
	{

		for (int i = 0; i < m_inGameSetting.GetButtonsCNT(); i++)
		{
			//DrawButton(m_inGameSetting.GetButton(i));
		}
		for (int i = 0; i < m_inGameSetting.GetButtonsCNT(); i++)
		{
			DrawButtonText(m_inGameSetting.GetButton(i));
		}
	}
}

void Scene::DrawButton(Button inputButton)
{
	matrix = Math::Matrix::CreateTranslation(0, 0, 0);
	SHADER.m_spriteShader.SetMatrix(matrix);
	size = inputButton.GetSize();
	position = inputButton.GetPosition();
	SHADER.m_spriteShader.DrawBox(position[0], position[1], size[0], size[1], &Math::Color(0.8, 0.6, 1, 1), true);
}

void Scene::DrawButtonText(Button inputButton)
{
	position = inputButton.GetPosition();
	str = inputButton.GetText();
	float scale = inputButton.GetScale();
	size = inputButton.GetSize();
	DrawString(position[0]-size[0], position[1]+size[1]/2, charStr, Math::Vector4(1, 0, 1, 1), scale);
}

void Scene::DrawString(float _x, float _y, const char _text[], const Math::Vector4& _color, float scale)
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
	spriteFont->DrawString(spriteBatch, _wtext, Math::Vector2(_x + 640, -_y + 360), _color,0.0f,{0,0},scale);
	spriteBatch->End();

	//Begin前のBlendStateを復元
	D3D.GetDevContext()->OMSetBlendState(oldBlendState, oldFactor, oldMask);

	//一時取得したBlendStateを解放 (解放しないと参照カウントが減らない)
	KdSafeRelease(oldBlendState);

	delete[] _wtext;
}

void Scene::DrawGraph()
{

}

void Scene::DrawTexts()
{

}

void Scene::DrawMainScene(Math::Color inputColor)
{

}

void Scene::SetResumeWindows()
{
	SC->SetCurrentScene(SceneControlData::Scenes::MainScene);
	WC->Resume();
}

void Scene::DynamicDraw2D()
{
	tmpTex.ClearRenerTarget(Math::Color(0,0, 0, 1));
	tmpTex.SetRenderTarget();
	
	if (WC->IsPause())
	{
		for (int i = 0; i < m_inGameSetting.GetButtonsCNT(); i++)
		{
			DrawButton(m_inGameSetting.GetButton(i));
		}
		for (int i = 0; i < m_inGameSetting.GetButtonsCNT(); i++)
		{
			//DrawButtonText(m_inGameSetting.GetButton(i));
		}
	}
	else
	{
		D3D.SetBlendState(BlendMode::Alpha);
		SHADER.m_spriteShader.SetMatrix(m_player.GetMatrix());
		SHADER.m_spriteShader.DrawTex(m_player.GetTexture(), charaRect, 1.0f);
		for (auto block : m_blocks)
		{
			//SHADER.m_spriteShader.SetMatrix(block.GetMatrix());
			//SHADER.m_spriteShader.DrawTex(block.GetTexture(), block.GetRectangle());

		}
		for (auto _terrainObject : m_terrain)
		{
			auto _blocks = *_terrainObject.GetBlocks();
			if (!_blocks.empty())
			{
				for (int i = 0; i < _blocks.size(); i++)
				{
					SHADER.m_spriteShader.SetMatrix(_blocks[i].GetMatrix());
					SHADER.m_spriteShader.DrawTex(_blocks[i].GetTexture(), _blocks[i].GetRectangle());
				}
			}
		}

	}
	
}

void Scene::CreateTerrainObject()
{
	float __dx = int((m_point[1].x - 640) / 32.0f) * 32.0f - int((m_point[0].x - 640) / 32.0f) * 32.0f;
	(__dx < 1) && (__dx > -1) ? __dx = 32.0f : __dx = __dx;
	float __dy = int((-m_point[1].y + 360) / 32.0f) * 32.0f - int((-m_point[0].y + 360) / 32.0f) * 32.0f;
	(__dy < 1) && (__dy > -1) ? __dy = 32.0f : __dy = __dy;
	float radian;
	KdTexture* _currentTex;
	switch (BlockKinds)
	{
	case 1:
		_currentTex = &m_BlockTex;
		break;
	case 2:
		_currentTex = &m_IceBlockTex;
		break;
	}

	int i;
	if ((__dx == 32.0f) && (__dy == 32.0f))
	{
		i = 1;
		radian = 0;
	}
	else
	{
		i = sqrt(pow(__dx, 2) + pow(__dy, 2)) / 32.0f;
		radian = atan2(__dy, __dx);
	}
	if (radian < 0)
	{
		radian += float(M_PI) * 2.0f;
	}
	int buffer;
	if (radian <= float(M_PI) / 16.0f)
	{
		radian = 0;
	}
	if ((radian > float(M_PI) / 16.0f) && (radian<float(M_PI) * 0.5f - float(M_PI) / 16.0f))
	{
		radian = float(M_PI) * 0.25f;
	}
	if ((radian >= float(M_PI) * 0.5f - float(M_PI) / 16.0f) && ((radian <= float(M_PI) * 0.5f + float(M_PI) / 16.0f)))
	{
		radian = float(M_PI) * 0.5f;
	}
	if (((radian > float(M_PI) * 0.5f + float(M_PI) / 16.0f)) && (radian<float(M_PI) / 16.0f * 15.0f))
	{
		radian = float(M_PI) * 0.75f;
	}
	if ((radian >= float(M_PI) / 16.0f * 15.0f) && (radian <= float(M_PI) / 16.0f * 17.0f))
	{
		radian = float(M_PI);
	}
	if ((radian > float(M_PI) / 16.0f * 17.0f) && (radian<float(M_PI) * 1.5f - float(M_PI) / 16.0f))
	{
		radian = float(M_PI) * 1.25f;
	}
	if ((radian >= float(M_PI) * 1.5f - float(M_PI) / 16.0f) && (radian <= float(M_PI) * 1.5f + float(M_PI) / 16.0f))
	{
		radian = float(M_PI) * 1.5f;
	}
	if ((radian > float(M_PI) * 1.5f + float(M_PI) / 16.0f) && ((radian <= float(M_PI) * 2.0f - float(M_PI) / 16.0f)))
	{
		radian = float(M_PI) * 1.75f;
	}
	if ((radian >= float(M_PI) * 2.0f - float(M_PI) / 16.0f) && (radian <= float(M_PI) * 2.0f))
	{
		radian = 2.0f * float(M_PI);
	}
	buffer = int(radian / (float(M_PI) * 0.25f));
	int _terrainType = BlockKinds;
	std::vector<int> _terrainTypeVector;
	m_blocks.clear();
	for (int j = 0; j < i; j++)
	{
		_terrainTypeVector.push_back(_terrainType);
		{
			switch (buffer)
			{
			case 0:
				m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f + j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 1:
				m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f + j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f + j * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 2:
				m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f + j * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 3:
				m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f - j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f + j * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 4:
				m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f - j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 5:
				m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f - j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f - j * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 6:
				m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f - j * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 7:
				m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f + j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f - j * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 8:
				m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f + j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			}
		}
	}
	
	for (int i = 0; i < (m_terrain.size()) && (!m_terrain.empty()); i++)
	{
		for (int j = 0; (j < m_blocks.size()) && (!m_blocks.empty()); j++)
		{
			if (m_terrain[i].IsContain())
			{
				m_terrain[i].Replace(m_blocks[j]);
			}
		}
	}

	m_terrain.push_back(TerrainObject({ int((m_point[0].x - 640) / 32) * 32.0f ,(int(-m_point[0].y + 360) / 32) * 32.0f }, buffer, _terrainTypeVector, m_blocks));
	
	//auto _terrain = new ;
	
	
	m_drawStartBool = false;
}

void Scene::SaveStage()
{
	std::ofstream outFile("StageData");
	if (outFile.is_open()) {
		//outFile << m_player.GetPlayerPos().first << ",";
		//outFile << m_player.GetPlayerPos().second << "\n";
		outFile << m_terrain.size() << "\n";
		for (int i = 0; i < m_terrain.size(); i++)
		{
			outFile << m_terrain[i].GetAngle() << ",";
			outFile << m_terrain[i].GetGPOS().first << ",";
			outFile << m_terrain[i].GetGPOS().second << ",";
			auto _typeBlock = m_terrain[i].GetTypeBlock();
			int _typeBlockItr = _typeBlock.size();
			outFile << _typeBlockItr << "\n";
			for (int j = 0; j < _typeBlockItr; j++)
			{
				outFile << _typeBlock[j] << ",";
			}
			outFile << "\n";
		}
		outFile.close();
	}
}

void Scene::LoadStage()
{
	std::ifstream inFile("StageData");
	m_terrain.clear();
	if (inFile.is_open()) {
		//TerrainObject example
		int x, y, angle, size, typeBlockSize, _buff;
		KdTexture* _Tex;
		std::vector<int> typeBlock;
		std::string line;
		std::getline(inFile, line, '\n');
		size = stoi(line);
		for (int j = 0; j < size; j++)
		{
			std::getline(inFile, line, ',');
			angle = stoi(line);
			std::getline(inFile, line, ',');
			x = stoi(line);
			std::getline(inFile, line, ',');
			y = stoi(line);
			std::getline(inFile, line, '\n');
			typeBlockSize = stoi(line);
			typeBlock.clear();
			for (int i = 0; i < typeBlockSize; i++)
			{
				std::getline(inFile, line, ',');
				_buff = stoi(line);
				typeBlock.push_back(_buff);
			}
			switch (_buff)
			{
			case 1:
				_Tex = &m_BlockTex;
				break;
			case 2:
				_Tex = &m_IceBlockTex;
				break;
			}
			m_terrain.push_back(TerrainObject({ x,y }, angle, typeBlock, *_Tex));
			std::getline(inFile, line, '\n');
		}
		
		inFile.close();
	}
}

void Scene::SaveSpawn()
{
	std::ofstream outFile("SpawnData");
	if (outFile.is_open()) {
		outFile << m_spawner.size() << "\n";
		for (int i = 0; i < m_spawner.size(); i++)
		{
			outFile << m_spawner[i].GetIndex() << "\n";
			outFile << m_spawner[i].GetCharaPos().first << ",";
			switch (m_spawner[i].GetIndex())
			{
			case 1:
				outFile << m_spawner[i].GetCharaPos().second << "\n";
				break;
			case 2:
				outFile << m_spawner[i].GetCharaPos().second << ",";
				outFile << m_spawner[i].GetType() << "\n";
				break;
			case 3:
				outFile << m_spawner[i].GetCharaPos().second << ",";
				outFile << m_spawner[i].GetType() << ",";
				outFile << m_spawner[i].GetInterval() << ",";
				outFile << m_spawner[i].GetNum() << "\n";
			}
		}
	}
	outFile.close();
}

void Scene::EnemyPosition()
{
}

void Scene::LoadSpawn()
{
	std::ifstream inFile("SpawnData");
	m_spawner.clear();
	if (inFile.is_open()) {
		int charaIndex, enemyType, interval, num, size;
		std::pair<float, float> pos;
		std::string line;
		std::getline(inFile, line, '\n');
		size = stoi(line);
		for (int i = 0; i < size; i++)
		{
			std::getline(inFile, line, '\n');
			charaIndex = stoi(line);
			std::getline(inFile, line, ',');
			pos.first = stof(line);
			switch (charaIndex)
			{
			case 1:
				std::getline(inFile, line, '\n');
				pos.second = stof(line);
				m_spawner.push_back(Spawner(charaIndex, pos, &m_player));
				break;
			case 2:
				std::getline(inFile, line, ',');
				pos.second = stof(line);
				std::getline(inFile, line, '\n');
				enemyType = stoi(line);
				//m_enemy.push_back(NPC(index, pos, enemyType));
				m_spawner.push_back(Spawner(charaIndex, pos, NULL, enemyType));
				break;
			case 3:
				std::getline(inFile, line, ',');
				pos.second = stof(line);
				std::getline(inFile, line, ',');
				enemyType = stoi(line);
				std::getline(inFile, line, ',');
				interval = stoi(line);
				std::getline(inFile, line, '\n');
				num = stoi(line);
				//m_enemy.push_back(NPC(index, pos, enemyType, interval, num));
				m_spawner.push_back(Spawner(charaIndex, pos, NULL, enemyType, interval, num));
				break;
			}
		}
	}
	inFile.close();
}

void Scene::CharaPosition()
{
	switch (index)
	{
	case 1:
		if (m_spawner.size() > 0)
		{
			m_spawner.erase(m_spawner.begin());
			m_spawner.insert(m_spawner.begin(), Spawner(index, spawnPos));
		}
		else m_spawner.insert(m_spawner.begin(), Spawner(index, spawnPos));
		break;
	default:
		m_spawner.push_back(Spawner(index, spawnPos, NULL, 1, 300, 5));
		break;
	}
}

//void Scene::Spawn()
//{
//	switch (index)
//	{
//	case 1:
//		m_player.SetInit(spawnPos);
//		break;
//	}
//}

void Scene::Update()
{
	//
	if (!WC->IsPause())
	{
		_test = false;
		for (int i = 0; i < m_terrain.size(); i++)
		{
			if (m_terrain[i].OnCollisionRange(m_player.GetPos()))
			{
				auto _blocks = m_terrain[i].GetBlocks();
				for (int j = 0;j<_blocks->size();j++)
				{
					auto _block = _blocks->at(j);
					test = m_player.CollisionToBlock(_block);
					if(test)
					{
						m_player.SetOnGroundFlag(true);
						_test = true;
					}
				}
			}
		}
		for (int i = 0;i<m_blocks.size();i++)
		{
			test = m_player.CollisionToBlock(m_blocks[i]);
			if (test)
			{
				m_player.SetOnGroundFlag(true);
				_test = true;
			}
			m_blocks[i].Update();
		}
		if (!m_player.MovePossible())
		{
			m_player.Stop();
		}
		if (GetAsyncKeyState('L'))
		{
			if (!lKey)
			{
				SaveStage();
				SaveSpawn();
				lKey = true;
			}
		}
		else lKey = false;
		if (GetAsyncKeyState('P'))
		{
			if (!pKey)
			{
				LoadStage();
				LoadSpawn();
				pKey = true;
			}
		}
		else pKey = false;

		if (GetAsyncKeyState('Q'))EditerMenu = BlockMenu;
		if (GetAsyncKeyState('W'))EditerMenu = CharaMenu;
		if (GetAsyncKeyState('E'))EditerMenu = ItemMenu;

		if (GetAsyncKeyState('K') & 0x8000)BlockKinds = 1;
		if (GetAsyncKeyState('J') & 0x8000)BlockKinds = 2;

		if (GetAsyncKeyState('I') & 0x8000)index = 1;
		if (GetAsyncKeyState('U') & 0x8000)index = 2;
		if (GetAsyncKeyState('Y') & 0x8000)index = 3;
		m_player.Update();
		if (GetAsyncKeyState(VK_LEFT))
		{
			m_player.SetDirection(Direction::Left);
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			m_player.SetDirection(Direction::Right);
		}
		else
		{
			m_player.SetDirection(Direction::Stand);
		}
		GetCursorPos(&m_mouse);
		if (GetAsyncKeyState(VK_SPACE))
		{
			if (!m_drawStartBool)
			{
				m_point[0] = m_mouse;
			}  
			m_drawStartBool = true;
		}
		else
		{
			if (m_drawStartBool)
			{
				m_point[1] = m_mouse;
				switch (EditerMenu)
				{
				case BlockMenu:
					CreateTerrainObject();
					break;
				case CharaMenu:
					
					if (GetAsyncKeyState('A') & 0x8000)
					{
						if (GetAsyncKeyState(VK_LBUTTON))
						{
							if (!mouseFlg)
							{
								mouseFlg = true;
								spawnPos.first = mouse.x - 640 - 8;
								spawnPos.second = -mouse.y + 360 + 32;
								CharaPosition();
							}
						}
						else mouseFlg = false;
					}
					break;
				case ItemMenu:
					break;
				}
			}
		}
		
		m_blocks.clear();
		for (size_t i = 0;i<m_terrain.size();)
		{
			if (m_terrain[i].GetBlocks()->empty())
			{
 				m_terrain.erase(m_terrain.begin()+i);
			}
			else
			{
				m_terrain[i].Update();
				i++;
			}
			
		}
	}
	GetCursorPos(&mouse);
	if (GetAsyncKeyState(VK_TAB))
	{
		if ( m_controlButtonClick == false)
			
			switch(SC->GetCurrentScene())
			{
			case SceneControlData::Scenes::MainScene:
				SC->SetCurrentMenu(SceneControlData::Menus::SettingMenu);
				SC->SetCurrentScene(SceneControlData::Scenes::MenuScene);
				WC->PauseGame();
				m_controlButtonClick = true;
				break;
			case SceneControlData::Scenes::MenuScene:
				WC->Resume();
				SC->SetCurrentScene(SceneControlData::Scenes::MainScene);
				m_controlButtonClick = true;
				break;
			}
	}
	else
	{
		m_controlButtonClick = false;
	}
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		switch (SC->GetCurrentScene())
		{
		case SceneControlData::Scenes::MainScene:

			break;
		case SceneControlData::Scenes::MenuScene:
			for (int i = 0; i < m_inGameSetting.GetButtonsCNT(); i++)
			{
				if (ClickButton(mouse, m_inGameSetting.GetButton(i)) == true)
				{
					m_inGameSetting.EventClick(m_inGameSetting.GetButton(i).SendClickData());
				}
			}
			break;
		}
	}
	m_player.CollisionClear();
	//Test
}

void Scene::UpdateMainMenu()
{

}

void Scene::Init(WindowsControlData* WCInput)
{
	// 画像の読み込み処理
	ShowCursor(true);
	spriteBatch = new DirectX::SpriteBatch(D3D.GetDevContext());
	spriteFont = new DirectX::SpriteFont(D3D.GetDev(),L"SpriteFont.dat");
	m_inGameSetting.InitInGameSetting();
	WC = WCInput;
	SC = new SceneControlData();
	SC->SetCurrentScene(SceneControlData::Scenes::MainScene);
	m_inGameSetting.AddData(*WC);
	m_BlockTex.Load("Texture/Object/RedBox.png");;
	m_IceBlockTex.Load("Texture/Snowslice03_03.png");;
	charaRect = Math::Rectangle(0, 0, 32, 32);
	//
	tmpTex.CreateRenderTarget(1280, 720);
	//m_player.SetDirection(Direction::Right);
	m_blocks.push_back(Block(0, 0, 32, 32, &m_BlockTex, false,   0));
	lKey = false;
	pKey = false;
	mouseFlg = false;
	//playerHp = 3;
	//m_player.SetPlayerPos(-999, 0);
}

void Scene::Release()
{
	// 画像の解放処理
	m_BlockTex.Release();
	delete SC;
	tmpTex.Release();
}

void Scene::ImGuiUpdate()
{
	//return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
		if (test)
		{
			ImGui::Text("On Groud");
			
		}
		else
		{
			ImGui::Text("Fly");
		}
		ImGui::Text("%d", m_player.GetDirection());
		ImGui::Text("%f", m_player.GetAngle());
		ImGui::Text("Mouse x %d", m_mouse.x);
		ImGui::Text("Mouse y  %d", m_mouse.y);
		ImGui::Text("spawnPos x  %f", spawnPos.first);
		ImGui::Text("spawnPos y  %f", spawnPos.second);
		ImGui::Text("EditerMenu  %d", EditerMenu);
		ImGui::Text("index  %d",index);
	}
	ImGui::Text("%f %f", m_player.GetPos().first, m_player.GetPos().second);
	ImGui::End();
}

bool Scene::ClickButton(POINT inputMouse, Button inputButton)
{
	size = inputButton.GetSize();
	position = inputButton.GetPosition();
	if ((inputMouse.x - 640) >= (position[0] - size[0]) && (inputMouse.x - 640) <= (position[0] + size[0]*1.05))
	{
		if ((360 - inputMouse.y) <= (position[1] + size[1]/2) && (360 - inputMouse.y) >= (position[1] - size[1]*2))
		{
			SHADER.m_spriteShader.DrawString(mouse.x-640, 360-mouse.y, "CLICK", Math::Vector4(1, 1, 1, 1));
			return true;
		}
	}
	return false;
}
