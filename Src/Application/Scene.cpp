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
		case EditerSelect::CharaMenu:
			_string[0] += "Chara";
			break;
			break;
		}
		switch (m_editerMenuIndex)
		{
		case EditerSelect::BlockMenu:
			_string[1] = "CurrentBlockType ";
			switch (m_unitType)
			{
			case 0:
				_string[1] += "Void";
				break;
			case BlockEditerSelect::Ground:
				_string[1] += "Ground";
				break;
			case BlockEditerSelect::Ice:
				_string[1] += "Ice";
				break;
			case BlockEditerSelect::IceWater:
				_string[1] += "IceWater";
			}
			_string[2] = "CurrentBlockVariant ";
			switch (m_selectedUnitVariant)
			{
			case 0:
				_string[2] += "Base";
				break;
			case 1:
				if (m_unitType == BlockEditerSelect::Ice)
				{
					_string[2] += "InsideIce";
				}
			}
			break;
		case EditerSelect::ItemMenu:
			_string[1] = "CurrentItemType ";
			switch (m_unitType)
			{
			case ItemSelect::Key:
				_string[1] += "Key";
				break;
			}
			_string[2] = "CurrentItemVariant";
			switch (m_selectedUnitVariant)
			{
			case 0:
				_string[2] += "Base";
			default:
				if (m_unitType == ItemSelect::Key)
				{
					_string[2] = "CurrentItemVariant";
					if (m_selectedUnitVariant == KeySelect::Yellow)
						_string[2] = "Yellow";
					if (m_selectedUnitVariant == KeySelect::Red)
						_string[2] = "Red";
					if (m_selectedUnitVariant == KeySelect::Blue)
						_string[2] = "Blue";
				}
			}
			break;
		case EditerSelect::CharaMenu:
			_string[1] = "CurrentCharaType ";
			switch (m_unitType)
			{
			case SpawnerSelect::Player:
				_string[1] += "Player";
				break;
			case SpawnerSelect::Enemy:
				_string[1] += "Enemy";
				break;
			case SpawnerSelect::Enemys:
				_string[1] += "Enemys";
				break;
			}
			if (m_unitType != SpawnerSelect::Player)
			{
				_string[2] = "CurrentEnemyVariant ";
				switch (m_selectedUnitVariant)
				{
				case EnemySelect::Slime:
					_string[2] += "Slime";
					break;
				case  EnemySelect::SnowBall:
					_string[2] += "SnowBall";
					break;
				}
			}
		}
		const char* _text[3] = { _string[0].c_str(),_string[1].c_str() ,_string[2].c_str() };
		DrawString(300, 300, _text[0], { 0, 0, 0, 1 }, 0.5f);
		DrawString(300, 250, _text[1], { 0, 0, 0, 1 }, 0.5f);
		DrawString(300, 200, _text[2], { 0, 0, 0, 1 }, 0.5f);
		
	}
	
	if (CLEARFLAG)
	{
		DrawString(-300, 250, "CLEAR", { 1,0,0,1 }, 2.0f);
	}
	else
	{
		if (m_stageType == 1)
		{
			DrawString(-300, 300, m_clearExpress, { 1,0,0,1 }, 2.0f);

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
	DrawString(position[0]-size[0], position[1]+size[1]/2, charStr, Math::Vector4(0, 0, 0, 1), scale);
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
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::CreateTranslation(0, 0, 0));
	SHADER.m_spriteShader.DrawTex(&m_backGround, Math::Rectangle(0, 0, 1280, 720));
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
		SHADER.m_spriteShader.DrawTex(m_player.GetTexture(), m_player.GetRect(), 1.0f);
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
		_currentTex = &m_iceWaterBlockTex[0];
		break;
	default:
		_currentTex = NULL;
		break;
	}

	
	std::vector<int> _terrainTypeVector;
	std::vector<int> _terrainVarVector;
	m_blocks.clear();
	for (int j = 0; j < i; j++)
	{
		_terrainTypeVector.push_back(_terrainType);
		_terrainVarVector.push_back(m_selectedUnitVariant);
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
		m_blocks[j].SetScroll(&m_scroll);
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
	

	m_terrain.push_back(TerrainObject({ int((m_point[0].x - 640) / 32) * 32.0f ,(int(-m_point[0].y + 360) / 32) * 32.0f }, buffer, _terrainTypeVector,_terrainVarVector, m_blocks));
	m_terrain[m_terrain.size() - 1].SetScroll(&m_scroll);
	//auto _terrain = new ;
	
	
	m_drawStartBool = false;
}

