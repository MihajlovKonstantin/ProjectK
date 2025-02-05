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
		//InfoPanelCollision
		for (size_t i = 0; i < m_inform.size(); i++)
		{
			auto _pos = m_inform[i].GetGPos();
			SHADER.m_spriteShader.DrawBox(_pos.first - m_scroll.first, _pos.second - m_scroll.second, 100, 100, &Math::Color( 0,1,0,0.2f ));
		}
		for (size_t i = 0; i < m_spawner.size(); i++)
		{
			auto _index = m_spawner[i].GetIndex();
			int _spawnerType;
			if ((_index == 2) || (_index == 3))
			{
				SHADER.m_spriteShader.SetMatrix(Math::Matrix::CreateTranslation({ m_spawner[i].GetCharaPos().first - m_scroll.first,m_spawner[i].GetCharaPos().second - m_scroll.second,0 }));
				_spawnerType = m_spawner[i].GetType();
				switch(_spawnerType)
				{
				case EnemyType::TypeSlime:
					SHADER.m_spriteShader.DrawTex(&m_slimeSpawnerTex, spawnerRectangle);
						break;
				case EnemyType::TypeSnowBall:
					SHADER.m_spriteShader.DrawTex(&m_snowBallSpawnerTex, spawnerRectangle);
					break;
				}
			}

		}
		//ブロック表示用
		SHADER.m_spriteShader.SetMatrix(Math::Matrix::CreateTranslation(590, 240, 0));
		SHADER.m_spriteShader.DrawTex(GetBlockTex(), charaRect, 1.0f);
		
		string _string[3];
		_string[0] ="(R/T)CurrentEditerMenu ";
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
		case EditerSelect::StageTypeMenu:
			_string[0] += "StageType";
			break;
		case EditerSelect::InfoPanelMenu:
			_string[0] += "InfoPanel";
			break;
		}
		switch (m_editerMenuIndex)
		{
		case EditerSelect::StageTypeMenu:
			switch (m_unitType)
			{
			case StageTypeSelect::Base:
				_string[1] += "Base";
				break;
			case StageTypeSelect::KeyCollect:
				_string[1] += "Key";
				break;
			default:
				m_unitType = 0;
				break;
			}
			break;
		case EditerSelect::BlockMenu:
			_string[1] = "(D/F)CurrentBlockType ";
			switch (m_unitType)
			{
			case 0:
				_string[1] += "Void";
				break;
			case BlockEditerSelect::Ground:
				_string[1] += "Ground";
				break;
			case BlockEditerSelect::Ice:
				_string[1] += "Snow";
				break;
			case BlockEditerSelect::IceWater:
				_string[1] += "IceWater";
				break;
			case BlockEditerSelect::Ladder:
				_string[1] += "ladder";
				break;
			case BlockEditerSelect::Lava:
				_string[1] += "Lave";
				break;
			case BlockEditerSelect::Crate:
				_string[1] += "Crate";
				break;
			}
			_string[2] = "CurrentBlockVariant ";
			_string[2] = "(X/C)CurrentBlockVariant ";
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
			_string[1] = "(D/F)CurrentItemType ";
			switch (m_unitType)
			{
			case ItemSelect::Key:
				_string[1] += "Key";
				break;
			default:
				m_unitType = 0;
				break;
			}
			_string[2] = "(D/F)CurrentItemVariant";
			switch (m_selectedUnitVariant)
			{
			case 0:
				_string[2] += "Base";
			default:
				if (m_unitType == ItemSelect::Key)
				{
					_string[2] = "(X/C)CurrentItemVariant";
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
			_string[1] = "(D/F)CurrentCharaType ";
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
			default:
				m_unitType = 0;
				break;
			}
			if (m_unitType != SpawnerSelect::Player)
			{
				_string[2] = "(X/C)CurrentEnemyVariant ";
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
			break;
		case EditerSelect::InfoPanelMenu:
			_string[1] = "(D/F)PanelSelect ";
			switch (m_unitType)
			{
			case InfoPanelEnun::Move:
				_string[1] += "Move";
				break;
			case InfoPanelEnun::LavaInf:
				_string[1] += "LavaInfo";
				break;
			case InfoPanelEnun::LadderInfo:
				_string[1] += "LadderInfo";
				break;
			case InfoPanelEnun::Jump:
				_string[1] += "Jump";
				break;
			case InfoPanelEnun::EditerMode:
				_string[1] += "EditerOpen";
				break;
			case InfoPanelEnun::Draw:
				_string[1] += "EditerDraw";
				break;
			}
			break;
		}

		
		
		const char* _text[3] = { _string[0].c_str(),_string[1].c_str() ,_string[2].c_str() };
		DrawString(260, 300, _text[0], { 0, 0, 0, 1 }, 0.5f);
		DrawString(260, 250, _text[1], { 0, 0, 0, 1 }, 0.5f);
		DrawString(260, 200, _text[2], { 0, 0, 0, 1 }, 0.5f);
		
	}
	if (!WC->IsPause())
	{
		DrawString(-100, 300, message.c_str(), { 1,0,0,1 }, 0.7f);
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
		if ((m_player.GetHp() <= 0) && (!CLEARFLAG))
		{
			SHADER.m_spriteShader.DrawString(0, 0, "GameOver", { 0,0,1,1 });
		}
		else
		{
			if (!CLEARFLAG)
			{
				/*m_hpBar = to_string(int(m_player.GetHp())) + "/100";
				DrawString(-300, 300, m_hpBarExpress, { 1,0,0,1 }, 0.5f);*/
			}

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
	DrawString(position[0] - size[0], position[1] + size[1] / 2, charStr, Math::Vector4(0, 0, 0, 1), scale);
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
	tmpTex.ClearRenerTarget(Math::Color(0, 0, 0, 1));
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
		if (m_stageType == 0)
		{
			SHADER.m_spriteShader.SetMatrix(Math::Matrix::CreateTranslation(0, -m_scroll.second, 0));
			SHADER.m_spriteShader.DrawTex(&m_stageBaseTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);
		}
		D3D.SetBlendState(BlendMode::Alpha);
		SHADER.m_spriteShader.SetMatrix(m_player.GetMatrix());
		SHADER.m_spriteShader.DrawTex(m_player.GetTexture(), m_player.GetRect(), 1.0f);
		//ダメージを受けるとhpバーが出てくる
		if (m_player.GetHpAlpha())
		{
			if (m_hpAlphaCnt <= 20)m_hpAlpha = 1.0f;
			if (m_hpAlphaCnt-- < 0)
			{
				m_hpAlphaCnt = m_BaseHpAlphaCnt;
				m_player.SetHpAlpha(false);
			}
		}

		m_hpAlpha -= 0.01f;

		if (m_hpAlpha < 0)m_hpAlpha = 0;

		SHADER.m_spriteShader.SetMatrix(m_player.GetHpMatrix());
		SHADER.m_spriteShader.DrawTex(m_player.GetHpTexture(), m_player.GetHpRect(), m_hpAlpha);
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
		
		for (int i = 0; i < m_spawner.size(); i++)
		{
			auto _slime = m_spawner[i].GetSlime();

			for (int j = 0; _slime->size() > j; j++)
			{
				if (SC->GetEditMode())
				{
					_slime->at(j).UpdateTransMat();
				}
				auto _matrix = _slime->at(j).GetMatrix();
				auto _texture = _slime->at(j).GetTexture();
				auto _rect = _slime->at(j).GetRect();
				SHADER.m_spriteShader.SetMatrix(_matrix);
				SHADER.m_spriteShader.DrawTex(_texture, _rect);
			}

			auto _snowBall = m_spawner[i].GetSnowBall();
			
			for (int j = 0; j < _snowBall->size(); j++)
			{
				if (SC->GetEditMode())
				{
					_snowBall->at(j).UpdateTransMat();
				}
				auto _matrix = _snowBall->at(j).GetMatrix();
				auto _texture = _snowBall->at(j).GetTexture();
				auto _rect = _snowBall->at(j).GetRect();
				SHADER.m_spriteShader.SetMatrix(_matrix);
				SHADER.m_spriteShader.DrawTex(_texture, _rect);
			}
		}

	}
	
}

void Scene::CreateTerrainObject()
{
	bool _anglePossible = true;
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
		radian = 0.0f * float(M_PI);
	}
	buffer = int(radian / (float(M_PI) * 0.25f));
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
	case BlockEditerSelect::IceWater:
		switch (buffer)
		{
		case 1:
			_currentTex = &m_iceWaterBlockTex[2];
			break;
		case 3:
			_currentTex = &m_iceWaterBlockTex[1];
			break;
		case 5:
			_currentTex = &m_iceWaterBlockTex[4];
			break;
		case 7:
			_currentTex = &m_iceWaterBlockTex[3];
			break;
		default:
			_currentTex = &m_iceWaterBlockTex[0];
			break;
		}
		break;
	default:
		_currentTex = NULL;
		break;
	case BlockEditerSelect::Ladder:
		_anglePossible = false;
		_currentTex = &m_ladderTex[0];
		break;
	case BlockEditerSelect::Lava:
		switch (buffer)
		{
		case 1:
			_currentTex = &m_lavaTex[2];
			break;
		case 3:
			_currentTex = &m_lavaTex[1];
			break;
		case 5:
			_currentTex = &m_lavaTex[4];
			break;
		case 7:
			_currentTex = &m_lavaTex[3];
			break;
		default:
			_currentTex = &m_lavaTex[0];
			break;
		}
		break;
	case BlockEditerSelect::Crate:
		_anglePossible = false;
		_currentTex = &m_crateTex[0];
		break;
	}
	if (buffer == 8)
	{
		buffer = 0;
	}

	std::vector<int> _terrainTypeVector;
	std::vector<int> _terrainVarVector;
	m_blocks.clear();
	for (int j = 0; j < i; j++)
	{
		_terrainTypeVector.push_back(m_unitType);
		_terrainVarVector.push_back(m_selectedUnitVariant);
		{
			if (_anglePossible)
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
				}
				switch (m_unitType)
				{
				case BlockEditerSelect::Ice:
					m_blocks[m_blocks.size() - 1].m_iceBlock = true;
					break;
				case BlockEditerSelect::IceWater:
					m_blocks[m_blocks.size() - 1].m_snowBlock = true;
					break;
				case BlockEditerSelect::Ladder:
					m_blocks[m_blocks.size() - 1].m_backStage = true;
					m_blocks[m_blocks.size() - 1].m_laderBlock = true;
					break;
				case BlockEditerSelect::Lava:
					m_blocks[m_blocks.size() - 1].m_lavaBlock = true;
					break;

				}
			}
			else
			{
				buffer = buffer / 2 * 2;
				switch (buffer)
				{
				case 0:
					m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f + j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
					break;
				case 2:
					m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f + j * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
					break;
				case 4:
					m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f - j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
					break;
				case 6:
					m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f - j * 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
					break;
				}
				switch (m_unitType)
				{
				case BlockEditerSelect::Ice:
					m_blocks[m_blocks.size() - 1].m_iceBlock = true;
					break;
				case BlockEditerSelect::IceWater:
					m_blocks[m_blocks.size() - 1].m_snowBlock = true;
					break;
				case BlockEditerSelect::Ladder:
					m_blocks[m_blocks.size() - 1].m_backStage = true;
					m_blocks[m_blocks.size() - 1].m_laderBlock = true;
					break;
				case BlockEditerSelect::Lava:
					m_blocks[m_blocks.size() - 1].m_lavaBlock = true;
					break;

				}
			}
			m_blocks[j].SetScroll(&m_scroll);
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
	if (m_unitType == 0)
	{
		m_blocks.clear();
	}

	if (!m_blocks.empty())
	{
		m_terrain.push_back(TerrainObject({ int((m_point[0].x - 640) / 32) * 32.0f ,(int(-m_point[0].y + 360) / 32) * 32.0f }, buffer, _terrainTypeVector, _terrainVarVector, m_blocks));
		m_terrain[m_terrain.size() - 1].SetScroll(&m_scroll);
	}
	m_blocks.clear();
	_terrainTypeVector.clear();
	_terrainVarVector.clear();
	//Angle Sup Block
	switch (m_unitType)
	{
	case BlockEditerSelect::Ground:
		_currentTex = &m_groundTex[0];
			break;
	case BlockEditerSelect::Ice:
		switch (m_selectedUnitVariant)
		{
		case Surface:
			_currentTex = &m_iceSurfaceTex[0];
			break;
		case Inside:
			_currentTex = &m_iceInsideTex[0];
			break;
		}
	case BlockEditerSelect::IceWater:
		_currentTex = &m_iceWaterBlockTex[0];
			break;

	case BlockEditerSelect::Ladder:
		_anglePossible = false;
		_currentTex = &m_ladderTex[0];
		break;
	case BlockEditerSelect::Lava:
			_currentTex = &m_lavaTex[0];
			break;
	default:
		_currentTex = NULL;
		break;
	}
	for (int j = 0; j <= i; j++)
	{
		_terrainTypeVector.push_back(m_unitType);
		_terrainVarVector.push_back(m_selectedUnitVariant);
		{
			switch (buffer)
			{
			case 1:
				m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f + j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f + j * 32.0f-32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 3:
				m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f - j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f + j * 32.0f-32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 5:
				m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f - j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f - j * 32.0f+32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			case 7:
				m_blocks.push_back(Block(int((m_point[0].x - 640) / 32) * 32.0f + j * 32.0f, (int(-m_point[0].y + 360) / 32) * 32.0f - j * 32.0f + 32.0f, 32.0f, 32.0f, _currentTex, false, 0));
				break;
			}
			if (!m_blocks.empty())
			{
				switch (m_unitType)
				{
				case BlockEditerSelect::Ice:
					m_blocks[m_blocks.size() - 1].m_iceBlock = true;
					break;
				case BlockEditerSelect::IceWater:
					m_blocks[m_blocks.size() - 1].m_snowBlock = true;
					break;
				case BlockEditerSelect::Ladder:
					m_blocks[m_blocks.size() - 1].m_backStage = true;
					m_blocks[m_blocks.size() - 1].m_laderBlock = true;
					break;
				case BlockEditerSelect::Lava:
					m_blocks[m_blocks.size() - 1].m_lavaBlock = true;
					break;

				}
				m_blocks[j].SetScroll(&m_scroll);
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
	if (m_unitType == 0)
	{
		m_blocks.clear();
	}
	if (!m_blocks.empty())
	{
		m_terrain.push_back(TerrainObject({ int((m_point[0].x - 640) / 32) * 32.0f ,(int(-m_point[0].y + 360) / 32) * 32.0f }, buffer + 8, _terrainTypeVector, _terrainVarVector, m_blocks));
		m_blocks.clear();
	}
	
	m_drawStartBool = false;
}

void Scene::CreateItem()
{
	std::pair<float, float>_pos = { m_point[0].x-640 ,-m_point[0].y+360 };
	switch (m_unitType)
	{
	case ItemSelect::VoidIS:
		DeleteItem();
		break;
	case ItemSelect::Key:
		switch (m_selectedUnitVariant)
		{
		case KeySelect::Yellow:
			_lastItem = Item(_pos, &m_itemLibrary, 0);
			m_item.push_back(_lastItem);
			break;
		case KeySelect::Blue:
			_lastItem = Item(_pos, &m_itemLibrary, 2);
			m_item.push_back(_lastItem);
			break;
		case KeySelect::Red:
			_lastItem = Item(_pos, &m_itemLibrary, 1);
			m_item.push_back(_lastItem);
			break;
		}
		break;
	}
}

void Scene::DeleteItem()
{
	if (!m_item.empty())
	{
 		auto _pos = m_item[0].GetPos();
		for (size_t i = 0; i < m_item.size();)
		{
			_pos = m_item[i].GetPos();
			_pos.first += 640;
			_pos.second = _pos.second * (-1) + 360;
			if ((abs(m_point[0].x - _pos.first) <= 100) && (abs(m_point[0].y - _pos.second) <= 100))
			{
				m_item.erase(m_item.begin() + i);
			}
			else
			{
				i++;
			}
		}
	}
	
}

void Scene::SaveStage()
{
	std::ofstream outFile("StageData");
	if (outFile.is_open()) {
		outFile << m_selectedMap<<"\n";
		outFile << m_selectedPath << "\n";
		outFile << RELEASE << "\n";
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
		std::getline(inFile, line, '\n');
		m_stageType = stoi(line);
		std::getline(inFile, line, '\n');
		size = stoi(line);
		for (int j = 0; j < size; j++)
		{
			typeBlock.clear();
			std::getline(inFile, line, ',');
			angle = stoi(line);
			std::getline(inFile, line, ',');
			x = stoi(line);
			std::getline(inFile, line, ',');
			y = stoi(line);
			std::getline(inFile, line, '\n');
			typeBlockSize = stoi(line);
			for (int i = 0; i < typeBlockSize; i++)
			{
				std::getline(inFile, line, ',');
				_buff = stoi(line);
				typeBlock.push_back(_buff);
			}
			for (int i = 0; i < typeBlockSize; i++)
			{
				std::getline(inFile, line, ',');
				_buff = stoi(line);
				_varBlock.push_back(_buff);
			}

			m_terrain.push_back(TerrainObject({ x,y }, angle, typeBlock,_varBlock, &m_blockLiblary));
			m_terrain[m_terrain.size() - 1].SetScroll(&m_scroll);
			std::getline(inFile, line, '\n');


		}
		inFile.close();
	}
}

void Scene::UpdateGameScene()
{
	message = "";
	m_scroll = m_player.GetGPos();

	//StageClear Data
	{
		if (m_stageType == 1)
		{
			m_clearState[1] = m_keyFlag.size();
		}
		if (m_stageType == 1)
		{
			m_clearStateString = to_string(m_clearState[0]) + "/" + to_string(m_clearState[1]);
		}
		if (m_stageType == 0)
		{
			if (m_player.GetGPos().second >= 160)
			{
				CLEARFLAG = true;
			}
		}
	}

	//Player Controll
	{
		if ((m_player.GetHp() > 0) && (!CLEARFLAG))
		{
			if (GetAsyncKeyState(VK_LEFT))
			{
				if (!m_rightFlg)
				{
					m_leftFlg = true;
					m_player.SetDirection(Direction::Left);
				}
			}
			else m_leftFlg = false;
			if (GetAsyncKeyState(VK_RIGHT))
			{
				if (!m_leftFlg)
				{
					m_rightFlg = true;
					m_player.SetDirection(Direction::Right);
				}
			}
			else m_rightFlg = false;

			if (GetAsyncKeyState(VK_UP))
			{
				if ((!m_downFlg) && (m_player.GetOnLadderFlag()))
				{

					m_upFlg = true;
					m_player.SetDirection(Direction::Up);
				}
			}
			else m_upFlg = false;
			if (GetAsyncKeyState(VK_DOWN))
			{
				if ((!m_upFlg) && (m_player.GetOnLadderFlag()))
				{
					m_downFlg = true;
					m_player.SetDirection(Direction::Down);
				}
			}
			else m_downFlg = false;

			if (GetAsyncKeyState(VK_SPACE))
			{
				if (!m_jumpFlg)
				{
					m_player.Jump();
					m_jumpFlg = true;
				}
			}
			else m_jumpFlg = false;

		}
		else
		{
			m_player.SetDirection(Stand);
		}
		if (!m_leftFlg && !m_rightFlg)
		{
			if (!m_upFlg && !m_downFlg)
			{
				m_player.SetDirection(Stand);
			}
		}
	}
	//Player to Item Collision
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

	
	//Player to Block collision
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
			}
		}
	}
	//Player to Inform Collision
	for (int i = 0; i < m_inform.size(); i++)
	{
		message += m_player.CollisionToInform(m_inform[i]);
	}
	//Spawner Update
	for (int i = 0; i < m_spawner.size(); i++)
	{
		//Slime Collision
		auto _slimeArr = m_spawner[i].GetSlime();
		for (int k = 0; k < _slimeArr->size(); k++)
		{
			for (int m = 0; m < m_terrain.size(); m++)
			{
				if (m_terrain[m].OnCollisionRange(_slimeArr->at(k).GetGPos()))
				{
					auto _blocks = m_terrain[m].GetBlocks();
					for (int j = 0; j < _blocks->size(); j++)
					{
						auto _block = _blocks->at(j);
						m_testCollision = _slimeArr->at(k).CollisionToBlock(_block);
					}
				}
			}
		}
		//SnowBall Collision
		auto _snowBzllArr = m_spawner[i].GetSnowBall();
		for (int k = 0; k < _snowBzllArr->size(); k++)
		{
			for (int m = 0; m < m_terrain.size(); m++)
			{
				if (m_terrain[m].OnCollisionRange(_snowBzllArr->at(k).GetGPos()))
				{
					auto _blocks = m_terrain[m].GetBlocks();
					for (int j = 0; j < _blocks->size(); j++)
					{
						auto _block = _blocks->at(j);
						m_testCollision = _snowBzllArr->at(k).CollisionToBlock(_block);
					}
				}
			}
		}
		//Update
		m_spawner[i].Update();
	}

	m_player.Update();
}

