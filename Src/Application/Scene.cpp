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
	if (SC->GetEditMode())
	{
		string _string[3];
		_string[0] ="CurrentEditerMenu ";
		switch (m_editerMenuIndex)
		{
		case EditerSelect::BlockMenu:
			_string[0] += "Block";
			break;
		case EditerSelect::ItemMenu:
			_string[0] += "item";
		case EditerSelect::EnemyMenu:
			_string[0] += "Enemy";
			break;
			break;
		}
		switch (m_editerMenuIndex)
		{
		case EditerSelect::BlockMenu:
			_string[1] = "CurrentBlockType" + std::to_string(m_unitType);
			_string[2] = "CurrentBlockVariant" + std::to_string(m_selectedUnitVariant);
			
			break;
		}
		const char* _text[3] = { _string[0].c_str(),_string[1].c_str() ,_string[2].c_str() };
		DrawString(300, 300, _text[0], { 1,1,1,1 }, 0.5f);
		DrawString(300, 250, _text[1], { 1,1,1,1 }, 0.5f);
		DrawString(300, 200, _text[2], { 1,1,1,1 }, 0.5f);
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
	spriteFont->DrawString(spriteBatch, _wtext, Math::Vector2(_x + 640, -_y + 360), _color,0.0f,{0,0},scale);
	spriteBatch->End();

	//Begin�O��BlendState�𕜌�
	D3D.GetDevContext()->OMSetBlendState(oldBlendState, oldFactor, oldMask);

	//�ꎞ�擾����BlendState����� (������Ȃ��ƎQ�ƃJ�E���g������Ȃ�)
	KdSafeRelease(oldBlendState);

	delete[] _wtext;
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
		for (int i = 0; i < m_item.size(); i++)
		{
			SHADER.m_spriteShader.SetMatrix(m_item[i].GetMatrix());
			SHADER.m_spriteShader.DrawTex(m_item[i].GetTexture(), m_item[i].GetRect());
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
	int _terrainType = m_unitType;
	switch (m_unitType)
	{
	case BlockEditerSelect::Ground:
		switch (buffer)
		{

		case 1:
			_currentTex = &m_groundTex[2];
			break;
		case 3:
			_currentTex = &m_groundTex[1];
			break;
		case 5:
			_currentTex = &m_groundTex[4];
			break;
		case 7:
			_currentTex = &m_groundTex[3];
			break;
		default:
			_currentTex = &m_groundTex[0];
			break;
		}

		break;
		
	case BlockEditerSelect::Ice:
		switch (m_selectedUnitVariant)
		{
		case Surface:
			switch (buffer)
			{

			case 1:
				_currentTex = &m_iceSurfaceTex[2];
				break;
			case 3:
				_currentTex = &m_iceSurfaceTex[1];
				break;
			case 5:
				_currentTex = &m_iceSurfaceTex[4];
				break;
			case 7:
				_currentTex = &m_iceSurfaceTex[3];
				break;
			default:
				_currentTex = &m_iceSurfaceTex[0];
				break;
			}
			break;
		case Inside:
			switch (buffer)
			{

			case 1:
				_currentTex = &m_iceInsideTex[2];
				break;
			case 3:
				_currentTex = &m_iceInsideTex[1];
				break;
			case 5:
				_currentTex = &m_iceInsideTex[4];
				break;
			case 7:
				_currentTex = &m_iceInsideTex[3];
				break;
			default:
				_currentTex = &m_iceInsideTex[0];
				break;
			}
			break;
		}
		break;
	case 3:
		_currentTex = &m_GroundBlockTex;
		break;
	case 4:
		_currentTex = &m_IceWaterBlockTex;
		break;
	default:
		_currentTex = NULL;
		break;
	}

	
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
					m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f + j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f + j * 32.0f, 32.0f, 32.0f, _currentTex, false, float(M_PI) * 0.25f));
					break;
				case 2:
					m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f + j * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
					break;
				case 3:
					m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f - j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f + j * 32.0f, 32.0f, 32.0f, _currentTex, false, float(M_PI) * 0.75f));
					break;
				case 4:
					m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f - j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
					break;
				case 5:
					m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f - j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f - j * 32.0f, 32.0f, 32.0f, _currentTex, false, float(M_PI) * 1.25f));
					break;
				case 6:
					m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f - j * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
					break;
				case 7:
					m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f + j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f - j * 32.0f, 32.0f, 32.0f, _currentTex, false, float(M_PI) * 1.75f));
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
	if(_terrainType==0)
	{ 
		m_blocks.clear();
	}
	

	m_terrain.push_back(TerrainObject({ int((m_point[0].x - 640) / 32) * 32.0f ,(int(-m_point[0].y + 360) / 32) * 32.0f }, buffer, _terrainTypeVector, m_blocks));
	
	//auto _terrain = new ;
	
	
	m_drawStartBool = false;
}