void Scene::CreateItem()
{
	std::pair<float, float>_pos = { m_point[0].x-640 ,-m_point[0].y+360 };
	switch (m_unitType)
	{
	case ItemSelect::Key:
		switch (m_selectedUnitVariant)
		{
		case KeySelect::Yellow:
			_lastItem = Item(_pos, &m_keyTexture[0], 0);
			m_item.push_back(_lastItem);
			break;
		case KeySelect::Blue:
			_lastItem = Item(_pos, &m_keyTexture[2], 2);
			m_item.push_back(_lastItem);
			break;
		case KeySelect::Red:
			_lastItem = Item(_pos, &m_keyTexture[1], 1);
			m_item.push_back(_lastItem);
			break;
		}
		break;
	}
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
			auto _varBlock = m_terrain[i].GetVarBlock();
			int _typeBlockItr = _typeBlock.size();
			outFile << _typeBlockItr << "\n";
			for (int j = 0; j < _typeBlockItr; j++)
			{
				outFile << _typeBlock[j] << ",";
			}
			outFile << "\n";
			for (int j = 0; j < _typeBlockItr; j++)//!
			{
				outFile << _varBlock[j] << ",";
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
		std::vector<int> _varBlock;
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
			for (int i = 0; i < typeBlockSize; i++)
			{
				getline(inFile, line, ',');
				_buff = stoi(line);
				_varBlock.push_back(_buff);
			}

			m_terrain.push_back(TerrainObject({ x,y }, angle, typeBlock,_varBlock, &m_blockLiblary));
			m_terrain[m_terrain.size() - 1].SetScroll(&m_scroll);
			getline(inFile, line, '\n');
		}
		
		inFile.close();
	}
}

void Scene::UpdateGameScene()
{
	m_scroll = m_player.GetGPos();
	if (m_stageType == 1)
	{
		m_clearState[1] = m_keyFlag.size();
	}

	
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (!m_rightFlg)
		{
			m_leftFlg = true;
			m_player.SetDirection(Direction::Left);
		}
	}
	else 
	{
		m_leftFlg = false;
		m_player.SetDirection(Direction::Stand);
	}

	
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (!m_leftFlg)
		{
			m_rightFlg = true;
			m_player.SetDirection(Direction::Right);
		}	
	}
	else m_rightFlg = false;
	
	
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (!m_jumpFlg)
		{
 			m_player.Jump();
			m_jumpFlg = true;
		}
	}
	else m_jumpFlg = false;
	for (int i = 0; i < m_item.size(); i++)
	{
		if (m_player.CollisionToItem(&m_item[i]))
		{
			int _index = m_item[i].GetIndex();
			if ( _index< 3)
			{
				m_keyFlag[_index] = true;
				m_clearState[0] = 0;
				for (int j = 0; j < m_keyFlag.size(); j++)
				{
					
					if (m_keyFlag[j])
					{
						m_clearState[0]++;
					}
				}
				if (m_clearState[0] == m_clearState[1])
				{
					CLEARFLAG = true;////�厖�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I
				}
			}
		}
	}
	if (m_stageType == 1)
	{
		m_clearStateString = to_string(m_clearState[0]) + "/" + to_string(m_clearState[1]);
	}

	m_testCollision = false;
	for (int i = 0; i < m_terrain.size(); i++)
	{
		if (m_terrain[i].OnCollisionRange(m_player.GetGPos()))
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
	for (int i = 0; i < m_spawner.size(); i++)
	{
		m_spawner[i].Update();
	}
	if (m_stageType == 0)
	{
		if (m_player.GetPos().second >= 220)
		{
			CLEARFLAG = true;
		}
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
			m_scroll.first--;
			if (m_scroll.first < m_scrollMax[0])
			{
				m_scrollMax[0] = m_scroll.first;
			}
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_scroll.first++;
		if (m_scroll.first > m_scrollMax[1])
		{
			m_scrollMax[1] = m_scroll.first;
		}
	}
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
				_maxType = MaxTypeBlock(m_unitType);
				break;
			case EditerSelect::ItemMenu:
				_maxType = MaxTypeItem();
				break;
			case EditerSelect::CharaMenu:
				_maxType = MaxTypeEnemy();
				break;
			}
			if (m_selectedUnitVariant >= _maxType)
			{
				m_selectedUnitVariant = 0;
			}
			m_controlButtonClick = true;
		}
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_scroll.first-=5;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_scroll.first += 5;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		m_scroll.second += 5;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_scroll.second -= 5;
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
				_maxType = MaxTypeBlock(m_unitType);
				break;
			case EditerSelect::ItemMenu:
				_maxType = MaxTypeItem();
				break;
			case EditerSelect::CharaMenu:
				_maxType = MaxTypeEnemy();
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
			case EditerSelect::CharaMenu:
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
			case EditerSelect::CharaMenu:
				_maxType = SpawnerSelect::COUNTSS;
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
				m_drawStartBool = false;
				break;
			case CharaMenu:
				CreateSpawn();
				m_drawStartBool = false;
				break;
			case ItemMenu:
				CreateItem();
				m_drawStartBool = false;
				break;
			}
		}
	}
	
	
	if (GetAsyncKeyState(VK_LEFT))
	{
		//m_scroll.first--;
		if (m_scroll.first < m_scrollMax[0])
		{
			//m_scrollMax[0] = m_scroll.first;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		//m_scroll.first++;
		if (m_scroll.first > m_scrollMax[1])
		{
			//m_scrollMax[1] = m_scroll.first;
		}
	}
	m_blocks.clear();
}