void Scene::UpdateEditScene()
{
	//Editer Menu Select
	{
		if (GetAsyncKeyState('R'))
		{
			if (!m_controlButtonClick)
			{
				m_editerMenuIndex++;
				if (m_editerMenuIndex >= EditerSelect::COUNTES)
				{
					m_editerMenuIndex = 0;
				}
				m_controlButtonClick = true;
				currentCD = MaxCD;
			}
		}
		if (GetAsyncKeyState('T'))
		{
			if (!m_controlButtonClick)
			{
				m_editerMenuIndex--;
				if (m_editerMenuIndex < 0)
				{
					m_editerMenuIndex = EditerSelect::COUNTES - 1;
				}
				m_controlButtonClick = true;
				currentCD = MaxCD;
			}
		}
	}
	//Unit Select
	{
		if (GetAsyncKeyState('D'))
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
					_maxType = ItemSelect::COUNTIS;
					break;
				case EditerSelect::CharaMenu:
					_maxType = SpawnerSelect::COUNTSS;
					break;
				case EditerSelect::StageTypeMenu:
					_maxType = 2;
					break;
				case EditerSelect::InfoPanelMenu:
					_maxType = InfoPanelEnun::COUNTIPE;
					break;
				}
				if (m_unitType >= _maxType)
				{
					m_unitType = 0;
				}
				m_controlButtonClick = true;
				currentCD = MaxCD;
			}
		}
		if (GetAsyncKeyState('F'))
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
					_maxType = ItemSelect::COUNTIS;
					break;
				case EditerSelect::CharaMenu:
					_maxType = SpawnerSelect::COUNTSS;
					break;
				case EditerSelect::StageTypeMenu:
					_maxType = 2;
					break;
				case EditerSelect::InfoPanelMenu:
					_maxType = InfoPanelEnun::COUNTIPE;
					break;
				}
				if (m_unitType < 0)
				{
					m_unitType = _maxType - 1;
				}
				m_controlButtonClick = true;
				currentCD = MaxCD;
			}
		}
	}
	//Variant Select
	{
		if (GetAsyncKeyState('X'))
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
				currentCD = MaxCD;
			}
		}

		if (GetAsyncKeyState('C'))
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
					m_selectedUnitVariant = _maxType - 1;
				}
				m_controlButtonClick = true;
				currentCD = MaxCD;
			}
		}
	}
	//Scroll Controll
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			m_scroll.first -= 5;
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
	}
	//Draw Controll
	{
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
				case StageTypeMenu:
					m_stageType = m_unitType;
					m_drawStartBool = false;
					break;
				case InfoPanelMenu:
					CreateInformPanel();
					m_drawStartBool = false;
					break;
				}
			}
		}
	}
	m_player.UpdateTransMat();
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
			case SpawnerSelect::Player:
				outFile << m_spawner[i].GetCharaPos().second << "\n";
				break;
			case SpawnerSelect::Enemy:
				outFile << m_spawner[i].GetCharaPos().second << ",";
				outFile << m_spawner[i].GetType() << "\n";
				break;
			case SpawnerSelect::Enemys:
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