void Scene::SaveStage()
{
	std::ofstream outFile("StageData");
	if (outFile.is_open()) {
		outFile << m_stageType << "\n";
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
	if (inFile.is_open()) {
		int x, y, angle, size, typeBlockSize, _buff;
		std::vector<int> typeBlock;
		std::string line;
		getline(inFile, line, '\n');
		m_stageType = stoi(line);
		getline(inFile, line, '\n');
		size = stoi(line);
		for (int j = 0; j < size; j++)
		{
			typeBlock.clear();
			getline(inFile, line, ',');
			angle = stoi(line);
			getline(inFile, line, ',');
			x = stoi(line);
			getline(inFile, line, ',');
			y = stoi(line);
			getline(inFile, line, '\n');
			typeBlockSize = stoi(line);
			for (int i = 0; i < typeBlockSize; i++)
			{
				getline(inFile, line, ',');
				_buff = stoi(line);
				typeBlock.push_back(_buff);
			}

			m_terrain.push_back(TerrainObject({ x,y }, angle, typeBlock, m_BlockTex));
			getline(inFile, line, '\n');
		}
		
		inFile.close();
	}
}

void Scene::UpdateGameScene()
{
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
	for (int i = 0; i < m_item.size(); i++)
	{
		if (m_player.CollisionToItem(&m_item[i]))
		{
			int _index = m_item[i].GetIndex();
			if ( _index< 3)
			{
				m_keyFlag[_index] = true;
				int _keyType=0;
				for (int j = 0; j < m_keyFlag.size(); j++)
				{
					if (m_keyFlag[j])
					{
						_keyType++;
					}
				}
				if (_keyType == m_keyFlag.size())
				{
					CLEARFLAG = true;////�厖�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I
				}
			}
		}
	}

	m_testCollision = false;
	for (int i = 0; i < m_terrain.size(); i++)
	{
		if (m_terrain[i].OnCollisionRange(m_player.GetPos()))
		{
			auto _blocks = m_terrain[i].GetBlocks();
			for (int j = 0; j < _blocks->size(); j++)
			{
				auto _block = _blocks->at(j);
				m_testCollision = m_player.CollisionToBlock(_block);
				if (m_testCollision)
				{
					m_player.SetOnGroundFlag(true);
				}
			}
		}
	}
	if (!m_player.MovePossible())
	{
		m_player.Stop();
	}
	m_spawner[0].Update();
	m_player.Update();
}

void Scene::UpdateEditScene()
{
	if (GetAsyncKeyState('T'))
	{
		if (!m_controlButtonClick)
		{
			m_editerMenuIndex++;
			if (m_editerMenuIndex >= EditerSelect::COUNTES)
			{
				m_editerMenuIndex = 0;
			}
			m_controlButtonClick = true;
		}
	}
	if (GetAsyncKeyState('Y'))
	{
		if (!m_controlButtonClick)
		{
			m_editerMenuIndex--;
			if (m_editerMenuIndex <0)
			{
				m_editerMenuIndex = EditerSelect::COUNTES-1;
			}
			m_controlButtonClick = true;
		}
	}
	if (GetAsyncKeyState('B'))
	{
		if (!m_controlButtonClick)
		{
			m_selectedUnitVariant++;
			int _maxType = 1;
			switch (m_editerMenuIndex)
			{
			case EditerSelect::BlockMenu:
				_maxType = MaxTypeBlock();
				break;
			case EditerSelect::ItemMenu:
				break;
			case EditerSelect::EnemyMenu:
				break;
			}
			if (m_selectedUnitVariant >= _maxType)
			{
				m_selectedUnitVariant = 0;
			}
			m_controlButtonClick = true;
		}
	}
	if (GetAsyncKeyState('N'))
	{
		if (!m_controlButtonClick)
		{
			m_selectedUnitVariant--;
			int _maxType = 1;
			switch (m_editerMenuIndex)
			{
			case EditerSelect::BlockMenu:
				_maxType = MaxTypeBlock();
				break;
			case EditerSelect::ItemMenu:
				break;
			case EditerSelect::EnemyMenu:
				break;
			}
			if (m_selectedUnitVariant < 0)
			{
				m_selectedUnitVariant = _maxType-1;
			}
			m_controlButtonClick = true;
		}
	}
	if (GetAsyncKeyState('G'))
	{
		if (!m_controlButtonClick)
		{
			m_unitType++;
			m_selectedUnitVariant = 0;
			int _maxType = 1;
			switch (m_editerMenuIndex)
			{
			case EditerSelect::BlockMenu:
				_maxType = BlockEditerSelect::COUNTBES;
				break;
			case EditerSelect::ItemMenu:
				break;
			case EditerSelect::EnemyMenu:
				_maxType = SpawnerSelect::COUNTSS;
				break;
			}
			if (m_unitType >= _maxType)
			{
				m_unitType = 0;
			}
			m_controlButtonClick = true;
		}
	}
	if (GetAsyncKeyState('H'))
	{
		if (!m_controlButtonClick)
		{
			m_unitType--;
			m_selectedUnitVariant = 0;
			int _maxType = 1;
			switch (m_editerMenuIndex)
			{
			case EditerSelect::BlockMenu:
				_maxType = BlockEditerSelect::COUNTBES;
				break;
			case EditerSelect::ItemMenu:
				break;
			case EditerSelect::EnemyMenu:
				break;
			}
			if (m_unitType < 0)
			{
				m_unitType = _maxType-1;
			}
			m_controlButtonClick = true;
		}
	}
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
 			switch (m_editerMenuIndex)
			{
			case BlockMenu:
				CreateTerrainObject();
				break;
			case EnemyMenu:
				CreateSpawn();
				break;
			case ItemMenu:
				break;
			}
		}
	}
	m_blocks.clear();
}