int Scene::MaxTypeBlock(int index)
{
	switch (index)
	{
	case BlockEditerSelect::Ground:
		return 1;
		break;
	case BlockEditerSelect::Ice:
		return IceBlockSelect::COUNTIBS;
		break;
	default:
		return 1;
		break;
	}
}
int Scene::MaxTypeItem()
{
	switch(m_unitType)
	{
	case ItemSelect::Key:
		return KeySelect::COUNTKS;
		break;
	default:
		return 1;
		break;
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
				break;
			}
		}
		outFile.close();
	}
}

void Scene::LoadSpawn()
{
	m_spawner.clear();
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
				m_spawner.push_back(Spawner(charaIndex, pos, &m_player));
				break;
			case 2:
				std::getline(inFile, line, ',');
				pos.second = stoi(line);
				std::getline(inFile, line, '\n');
				type = stoi(line);
				m_spawner.push_back(Spawner(charaIndex, pos, &m_player, &m_terrain, type));
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
				m_spawner.push_back(Spawner(charaIndex, pos, &m_player, &m_terrain, type, interval, num));
				break;
			}
		}
		inFile.close();
	}
}

void Scene::CreateSpawn()
{
	/*if (m_spawner.empty())
	{
		m_spawner.push_back(Spawner(0, { 0,0 }, NULL));
	}*/
	SpawnPos.first = m_point[0].x-640;
	SpawnPos.second = -m_point[0].y+360;
	int charaIndex = m_unitType;
	switch (charaIndex)
	{
	case SpawnerSelect::Player:
		if (m_spawner.size() != 0)
		{
			if(m_spawner[0].GetIndex() == 1)m_spawner.erase(m_spawner.begin());
			m_spawner.insert(m_spawner.begin(), (Spawner(charaIndex, SpawnPos, &m_player)));
		}
		else m_spawner.push_back(Spawner(charaIndex, SpawnPos, &m_player));
		break;
	case SpawnerSelect::Enemy:
		m_spawner.push_back(Spawner(charaIndex, SpawnPos, &m_player, &m_terrain, m_selectedUnitVariant));
		break;
	default:
		m_spawner.push_back(Spawner(charaIndex, SpawnPos, &m_player, &m_terrain, m_selectedUnitVariant, 300, 5));
		break;
	}
}