void Scene::SaveItem()
{
	std::ofstream outFile("ItemData");
	if (outFile.is_open()) {
		outFile << m_item.size() << "\n";
		for (int i = 0; i < m_item.size(); i++)
		{
			outFile << m_item[i].GetIndex() << "\n";
			outFile << m_item[i].GetPos().first << ",";
			outFile << m_item[i].GetPos().second << "\n";
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
			case SpawnerSelect::Player:
				std::getline(inFile, line, '\n');
				pos.second = stoi(line);
				m_spawner.push_back(Spawner(charaIndex, pos,&m_enemylibrary, &m_player));
				break;
			case SpawnerSelect::Enemy:
				std::getline(inFile, line, ',');
				pos.second = stoi(line);
				std::getline(inFile, line, '\n');
				type = stoi(line);
				m_spawner.push_back(Spawner(charaIndex, pos, &m_enemylibrary, &m_player, &m_terrain, type));
				break;
			case SpawnerSelect::Enemys:
				std::getline(inFile, line, ',');
				pos.second = stoi(line);
				std::getline(inFile, line, ',');
				type = stoi(line);
				std::getline(inFile, line, ',');
				interval = stoi(line);
				std::getline(inFile, line, '\n');
				num = stoi(line);
				m_spawner.push_back(Spawner(charaIndex, pos, &m_enemylibrary, &m_player, &m_terrain, type, interval, num));
				break;
			}
		}
		inFile.close();
	}
}

