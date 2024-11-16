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
	/*
	if (WC->IsPause())
	{

		for (int i = 0; i < m_inGameSetting.GetButtonsCNT(); i++)
		{
			DrawButton(m_inGameSetting.GetButton(i));
		}
		for (int i = 0; i < m_inGameSetting.GetButtonsCNT(); i++)
		{
			DrawButtonText(m_inGameSetting.GetButton(i));
		}
	}
	else
	{
		SHADER.m_spriteShader.SetMatrix(matrix);
		SHADER.m_spriteShader.DrawTex(&charaTex, charaRect, 1.0f);
	}
	*/
	
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
		SHADER.m_spriteShader.SetMatrix(m_block.GetMatrix());
		SHADER.m_spriteShader.DrawTex(m_block.GetTexture(), m_block.GetRectangle());
	}
	
}
/*
void Scene::InitAssets()
{
	/*
	KdTexture _result;
	_result.ClearRenerTarget(Math::Color(1, 1, 1, 1));
	_result.SetRenderTarget();
	
	std::pair<int, int> _startPos = { 2,0 };
	std::array<std::array<int, 6>, 5> _base;//Base field
	std::vector<std::pair<int, int>>_possiblePair;// PossiblePlacement
	std::vector<std::pair<int, int>>_possibleDirection;//This Vector is parralell to Possible Pair. Here is pair antogonistick direction for generation
	std::vector<size_t> _pAdress;
	//std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> _possibleCollection;//Collection of last two vector
	std::vector<Box> _result;//Result from function
	std::random_device _rd;
	std::mt19937 _gen(_rd());
	std::uniform_int_distribution<> _distrib(1, 4);//Randomize size of big room
	bool _connectWithStartFlag = false;

	//Make all field free
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			_base[i][j] = 0;
		}
	}
	try
	{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++)
		{
			int _randomNum = _distrib(_gen);//Select max size of room

			if (_base[i][j] == 0)//If block is free try to fill
			{
				_base[i][j] = 1;//Start position become filled
				Box _newBox;

				_newBox.m_room.push_back({ i, j });//Push start position in new Box, and try to find all free direction for each block in box
				
				while (_newBox.m_room.size() < _randomNum)
				{
						_possiblePair.clear();
						_possibleDirection.clear();
						_pAdress.clear();
						for (size_t p = 0; p < _newBox.m_room.size(); ++p) {
							auto pos = _newBox.m_room[p];
							if (pos.m_first - 1 > 0) {
								if (ItsFree(_base, { pos.m_first - 1, pos.m_second })) {
									_possiblePair.push_back({ pos.m_first - 1, pos.m_second });
									_possibleDirection.push_back({ Direction::Up,Direction::Down });
									_pAdress.push_back(p);
								}
							}
							if (pos.m_first + 1 < 4) {
								if (ItsFree(_base, { pos.m_first + 1, pos.m_second })) {
									_possiblePair.push_back({ pos.m_first + 1, pos.m_second });
									_possibleDirection.push_back({ Direction::Down,Direction::Up });
									_pAdress.push_back(p);
								}
							}
							if (pos.m_second - 1 > 0) {
								if (ItsFree(_base, { pos.m_first, pos.m_second - 1 })) {
									_possiblePair.push_back({ pos.m_first, pos.m_second - 1 });
									_possibleDirection.push_back({ Direction::Left,Direction::Right });
									_pAdress.push_back(p);
								}
							}
							if (pos.m_second + 1 < 5) {
								if (ItsFree(_base, { pos.m_first, pos.m_second + 1 })) {
									_possiblePair.push_back({ pos.m_first, pos.m_second + 1 });
									_possibleDirection.push_back({ Direction::Right,Direction::Left });
									_pAdress.push_back(p);
								}
							}
						}
						//if we have free direction - chose random dirrection->chose random position for enter->push open statement
						if (!_possiblePair.empty()) {

							std::uniform_int_distribution<> __distrib(0, _possiblePair.size() - 1);
							std::uniform_int_distribution<> __distribSecond(0, 2);
							int __firstRandNum = __distrib(_gen);
							int __secondRandNum = __distribSecond(_gen);
							Room _pData = { _possiblePair[__firstRandNum].first,_possiblePair[__firstRandNum].second };
							int _sizeT = _pAdress[__firstRandNum];
							std::pair<int, int> __pPair = { _possibleDirection[__firstRandNum].second ,__secondRandNum };
							_pData.m_openStatement.push_back(__pPair);
							_newBox.m_room.push_back(_pData);
							_newBox.m_room.at(_sizeT).m_openStatement.push_back({ _possibleDirection[__firstRandNum].first, __secondRandNum });

							_base[_possiblePair[__firstRandNum].first][_possiblePair[__firstRandNum].second] = 1;
						}
						else {
							break;
						}
					};
				//If we still dont find the Box with start position -> check current
				if (_connectWithStartFlag==false)
				{
					for (int k = 0; k < _newBox.m_room.size(); k++)
					{
						if ((_newBox.m_room[k].m_first == _startPos.first) && (_newBox.m_room[k].m_second == _startPos.second))
						{
							_newBox.m_connectedWithStart = true;
						}
					}
				}
				_result.push_back(_newBox);
			}
		}


	}
	}
	catch (exception)
	{
		//error message
	};
	_result;
	//Found all room nearby
	int _countOfBox = _result.size();
	for (int i = 0; i < _countOfBox;i++)//first box
	{

		for (int j = i+1; j < _countOfBox; j++)//second box
		{
			int __blockFB = _result.at(i).m_room.size();
			int __blockSB = _result.at(j).m_room.size();
			for (int k = 0; k < __blockFB; k++)
			{
				for (int l = 0; l < __blockSB; l++)
				{
					int __firstBlock[2] = {_result[i].m_room[k].m_first,_result[i].m_room[k].m_second };
					int __secondBlock[2] = { _result[j].m_room[l].m_first, _result[j].m_room[l].m_second };
					if ((pow(__firstBlock[0] - __secondBlock[0], 2) + pow(__firstBlock[1] - __secondBlock[1], 2)) < 2)
					{
						_result[i].m_nearbyRoom.push_back(j);
						_result[j].m_nearbyRoom.push_back(i);
						goto next;
					}
				}
			}
		next:;
		}
	
	}
	std::vector<std::unique_ptr<Box*>> _uniqueVector;//vector for all unconnected box
	std::vector<int> _connectedWithStart;
	struct _PossiblePair
	{
		std::pair<int, int> _boxIndex;//first index - unique index, second - global(result) index
		std::pair<int, int> _blockIndex;//index of selected block in boxes
		std::pair<int, int> _possibleDirection;//dirrection for connections
	};
	std::vector<_PossiblePair> _PPVector;
	for (int i = 0; i < _result.size(); i++)
	{
		_uniqueVector.push_back(make_unique<Box*>(&_result[i]));
	}
	do
	{
		for (int i = 0; i < _uniqueVector.size(); i++)
		{
			_PPVector.clear();
			_connectedWithStart.clear();
			auto __nearbyRoomCopy = (*_uniqueVector[i])->m_nearbyRoom;
			if ((*_uniqueVector[i])->m_connectedWithStart == false)
			{
				int __nearbyRoomCount = __nearbyRoomCopy.size();
				for (int j = 0; j < __nearbyRoomCount; j++)
				{
					if (_result[__nearbyRoomCopy[j]].m_connectedWithStart == true)
					{
						_connectedWithStart.push_back(__nearbyRoomCopy[j]);
					}
				}
				if (_connectedWithStart.empty() != true)
				{
					int __blockFB = (*_uniqueVector[i])->m_room.size();
					int __connectedWSCount = _connectedWithStart.size();
					for (int j = 0; j < __connectedWSCount; j++)
					{
						int __globalIndexSB = _connectedWithStart[j];
						Box* __SBInstance =  &_result[__globalIndexSB];
						int __blockSB = __SBInstance->m_room.size();
						for (int k = 0; k < __blockFB; k++)
						{
							for (int l = 0; l < __blockSB; l++)
							{
								Room __FBData = (*_uniqueVector[i])->m_room[k];
								Room __SBData = __SBInstance->m_room[l];
								_PossiblePair __newPP;
								if ((std::abs(__FBData.m_first - __SBData.m_first) < 2) && (std::abs(__FBData.m_second - __SBData.m_second) < 2) && ((std::abs(__FBData.m_second - __SBData.m_second) + std::abs(__FBData.m_first - __SBData.m_first))<2))
								{
									__newPP._boxIndex = { i,_connectedWithStart[j] };
									__newPP._blockIndex = { k,l };
									if (__FBData.m_first > __SBData.m_first)
									{
										__newPP._possibleDirection = { Direction::Up,Direction::Down };
									}
									
									if (__FBData.m_first < __SBData.m_first)
									{
										__newPP._possibleDirection = { Direction::Down,Direction::Up };
									}
									if (__FBData.m_second > __SBData.m_second)
									{
										__newPP._possibleDirection = { Direction::Left,Direction::Right };
									}
									if (__FBData.m_second <__SBData.m_second)
									{
										__newPP._possibleDirection = { Direction::Right,Direction::Left };
									}
									_PPVector.push_back(__newPP);
								}
							}
						}
					}
				std::uniform_int_distribution<>__PPDistrib(0, _PPVector.size() - 1);
				std::uniform_int_distribution<>__positionDistrib(0,2);
				int __selectedPPVectorIndex = __PPDistrib(_gen);
				int __selectedPosition = __positionDistrib(_gen);
				_PossiblePair __selectedPP = _PPVector[__selectedPPVectorIndex];
				(*_uniqueVector[__selectedPP._boxIndex.first])->m_room[__selectedPP._blockIndex.first].m_openStatement.push_back({ __selectedPP._possibleDirection.first,__selectedPosition });
				_result[__selectedPP._boxIndex.second].m_room[__selectedPP._blockIndex.second].m_openStatement.push_back({ __selectedPP._possibleDirection.second,__selectedPosition });
				(*_uniqueVector[i])->m_connectedWithStart = true;
				}
			}
			else
			{
				auto __p = _uniqueVector.begin();
				_uniqueVector.erase(__p + i);
			}
		}

	} while (_uniqueVector.empty() != true);
	_result;
	std::array<std::array<Room, 6>, 5> Result;
	for (int i = 0; i < _result.size(); i++)
	{
		Box __currentBox = _result[i];
		for (int j = 0; j < __currentBox.m_room.size(); j++)
		{
			ConnectedRoom __subCR;
			for (int k = 0; k < __currentBox.m_room[j].m_openStatement.size(); k++)
			{
				switch (__currentBox.m_room[j].m_openStatement[k].first)
				{
				case Direction::Up:
					__subCR.m_indexRoom = { __currentBox.m_room[j].m_first-1,__currentBox.m_room[j].m_second };
						break;
				case Direction::Right:
					__subCR.m_indexRoom = { __currentBox.m_room[j].m_first,__currentBox.m_room[j].m_second+1 };
					break;
				case Direction::Down:
					__subCR.m_indexRoom = { __currentBox.m_room[j].m_first + 1,__currentBox.m_room[j].m_second };
					break;
				case Direction::Left:
					__subCR.m_indexRoom = { __currentBox.m_room[j].m_first,__currentBox.m_room[j].m_second - 1 };
					break;
				}
				
				__currentBox.m_room[j].m_connectedRoomData.push_back(__subCR);

				__currentBox.m_room[j].m_border[Direction::Up] = 720 * (Result.size()-1 - __currentBox.m_room[j].m_first) + 360;
				__currentBox.m_room[j].m_border[Direction::Down] = 720 *(Result.size()-1 - __currentBox.m_room[j].m_first) - 360+1;
				__currentBox.m_room[j].m_border[Direction::Right] = 1280 * __currentBox.m_room[j].m_second + 640;
				__currentBox.m_room[j].m_border[ Direction::Left ] = 1280 * __currentBox.m_room[j].m_second - 640+1;
			}
			Result[__currentBox.m_room[j].m_first][__currentBox.m_room[j].m_second] = __currentBox.m_room[j];
		}
	}
	Result;
}
bool Scene::ItsFree(std::array<std::array<int, 6>, 5> base, std::pair<int,int> pos)
{
	if (base[pos.first][pos.second] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
*/
void Scene::Update()
{
	//
	if (!WC->IsPause())
	{
		test = m_player.CollisionToBlock(m_block, NULL);
		if (test)
		{
			m_player.Stop();
		}
		m_player.Update();
		m_block.Update();
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
	//Test
	
	//if(GetAsyncKeyState(VK_UP))
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
	m_charaTex.Load("Texture/Object/RedBox.png");;
	charaRect = Math::Rectangle(0, 0, 32, 32);
	//
	tmpTex.CreateRenderTarget(1280, 720);
}

void Scene::Release()
{
	// 画像の解放処理
	m_charaTex.Release();
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
		ImGui::Text("%f", m_player.GetAngle());
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