int Scene::MaxTypeBlock()
{
	switch (m_unitType)
	{
	case BlockEditerSelect::Ground:
		return 1;
		break;
	case BlockEditerSelect::Ice:
		return IceBlockSelect::COUNTIBS;
		break;
	default:
		return 1;
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
				break;
			}
		}
		outFile.close();
	}
}

void Scene::LoadSpawn()
{
	std::ifstream inFile("SpawnData");
	if (inFile.is_open()) {
		int charaIndex, type, interval, num, size;
		std::pair<float, float>pos;
		std::string line;
		std::getline(inFile, line, '\n');
		size = stoi(line);
		for (int i = 0; i < size; i++)
		{
			std::getline(inFile, line, '\n');
			charaIndex = stoi(line);
			std::getline(inFile, line, ',');
			pos.first = stoi(line);
			switch (charaIndex)
			{
			case 1:
				std::getline(inFile, line, '\n');
				pos.second = stoi(line);
				m_spawner.push_back(Spawner(charaIndex, pos));
				break;
			case 2:
				std::getline(inFile, line, ',');
				pos.second = stoi(line);
				std::getline(inFile, line, '\n');
				type = stoi(line);
				m_spawner.push_back(Spawner(charaIndex, pos, NULL, type));
				break;
			case 3:
				std::getline(inFile, line, ',');
				pos.second = stoi(line);
				std::getline(inFile, line, ',');
				type = stoi(line);
				std::getline(inFile, line, ',');
				interval = stoi(line);
				std::getline(inFile, line, '\n');
				num = stoi(line);
				m_spawner.push_back(Spawner(charaIndex, pos, NULL, type, interval, num));
				break;
			}
		}
		inFile.close();
	}
}

void Scene::CreateSpawn()
{
	SpawnPos = { 100,200 };
	int charaIndex = 1;
	switch (charaIndex)
	{
	case 1:
		if (m_spawner[0].GetIndex() == 1)
		{
			m_spawner.erase(m_spawner.begin());
			m_spawner.insert(m_spawner.begin(), Spawner(charaIndex, SpawnPos, &m_player));
		}
		else m_spawner.insert(m_spawner.begin(), (Spawner(charaIndex, SpawnPos, &m_player)));
		break;
	default:
		m_spawner.push_back(Spawner(charaIndex, { 200,100 }, NULL, 1, 300, 5));
		break;
	}
}