void Scene::StopMusic()
{
	//soundInstance->Pause();
}

int Scene::MaxTypeEnemy()
{
	switch (m_unitType)
	{
	case SpawnerSelect::Player:
		return 0;
		break;
	case SpawnerSelect::Enemy:
		return EnemySelect::COUNTENS;
		break;
	case SpawnerSelect::Enemys:
		return EnemySelect::COUNTENS;
		break;
	}
}

void Scene::Update()
{
	//if(soundInstance.IsPause())
	// {
	//	soundInstance.Resume();
	// }
	//
	if (SC->GetCurrentScene() == SceneControlData::Scenes::MainScene)
	{
		if (GetAsyncKeyState('L'))
		{
			if (!m_lKey)
			{
				SaveStage();
				SaveSpawn();
			}
			m_lKey = true;
		}
		else m_lKey = false;
		if (GetAsyncKeyState('P'))
		{
			if (!m_pKey)
			{
				LoadStage();
				LoadSpawn();
			}
			m_pKey = true;
		}
		else m_pKey = false;
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
		m_mouse.x += 16+m_scroll.first;
		m_mouse.y += 12-m_scroll.second;
		ScreenToClient(APP.m_window.GetWndHandle(), &m_mouse);
		
		if ((GetAsyncKeyState('E') && !m_controlButtonClick))
		{
			SC->SetEditMode(!SC->GetEditMode());
			m_controlButtonClick = true;
		};
		if (!WC->IsPause())
		{
			if (SC->GetEditMode())
				UpdateEditScene();
			else
				UpdateGameScene();
		}
	}
	
	GetCursorPos(&mouse);
	ScreenToClient(APP.m_window.GetWndHandle(), &mouse);
	mouse.x += 16;
	mouse.y += 12;
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
					//soundInstance->Pause();
					m_inGameSetting.EventClick(m_inGameSetting.GetButton(i).SendClickData());
					
				}
			}
			break;
		}
	}
	
	//Test
	
	//m_enemy.Discovery();
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
	//m_GroundBlockTex.Load("Texture/GroundBlock/Groundslice03_03.png");;
	m_iceWaterBlockTex[0].Load("Texture/GimmickBlock/iceWaterDeepStars.png");;
	charaRect = Math::Rectangle(0, 0, 32, 32);
	m_playerTex.Load("Texture/Creature/player.png");
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
	
	m_keyTexture[0].Load("Texture/Item/Key1.png");
	m_keyTexture[1].Load("Texture/Item/Key2.png");
	m_keyTexture[2].Load("Texture/Item/Key3.png");
	
	m_backGround.Load("Texture/BackGround/Title.png");

	m_enemy = NPC();
	m_enemy.InitTO(m_terrain);
	for (int i = 1; i < m_typeBlockNum; i++)
	{
		std::vector<std::array<KdTexture*,5>> _loadVector ;
		std::array<KdTexture*, 5>_loadarray;
		switch (i)
		{
		case BlockEditerSelect::Ground:
			for (int j = 0; j < 5; j++)
				_loadarray[j]=(&m_groundTex[j]);
			_loadVector.push_back(_loadarray);
				
				break;

		case BlockEditerSelect::Ice:
			for (int j = 0; j < MaxTypeBlock(i); j++)
			{
				switch (j)
				{
				case Surface:
					for (int l = 0; l < 5; l++) 
					{
						_loadarray[l] = (&m_iceSurfaceTex[l]);
					}
					_loadVector.push_back(_loadarray);
					break;
				case Inside:
					for (int l = 0; l < 5; l++)
					{
						_loadarray[l] = (&m_iceInsideTex[l]);
					}
					_loadVector.push_back(_loadarray);
					break;
				}
			}
			break;
		case 3:
			for (int l = 0; l < 5; l++)
			{
				_loadarray[l] = (&m_iceWaterBlockTex[l]);
			}
			_loadVector.push_back(_loadarray);
			break;
		}
		m_blockLiblary[i] = _loadVector;
	}
	m_player.SetScroll(&m_scroll);
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
		if (m_player.GetOnGroundFlag())
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