void Scene::CreateSpawn()
{
	SpawnPos.first = m_point[0].x-640;
	SpawnPos.second = -m_point[0].y+360;
	int charaIndex = m_unitType;
	switch (charaIndex)
	{
	case SpawnerSelect::Player:
		if (m_spawner.size() != 0)
		{
			if(m_spawner[0].GetIndex() == 1)m_spawner.erase(m_spawner.begin());
			m_spawner.insert(m_spawner.begin(), (Spawner(charaIndex, SpawnPos, &m_enemylibrary, &m_player)));
		}
		else m_spawner.push_back(Spawner(charaIndex, SpawnPos, &m_enemylibrary, &m_player));
		break;
	case SpawnerSelect::Enemy:
		m_spawner.push_back(Spawner(charaIndex, SpawnPos, &m_enemylibrary, &m_player, &m_terrain, m_selectedUnitVariant));
		m_spawner[m_spawner.size() - 1].SetScroll(&m_scroll);
		break;
	default:
		m_spawner.push_back(Spawner(charaIndex, SpawnPos, &m_enemylibrary, &m_player, &m_terrain, m_selectedUnitVariant, 300, 5));
		m_spawner[m_spawner.size() - 1].SetScroll(&m_scroll);
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

void Scene::CreateDataPatch()
{

}

void Scene::InitMap(std::string mapName)
{
}

void Scene::SaveMap()
{
	std::ofstream outFile("CurrentMap.map");
	std::ifstream inFile("StageData");
	std::string line;
	if (inFile.is_open()) {
		std::getline( inFile,line);
		outFile << line << std::endl;
		std::getline(inFile, line);
		outFile << line << std::endl;
		while (std::getline(inFile, line)) {
			outFile << line << std::endl;
		}
	}
	inFile.close();
	inFile = std::ifstream("SpawnData");
	if (inFile.is_open()) {
		while (std::getline(inFile, line)) {
			outFile << line << std::endl;
		}
	}
	inFile.close();
	inFile = std::ifstream("ItemData");
	if (inFile.is_open()) {
		while (std::getline(inFile, line)) {
			outFile << line << std::endl;
		}
	}
	outFile.close();

	

	std::string _dirFinder = "del \"" + m_dataPath + "\\CurrentMap.map\"";
	system(_dirFinder.c_str());
	_dirFinder = "copy \"CurrentMap.map\" \"" + m_dataPath + "\\\"";
	system(_dirFinder.c_str());
	if (RELEASE == 0)
	{
		_dirFinder = "delete \"" + m_selectedPath + "\\" + m_selectedMap + "\"";
		system(_dirFinder.c_str());
		_dirFinder = "copy \"" + m_dataPath + "\\CurrentMap.map\" \"" + m_selectedPath + "\\\"";
		system(_dirFinder.c_str());
		_dirFinder = "rename \"" + m_selectedPath + "\\CurrentMap.map \"" + m_selectedMap + "\"";
		system(_dirFinder.c_str());
		
	}
	_dirFinder = "del \"CurrentMap.map\"";
	system(_dirFinder.c_str());
	char buffer[1024];
	if (getcwd(buffer, sizeof(buffer)) != nullptr) {
		std::string currentDir(buffer);
		std::string newDir = " delete \"" + currentDir + "\\CurrentMap.map\"";
		system(newDir.c_str());
	}
}

void Scene::LoadMap()
{
	SC->SetEditMode(false);
	std::ifstream inFile(m_dataPath+"\\CurrentMap.map");
	m_terrain.clear();
	m_spawner.clear();
	std::string line;
	if (inFile.is_open()) {
		std::string line;
		getline(inFile, line);
		WC->SetMap(line);
		getline(inFile, line);
		WC->SetPath(line);
		m_selectedPath = line;
		getline(inFile, line);
		RELEASE = stoi(line);
		int x, y, angle, size, typeBlockSize, _buff;
		std::vector<int> typeBlock;
		std::vector<int> _varBlock;
		
		std::getline(inFile, line, '\n');
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
			m_terrain.push_back(TerrainObject({ x,y }, angle, typeBlock, _varBlock, &m_blockLiblary));
			m_terrain[m_terrain.size() - 1].SetScroll(&m_scroll);
		}
		

		int charaIndex, type, interval, num;
		std::pair<float, float>pos;
		std::getline(inFile, line, '\n');
		if (line == "")
		{
			std::getline(inFile, line, '\n');
		}
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
					m_spawner.push_back(Spawner(charaIndex, pos, &m_enemylibrary, &m_player));
					break;
				case 2:
					std::getline(inFile, line, ',');
					pos.second = stoi(line);
					std::getline(inFile, line, '\n');
					type = stoi(line);
					m_spawner.push_back(Spawner(charaIndex, pos, &m_enemylibrary, &m_player, &m_terrain, type));
					m_spawner[m_spawner.size() - 1].SetScroll(&m_scroll);
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
					m_spawner.push_back(Spawner(charaIndex, pos, &m_enemylibrary, &m_player, &m_terrain, type, interval, num));
					m_spawner[m_spawner.size() - 1].SetScroll(&m_scroll);
					break;
				}
		}
		
		int itemIndex, itemNum,xPos,yPos;
		{
			std::getline(inFile, line, '\n');
			if (line == "")
			{
				std::getline(inFile, line, '\n');
			}
			if (!(line == ""))
			{
				itemNum = stoi(line);
				for (int i = 0; i < itemNum; i++)
				{
					std::getline(inFile, line, '\n');
					itemIndex = stoi(line);
					std::getline(inFile, line, ',');
					xPos = stoi(line);
					std::getline(inFile, line, '\n');
					yPos = stoi(line);
					m_item.push_back(Item({ xPos, yPos }, &m_itemLibrary, itemIndex));
				}
			}
			
		}

	}
	inFile.close();
	char buffer[1024];
	if (getcwd(buffer, sizeof(buffer)) != nullptr)
	{
		std::string currentDir(buffer);
		std::string newDir = " delete /Q \"" + currentDir + "\\CurrentMap.map\"";
		system(newDir.c_str());
	}
	CLEARFLAG = false;
	for (size_t i = 0; i < m_keyFlag.size(); i++)
	{
		m_keyFlag[i] = false;
	}
	switch (m_stageType)
	{
	case 0:
		m_clearStateString = "";
		break;
	case 1:
		m_clearStateString = "0/0";
		m_clearExpress = m_clearStateString.c_str();
		m_clearState[0] = 0;
		break;
	}
	m_selectedMap = WC->GetMap();
	std::string _dirFinder = "del \"CurrentMap.map\"";
	system(_dirFinder.c_str());
	m_player.Init({0,0});
}