void Scene::Update()
{

	//
	if (SC->GetCurrentScene() == SceneControlData::Scenes::MainScene)
	{
		if (GetAsyncKeyState('L'))
		{
			if (!lKey)
			{
				SaveStage();
				SaveSpawn();
			}
			lKey = true;
		}
		else m_lKey = false;
		if (GetAsyncKeyState('P'))
		{
			if (!pKey)
			{
				LoadStage();
				LoadSpawn();
			}
			pKey = true;
		}
		else m_pKey = false;
		if (GetAsyncKeyState('T'))
		{
			if (!_tKey)
			{
				m_player.Move(-16 * sqrt(2) * 0.5, 16 * sqrt(2) * 0.5);
				_tKey = true;
			}
		}
		else
		{
			_tKey = false;
		}
		for (size_t i = 0; i < m_terrain.size();)
		{
			if (m_terrain[i].GetBlocks()->empty())
			{
				m_terrain.erase(m_terrain.begin() + i);
			}
			else
			{
				m_terrain[i].Update();
				i++;
			}
			m_player.CollisionClear();
		}
		for (size_t i = 0; i < m_item.size();)
		{
			if (m_item[i].IsDestruct())
			{
				m_item.erase(m_item.begin() + i);
			}
			else
			{
				m_item[i].Update();
				i++;
			}
		}
		GetCursorPos(&m_mouse);
		if (GetAsyncKeyState('E')) SC->SetEditMode(!SC->GetEditMode());
		if (!WC->IsPause())
		{
			if (SC->GetEditMode())
				UpdateEditScene();
			else
				UpdateGameScene();
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
	if (GetAsyncKeyState('Z'))
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
	
	//Test
	
	
	}

void Scene::UpdateMainMenu()
{

}

void Scene::Init(WindowsControlData* WCInput)
{
	// �摜�̓ǂݍ��ݏ���
	ShowCursor(true);
	spriteBatch = new DirectX::SpriteBatch(D3D.GetDevContext());
	spriteFont = new DirectX::SpriteFont(D3D.GetDev(),L"SpriteFont.dat");
	m_inGameSetting.InitInGameSetting();
	WC = WCInput;
	SC = new SceneControlData();
	SC->SetCurrentScene(SceneControlData::Scenes::MainScene);
	m_inGameSetting.AddData(*WC);
	m_BlockTex.Load("Texture/GroundBlock/Ground0.png");;
	m_IceSurfaceBlockTex.Load("Texture/GroundBlock/Snowslice03_03.png");;
	m_IceInsideBlockTex.Load("Texture/GroundBlock/Snowslice27_27.png");;
	//m_GroundBlockTex.Load("Texture/GroundBlock/Groundslice03_03.png");;
	m_IceWaterBlockTex.Load("Texture/GimmickBlock/iceWaterDeepStars.png");;
	charaRect = Math::Rectangle(0, 0, 32, 32);
	m_playerTex.Load("Texture/Object/RedBox.png");
	m_groundTex[0].Load("Texture/GroundBlock/Ground0.png");
	m_groundTex[1].Load("Texture/GroundBlock/Ground1.png");
	m_groundTex[2].Load("Texture/GroundBlock/Ground2.png");
	m_groundTex[3].Load("Texture/GroundBlock/Ground3.png");
	m_groundTex[4].Load("Texture/GroundBlock/Ground4.png");

	m_iceInsideTex[0].Load("Texture/GroundBlock/InsideIce.png");
	m_iceInsideTex[1].Load("Texture/GroundBlock/Ice1.png");
	m_iceInsideTex[2].Load("Texture/GroundBlock/Ice2.png");
	m_iceInsideTex[3].Load("Texture/GroundBlock/Ice3.png");
	m_iceInsideTex[4].Load("Texture/GroundBlock/Ice4.png");

	m_iceSurfaceTex[0].Load("Texture/GroundBlock/InsideIce.png");
	m_iceSurfaceTex[1].Load("Texture/GroundBlock/Ice1.png");
	m_iceSurfaceTex[2].Load("Texture/GroundBlock/Ice2.png");
	m_iceSurfaceTex[3].Load("Texture/GroundBlock/Ice3.png");
	m_iceSurfaceTex[4].Load("Texture/GroundBlock/Ice4.png");
	//
	tmpTex.CreateRenderTarget(1280, 720);
	//m_blocks.push_back(Block(0, 0, 32, 32, &m_BlockTex, false,   0));
	m_lKey = false;
	m_pKey = false;
	
	_texture[0].Load("Texture/Item/Key1.png");
	_key = Item({0,0},&_texture[0],0 );
	m_item.push_back(_key);
	_texture[1].Load("Texture/Item/Key2.png");
	_key = Item({ 0,-64 }, &_texture[1], 1);
	m_item.push_back(_key);
	_texture[2].Load("Texture/Item/Key3.png");
	_key = Item({ 0,-128 }, &_texture[2], 2);
	m_item.push_back(_key);

	m_spawner.push_back(Spawner(1, SpawnPos, &m_player));
}

void Scene::Release()
{
	// �摜�̉������
	m_BlockTex.Release();
	delete SC;
	tmpTex.Release();
}

void Scene::ImGuiUpdate()
{
	//return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// �f�o�b�O�E�B���h�E
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
		if (m_testCollision)
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