int Scene::GetClearFlag()
{
	if (CLEARFLAG)
	{
		return 1;
	}
	return 0;
}

KdTexture* Scene::GetBlockTex()
{
	KdTexture* _BlockTex = &m_voidTex;

	switch (m_editerMenuIndex)
	{
	case EditerSelect::BlockMenu:
		switch (m_unitType)
		{
		case 0:
			_BlockTex = &m_voidTex;
			break;
		case 1:
			_BlockTex = &m_groundTex[0];
			break;
		case 2:
			_BlockTex = &m_iceSurfaceTex[0];
			break;
		case 3:
			_BlockTex = &m_iceWaterBlockTex[0];
			break;
		case 4:
			_BlockTex = &m_ladderTex[0];
			break;	
		case 5:
			_BlockTex = &m_lavaTex[0];
			break;	
		case 6:
			_BlockTex = &m_crateTex[0];
			break;
		}
		break;
	case EditerSelect::ItemMenu:

		break;
	case EditerSelect::CharaMenu:
		
		break;
	case EditerSelect::StageTypeMenu:
		
		break;
	}

	return _BlockTex;
}

void Scene::CreateInformPanel()
{
	for (size_t i = 0; i < m_inform.size();)
	{
		if (m_unitType == m_inform[i].GetIndex())
		{
			m_inform.erase(m_inform.begin()+i);
		}
		else
		{
			i++;
		}
	}
	auto _newInform = InformPanel({ m_mouse.x-640,-m_mouse.y+360 }, m_unitType);
	m_inform.push_back(_newInform);
}

void Scene::Update()
{
	m_message = "";
	if (m_controlButtonClick == true)
	{
		currentCD--;
		if (currentCD < 0)
		{
			currentCD = 0;
		}
	}
	
	if (currentCD > 0)
	{
		m_controlButtonClick = true;
	}
	else
	{
		m_controlButtonClick = false;
	}
	if (SC->GetCurrentScene() == SceneControlData::Scenes::MainScene)
	{
		if (GetAsyncKeyState('S'))
		{
			if (!m_sKey)
			{
				SaveStage();
				SaveSpawn();
				SaveItem();
				SaveMap();
			}
			m_sKey = true;
		}
		else m_sKey = false;
		if (GetAsyncKeyState('A'))
		{
			if (!m_aKey)
			{
				LoadMap();
			}
			m_aKey = true;
		}
		else m_aKey = false;
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
				m_item[i].Update(m_scroll);
				i++;
			}
		}
		GetCursorPos(&m_mouse);
		m_mouse.x += 16+m_scroll.first;
		m_mouse.y += 12-m_scroll.second;
		ScreenToClient(APP.m_window.GetWndHandle(), &m_mouse);
		
		if ((GetAsyncKeyState('E') && !m_controlButtonClick))
		{
			if (RELEASE == 0)
			{
				SC->SetEditMode(!SC->GetEditMode());
			}
			else
			{
				if (WC->IsPause())
				{
					WC->Resume();
				}
				else
				{
					WC->PauseGame();
				}
			}
			m_controlButtonClick = true;
			currentCD = MaxCD;
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
				currentCD = MaxCD;
				break;
			case SceneControlData::Scenes::MenuScene:
				WC->Resume();
				SC->SetCurrentScene(SceneControlData::Scenes::MainScene);
				m_controlButtonClick = true;
				currentCD = MaxCD;
				break;
			}
	}
	/*if (GetAsyncKeyState('Z'))
	{
		m_controlButtonClick = false;
	}*/
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
}

void Scene::Init(WindowsControlData* WCInput, std::string dataPath, std::string selectedPath)
{
	
	m_controlButtonClick = false;
	m_dataPath = dataPath;
	m_selectedPath = selectedPath;
	// �摜�̓ǂݍ��ݏ���
	ShowCursor(true);
	spriteBatch = new DirectX::SpriteBatch(D3D.GetDevContext());
	spriteFont = new DirectX::SpriteFont(D3D.GetDev(),L"SpriteFont.dat");
	m_inGameSetting.InitInGameSetting();
	WC = WCInput;
	SC = new SceneControlData();
	SC->SetCurrentScene(SceneControlData::Scenes::MainScene);
	m_inGameSetting.AddData(*WC);
	//m_blockTex.Load("Texture/GroundBlock/Ground0.png");;
	//m_GroundBlockTex.Load("Texture/GroundBlock/Groundslice03_03.png");;
	WC->Resume();
	charaRect = Math::Rectangle(0, 0, 32, 32);

	m_stageBaseTex.Load("Texture/BackGround/clearBack.png");

	m_playerTex.Load("Texture/Player/player.png");
	m_playerHpTex.Load("Texture/Player/hp.png");

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

	m_iceWaterBlockTex[0].Load("Texture/GimmickBlock/iceWater0.png");
	m_iceWaterBlockTex[1].Load("Texture/GimmickBlock/iceWater1.png");
	m_iceWaterBlockTex[2].Load("Texture/GimmickBlock/iceWater2.png");
	m_iceWaterBlockTex[3].Load("Texture/GimmickBlock/iceWater3.png");
	m_iceWaterBlockTex[4].Load("Texture/GimmickBlock/iceWater4.png");

	m_ladderTex[0].Load("Texture/GimmickBlock/ladder_mid.png");

	m_lavaTex[0].Load("Texture/GimmickBlock/liquidLava0.png");
	m_lavaTex[1].Load("Texture/GimmickBlock/liquidLava1.png");
	m_lavaTex[2].Load("Texture/GimmickBlock/liquidLava2.png");
	m_lavaTex[3].Load("Texture/GimmickBlock/liquidLava3.png");
	m_lavaTex[4].Load("Texture/GimmickBlock/liquidLava4.png");

	m_crateTex[0].Load("Texture/GimmickBlock/crate.png");

	m_voidTex.Load("Texture/GroundBlock/void.png");

	m_slimeSpawnerTex.Load("Texture/GimmickBlock/SlimeSpawner.png");
	m_snowBallSpawnerTex.Load("Texture/GimmickBlock/SnowBallSpawner.png");
	tmpTex.CreateRenderTarget(1280, 720);
	//m_blocks.push_back(Block(0, 0, 32, 32, &m_blockTex, false,   0));
	m_sKey = false;
	m_aKey = false;
	
	m_keyTexture[0].Load("Texture/Item/Key1.png");
	m_keyTexture[1].Load("Texture/Item/Key2.png");
	m_keyTexture[2].Load("Texture/Item/Key3.png");

	for (int i = 0; i < 3; i++)
	{
		m_itemLibrary.push_back(&m_keyTexture[i]);
	}
	
	
	m_backGround.Load("Texture/BackGround/Title.png");

	m_slimeTex.Load("Texture/Creature/slime.png");
	m_snowBallTex.Load("Texture/Creature/snowball.png");

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
		case BlockEditerSelect::IceWater:
			for (int l = 0; l < 5; l++)
			{
				_loadarray[l] = (&m_iceWaterBlockTex[l]);
			}
			_loadVector.push_back(_loadarray);
			break;
		case BlockEditerSelect::Ladder:
			for (int l = 0; l < 5; l++)
			{
				_loadarray[l] = (&m_ladderTex[l]);
			}
			_loadVector.push_back(_loadarray);
			break;
		case BlockEditerSelect::Lava:
			for (int l = 0; l < 5; l++)
			{
				_loadarray[l] = (&m_lavaTex[l]);
			}
			_loadVector.push_back(_loadarray);
			break;
		}
		m_blockLiblary[i] = _loadVector;
	}

	for (int i = 0; i < m_enemyNum; i++)
	{
		std::vector<KdTexture*> _loadvector;

		switch (i)
		{
		case EnemySelect::Slime:
			_loadvector.push_back(&m_slimeTex);
			break;
		case EnemySelect::SnowBall:
			_loadvector.push_back(&m_snowBallTex);
			break;
		}
		m_enemylibrary[i] = _loadvector;
	}

	m_player.SetScroll(&m_scroll);
}

void Scene::Release()
{
	// �摜�̉������
	//m_blockTex.Release();
	delete SC;
	m_stageBaseTex.Release();
	tmpTex.Release();
	m_playerTex.Release();
	m_playerHpTex.Release();
	m_blockTex.Release();
	m_backGround.Release();
	m_snowBallTex.Release();
	m_slimeTex.Release();
	m_voidTex.Release();
	m_snowBallSpawnerTex.Release();
	m_slimeSpawnerTex.Release();
	for (int i = 0; i < m_keyTexture.size(); i++)m_keyTexture[i].Release();
	for (int i = 0; i < m_groundTex.size(); i++)m_groundTex[i].Release();
	for (int i = 0; i < m_iceInsideTex.size(); i++)m_iceInsideTex[i].Release();
	for (int i = 0; i < m_iceSurfaceTex.size(); i++)m_iceSurfaceTex[i].Release();
	for (int i = 0; i < m_iceWaterBlockTex.size(); i++)m_iceWaterBlockTex[i].Release();
	for (int i = 0; i < m_ladderTex.size(); i++)m_ladderTex[i].Release();
	for (int i = 0; i < m_lavaTex.size(); i++)m_lavaTex[i].Release();
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
		if (m_player.GetMoveBlock(0))
		{
			ImGui::Text("Yes");
		}
		else
		{
			ImGui::Text("No");
		}
		ImGui::Text("%d", m_player.GetDirection());
		ImGui::Text("%f", m_player.GetAngle());
		ImGui::Text("Mouse x %d", m_mouse.x);
		ImGui::Text("Mouse y  %d", m_mouse.y);
		ImGui::Text("Player x %f", m_player.GetGPos().first);
		ImGui::Text("Player y  %f", m_player.GetGPos().second);
		ImGui::Text("%d", m_player.GetColissionDataSize());
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
