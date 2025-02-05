#pragma once
#include "Data/Classes/Header/Menu.h"

KdTexture* Menu::GetTexture()
{
	return m_texture;
}

void Menu::SetTexture(KdTexture* texture)
{
	m_texture = texture;
}

Math::Matrix Menu::GetMatrix()
{
	return m_matrix;
}

Math::Rectangle Menu::GetRect()
{
	return m_rect;
}

void Menu::Update()
{
	D3D.GetDevContext()->ClearRenderTargetView(D3D.GetBackBuffer(), Math::Color(0.0f, 0.0f, 0.0f, 1));
	D3D.GetDevContext()->ClearDepthStencilView(D3D.GetZBuffer(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	m_pos.first -= 0.05;
	if (m_pos.first < -1280.0f)
	{
		m_pos.first = 0;
	}
	if (inputMode)
	{
		for (char c = 'A'; c <= 'Z'; ++c)
		{
			if (GetAsyncKeyState(c) & 0x8000)
			{
				inputUser += tolower(c);
				Sleep(100);
			}
		}
		for (char c = '0'; c <= '9'; ++c)
		{
			if (GetAsyncKeyState(c) & 0x8000) 
			{
				inputUser += c;
				Sleep(100);
			}
		}
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) 
		{
			inputMode = false;
			endInput = true;
		} 
		if (GetAsyncKeyState(VK_BACK) & 0x8000)
		{
			if(!inputUser.empty())
			{
				inputUser.resize(inputUser.size() - 1);
			}
			
			Sleep(100);
		}
	}
	if (GetSelectMapMenuState())
	{
		if (!IsCampainMenu)
		{
			if (IsDirty())
			{
				int firstVisableIndex = 0, lastVisableIndex = 0, lastMapIndex = 0, dataBlockIndex = 0;
				lastMapIndex = GetMapNum();
				dataBlockIndex = GetBlockData();
				if ((dataBlockIndex == 0) && (lastMapIndex < 9))
				{
					for (int i = 0; i < lastMapIndex; i++)
					{
						buttons[i].SetVisable(true);
						buttons[i].SetActive(true);
					}
				}
				if (((dataBlockIndex + 1) * 9 > lastMapIndex) && (dataBlockIndex != 0))
				{
					int i;
					for (i = 0; i < dataBlockIndex * 9; i++)
					{
						buttons[i].SetVisable(false);
						buttons[i].SetActive(false);
					}
					for (i = dataBlockIndex * 9; i < lastMapIndex; i++)
					{
						buttons[i].SetVisable(true);
						buttons[i].SetActive(true);
					}
				}
				if ((dataBlockIndex == 0) && (lastMapIndex >= 9))
				{
					int i;
					for (i = 0; i < 9; i++)
					{
						buttons[i].SetVisable(true);
						buttons[i].SetActive(true);
					}
					for (i = 9; i < lastMapIndex; i++)
					{
						buttons[i].SetVisable(false);
						buttons[i].SetActive(false);
					}
				}
				if ((dataBlockIndex != 0) && ((dataBlockIndex + 1) * 9 <= lastMapIndex))
				{
					int i;
					for (i = 0; i < dataBlockIndex * 9; i++)
					{
						buttons[i].SetVisable(false);
						buttons[i].SetActive(false);
					}
					for (i = dataBlockIndex * 9; i < (dataBlockIndex + 1) * 9; i++)
					{
						buttons[i].SetVisable(true);
						buttons[i].SetActive(true);
					}
					for (i = (dataBlockIndex + 1) * 9; i < lastMapIndex; i++)
					{
						buttons[i].SetVisable(false);
						buttons[i].SetActive(false);
					}
				}
				SetDirty(false);
			}
		}
		else
		{
			if (inputMode)
			{

			}
			if (IsDirty())
			{
				int firstVisableIndex = 0, lastVisableIndex = 0, lastMapIndex = 0, dataBlockIndex = 0;
				lastMapIndex = GetMapNum();
				dataBlockIndex = GetBlockData();
				if ((dataBlockIndex == 0) && (lastMapIndex < 9))
				{
					for (int i = 0; i < lastMapIndex; i++)
					{
						buttons[i].SetVisable(true);
						buttons[i].SetActive(true);
					}
				}
				if (((dataBlockIndex + 1) * 9 > lastMapIndex) && (dataBlockIndex != 0))
				{
					int i;
					for (i = 0; i < dataBlockIndex * 9; i++)
					{
						buttons[i].SetVisable(false);
						buttons[i].SetActive(false);
					}
					for (i = dataBlockIndex * 9; i < lastMapIndex; i++)
					{
						buttons[i].SetVisable(true);
						buttons[i].SetActive(true);
					}
				}
				if ((dataBlockIndex == 0) && (lastMapIndex >= 9))
				{
					int i;
					for (i = 0; i < 9; i++)
					{
						buttons[i].SetVisable(true);
						buttons[i].SetActive(true);
					}
					for (i = 9; i < lastMapIndex; i++)
					{
						buttons[i].SetVisable(false);
						buttons[i].SetActive(false);
					}
				}
				if ((dataBlockIndex != 0) && ((dataBlockIndex + 1) * 9 <= lastMapIndex))
				{
					int i;
					for (i = 0; i < dataBlockIndex * 9; i++)
					{
						buttons[i].SetVisable(false);
						buttons[i].SetActive(false);
					}
					for (i = dataBlockIndex * 9; i < (dataBlockIndex + 1) * 9; i++)
					{
						buttons[i].SetVisable(true);
						buttons[i].SetActive(true);
					}
					for (i = (dataBlockIndex + 1) * 9; i < lastMapIndex; i++)
					{
						buttons[i].SetVisable(false);
						buttons[i].SetActive(false);
					}
				}
				SetDirty(false);
			}
		}
		
	}
	if (currentColdown > 0)
	{
		currentColdown--;
	}
	m_matrix = Math::Matrix::CreateTranslation(m_pos.first, m_pos.second, 0);
}


Menu::Menu()
{

}

void Menu::InitMainMenu(std::string dataPath)
{
	m_dataPath = dataPath;
	buttons.clear();
	Button _newButton = Button({ 80.0f,45.0f }, { 0.0f,-60.0f }, "Start", 1.5f, 0, goScene, SceneSelect::StartScreen);
	buttons.push_back(_newButton);
	_newButton = Button({ 120.0f, 45.0f }, { 0.0f, -180.0f }, "Setting",1.5f,change,goScene,Option);
	buttons.push_back(_newButton);
	_newButton = Button({ 70.0f, 45.0f }, { 0.0f, -300.0f }, "Help", 1.5f, change, goScene, Help);
	buttons.push_back(_newButton);
	std::string _dirrectory = dataPath + "\\CurrentMap.map";
	std::ifstream ifFile(_dirrectory);
	if (ifFile.is_open())
	{
		std::string line;
		getline(ifFile, line);
		selectedMap = line;
		getline(ifFile, line);
		selectedPath = line;
	}
	ifFile.close();
	
}

void Menu::InitSetting()
{
	buttons.clear();
	Button _newButton = Button({ 60.0f, 40.0f }, { -500.0f, 170.0f }, "EXIT",1.5f,change,goScene,Title);
	Button _musicButton = Button({ 120.0f,40.0f }, { 300.0f,90.0f }, " Music-", 1.5f, nochange, decreaseByIndex, volume);
	buttons.push_back(_newButton);
	buttons.push_back(_musicButton);
	_musicButton = Button({ 120.0f,40.0f }, { 300.0f,250.0f }, " Music+", 1.5f, nochange, increaseByIndex, volume);
	buttons.push_back(_musicButton);
}
void Menu::InitInGameSetting()
{
	buttons.clear();
	Button _newButton = Button({ 100.0f, 40.0f }, { -300.0f, 0.0f }, "Exit", 1.5f, change, goScene, Title);
	buttons.push_back(_newButton);
}
void Menu::InitSelectMapPlayeble(std::vector<std::string> mapList, std::string path,std::string dataPath)
{
	dirty = true;
	selectedBlockData = 0;
	IsSelectMapMenu = true;
	m_dataPath = dataPath;
	buttons.clear();
	Button _newButton;
	selectedPath = path;
	newPath = dataPath + "\\EditMap";
	int dX = 0, dY = 0;
	for (size_t i = 0; i < mapList.size(); i++)
	{
		switch (i % 3)
		{
		case 0:
			dX = 0;
			break;
		case 1:
			dX = 300;
			break;
		case 2:
			dX = 600;
			break;
		}
		div_t _index = div(i, 9);
		_index = div(_index.rem, 3);
		switch (_index.quot)
		{
		case 0:
			dY = 0;
			break;
		case 1:
			dY = -100;
			break;
		case 2:
			dY = -200;
			break;
		}
		_newButton = Button({ 100.0f,40.0f }, { -300.0f+dX,200.0f+dY }, mapList[i], 0.5f, i, 6, i);
		_newButton.ChangeVisiable();
		_newButton.ChangeActive();
		buttons.push_back(_newButton);
	}
	maxBlockData = buttons.size() / 9;
	mapNum = buttons.size();
	_newButton = Button({ 60.0f,40.0f }, { -500.0f,-200.0f }, "Open", 1.0f, 1025, openMap, SceneSelect::Game);
	//buttons.push_back(_newButton);
	//_newButton = Button({ 60.0f,40.0f }, { -350.0f,-200.0f }, "New", 1.0f, 1025, newMap, SceneSelect::Game);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f, 40.0f }, { -500.0f, 200.0f }, "EXIT", 1.0f, 1026, OptionSelect::goScene, StartScreen);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f,40.0f }, { 0.0f,300.0f }, "Last", 1.0f, 1027, decreaseByIndex, 31);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f,40.0f }, { 0.0f,-300.0f }, "Next", 1.0f, 1028, increaseByIndex, 31);
	buttons.push_back(_newButton);
}
void Menu::InitSelectEditingMap(std::vector<std::string> mapList, std::string path, std::string dataPath)
{
	dirty = true;
	selectedBlockData = 0;
	IsSelectMapMenu = true;
	m_dataPath = dataPath;
	buttons.clear();
	Button _newButton;
	selectedPath = path;
	newPath = dataPath + "\\Map";
	int dX = 0, dY = 0;
	for (size_t i = 0; i < mapList.size(); i++)
	{
		switch (i % 3)
		{
		case 0:
			dX = 0;
			break;
		case 1:
			dX = 300;
			break;
		case 2:
			dX = 600;
			break;
		}
		div_t _index = div(i, 9);
		_index = div(_index.rem, 3);
		switch (_index.quot)
		{
		case 0:
			dY = 0;
			break;
		case 1:
			dY = -100;
			break;
		case 2:
			dY = -200;
			break;
		}
		_newButton = Button({ 100.0f,40.0f }, { -300.0f + dX,200.0f + dY }, mapList[i], 0.5f, i, 6, i);
		_newButton.ChangeVisiable();
		_newButton.ChangeActive();
		buttons.push_back(_newButton);
	}
	maxBlockData = buttons.size() / 9;
	mapNum = buttons.size();
	_newButton = Button({ 60.0f,40.0f }, { -540.0f,-200.0f }, "Open", 1.0f, 1025, openMap, SceneSelect::Game);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f,40.0f }, { -390.0f,-200.0f }, "New", 1.0f, 1025, newMap, SceneSelect::Game);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f, 40.0f }, { -540.0f, 200.0f }, "EXIT", 1.0f, 1026, OptionSelect::goScene, StartScreen);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f,40.0f }, { 0.0f,300.0f }, "Last", 1.0f, 1027, decreaseByIndex, 31);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f,40.0f }, { 0.0f,-300.0f }, "Next", 1.0f, 1028, increaseByIndex, 31);
	buttons.push_back(_newButton);
	_newButton = Button({ 100.0f,40.0f }, { -500.0f,-100.0f }, "Release", 1.0f, 1029, OptionSelect::releaseMap, 0);
	buttons.push_back(_newButton);
}
void Menu::InitCampainMenu(std::vector<std::string> mapList, std::string dataPath)
{
	inputMode = false;
	endInput = false;
	inputUser = "";
	dirty = true;
	selectedBlockData = 0;
	IsSelectMapMenu = true;
	IsCampainMenu = true;
	m_dataPath = dataPath;
	buttons.clear();
	selectedPath = "C:\\Lessons\\DIGITAL WORKS\\ProjectK\\Data\\Map";
	Button _newButton;
	int dX = 0, dY = 0;
	{
		m_campain->m_data[0].visableStatus = 1;
		for (int i = 0; i < m_campain->m_data.size()-1;i++)
		{
			if (m_campain->m_data.size() != 1)
			{
				if (m_campain->m_data[i].clearStatus==1)
				{
					m_campain->m_data[i+1].visableStatus = 1;
				}
			}
			
		}
	}
	for (size_t i = 0; i < mapList.size(); i++)
	{
		switch (i % 3)
		{
		case 0:
			dX = 0;
			break;
		case 1:
			dX = 300;
			break;
		case 2:
			dX = 600;
			break;
		}
		div_t _index = div(i, 9);
		_index = div(_index.rem, 3);
		switch (_index.quot)
		{
		case 0:
			dY = 0;
			break;
		case 1:
			dY = -100;
			break;
		case 2:
			dY = -200;
			break;
		}
		if (m_campain->m_data[i].visableStatus)
		{
			_newButton = Button({ 100.0f,40.0f }, { -300.0f + dX,200.0f + dY }, mapList[i], 0.5f, i, 6, i);
			_newButton.ChangeVisiable();
			_newButton.ChangeActive();
			buttons.push_back(_newButton);
		}
		
	}
	maxBlockData = buttons.size() / 9;
	mapNum = buttons.size();
	_newButton = Button({ 60.0f,40.0f }, { -500.0f,-200.0f }, "Open", 1.0f, 1025, openMap, SceneSelect::Game);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f,40.0f }, { -350.0f,-200.0f }, "New", 1.0f, 1025, newMap, SceneSelect::Game);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f, 40.0f }, { -500.0f, 200.0f }, "EXIT", 1.0f, 1026, OptionSelect::goScene, StartScreen);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f,40.0f }, { 0.0f,300.0f }, "Last", 1.0f, 1027, decreaseByIndex, 31);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f,40.0f }, { 0.0f,-300.0f }, "Next", 1.0f, 1028, increaseByIndex, 31);
	buttons.push_back(_newButton);
	_newButton = Button({ 100.0f,40.0f }, { -500.0f,-100.0f }, "Release", 1.0f, 1029, OptionSelect::releaseMap, 0);
	buttons.push_back(_newButton);
}
void Menu::InitHelp()
{
	Button _newButton;
	buttons.clear();
	_newButton = Button({ 60.0f,40.0f }, { -400.0f,-200.0f }, "Next", 1.0f, 9, OptionSelect::increaseByIndex, DataValue::screenIdex);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f,40.0f }, { -500.0f,-200.0f }, "Back", 1.0f, 9, OptionSelect::decreaseByIndex, DataValue::screenIdex);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f,40.0f }, { -500.0f,0.0f }, "Exit", 1.5f, 9, OptionSelect::goScene, SceneSelect::Title);
	buttons.push_back(_newButton);
}
void Menu::InitStartScrene(std::string dataPath)
{
	m_dataPath = dataPath;
	Button _newButton;
	buttons.clear();
	_newButton = Button({ 70.0f, 45.0f }, { 0.0f, 0.0f }, "Play", 1.5f, change, goScene, SelectPlaybleMap);
	buttons.push_back(_newButton);
	_newButton = Button({ 120.0f, 45.0f }, { 300.0f, 0.0f }, "Campain", 1.5f, change, goScene, SceneSelect::CampainMenu);
	buttons.push_back(_newButton);
	_newButton = Button({ 70.0f, 45.0f }, { -300.0f, 0.0f }, "Edit", 1.5f, change, goScene, SceneSelect::SelectEditMap);
	buttons.push_back(_newButton);
	_newButton = Button({ 70.0f,45.0f }, { -300.0f,-160.0f }, "Push", 1.5f, change, updateMap, 0);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f, 40.0f }, { -500.0f, 200.0f }, "EXIT", 1.5f, change, goScene, Title);
	buttons.push_back(_newButton);
}
Button Menu::GetButton()
{
	return testButton;
}

Button Menu::GetButton(int cnt)
{
		return buttons[cnt];
}

int Menu::GetButtonsCNT()
{
	return buttons.size();
}
int ExtractNumber(const string& s)
{
	stringstream _ss(s);
	int _num;
	_ss >> _num;
	return _num;
}

void Menu::EventClick(array<int, 2> eventData)
{
	
	//char current_work_dir[FILENAME_MAX];
	//_getcwd(current_work_dir, sizeof(current_work_dir));
	switch (eventData[0])
	{
	case goScene:
		SwitchWindowsEvent(eventData[1]);
		break;
	case increaseByIndex:
		IncreaceByIndex(eventData[1]);
		break;
	case decreaseByIndex:
		DecreaceByIndex(eventData[1]);
		break;
	case setEndFlg:
		data->SetEndState(true);
		break;
	case switchBool:
		SwitchBoolEvent(eventData[1]);
		break;
	case selectMap:
		selectedMap.clear();
		data->SetCampainMapIndex(ExtractNumber(buttons[eventData[1]].GetText()));
		selectedMap = buttons[eventData[1]].GetText();
		break;
	case openMap:
		OpenMap(eventData[1]);
		break;
	case newMap:
		if (true)
		{
			if ((inputMode == false) && (endInput == false))
			{
				inputMode = true;
			}
			else
			{
				if (endInput == true)
				{
					_dirFinder = "echo. > \"" + selectedPath +"\\" + inputUser+".map\"";
					system(_dirFinder.c_str());
					_dirFinder = "" + selectedPath +"\\" + inputUser + ".map";
					ofFile = ofstream(_dirFinder);
					ofFile << inputUser+".map" << endl;
					ofFile << selectedPath << endl;
					ofFile << 0 << endl;
					ofFile << 0 << endl;
					ofFile << 0 << endl;
					ofFile << 0 << endl;
					ofFile.close();
					selectedMap = inputUser+".map";
					_dirFinder = " copy \"" + selectedPath + "\\" + selectedMap + "\" \"" + m_dataPath + "\"";
					system(_dirFinder.c_str());
					_dirFinder = "del \"" + m_dataPath + "\\CurrentMap.map\"";
					system(_dirFinder.c_str());
					_dirFinder = "rename \"" + m_dataPath + "\\" + selectedMap + "\" CurrentMap.map";
					system(_dirFinder.c_str());
					data->SetMap(selectedMap);
					data->SetPath(selectedPath);
					inputUser = "";
					endInput = false;
					inputMode = false;
					SwitchWindowsEvent(eventData[1]);
				}
			}
		}
		
		break;
	case updateMap:
		_dirFinder = m_dataPath + "\\CurrentMap.map";
		inFile = ifstream(_dirFinder.c_str());
		if (inFile.is_open())
		{
			std::getline(inFile, _line);
			selectedMap = _line;
			std::getline(inFile, _line);
			selectedPath = _line;
			std::getline(inFile, _line);
			inFile.close();
			if (!data->IsCampain())
			{
				if (stoi(_line) == 0)
				{
					_dirFinder = "del \"" + selectedPath + "\\" + selectedMap + "\"";
					system(_dirFinder.c_str());
					_dirFinder = "copy \"" + m_dataPath + "\\CurrentMap.map\" \"" + selectedPath + "\\\"";
					system(_dirFinder.c_str());
					_dirFinder = "rename \"" + selectedPath + "\\CurrentMap.map\" \"" + selectedMap + "\"";
					system(_dirFinder.c_str());
					_dirFinder = "del \"" + m_dataPath + "\\CurrentMap.map\"";
					system(_dirFinder.c_str());
				}
				data->Restart();
			}
			else
			{
				if (stoi(_line) == 0)
				{
					_dirFinder = "del \"" + selectedPath + "\\" + selectedMap + "\"";
					system(_dirFinder.c_str());
					_dirFinder = "copy \"" + m_dataPath + "\\CurrentMap.map\" \"" + selectedPath + "\\\"";
					system(_dirFinder.c_str());
					_dirFinder = "rename \"" + selectedPath + "\\CurrentMap.map\" \"" + selectedMap + "\"";
					system(_dirFinder.c_str());
					_dirFinder = "del \"" + m_dataPath + "\\CurrentMap.map\"";
					system(_dirFinder.c_str());
				}
				for (size_t i = 0;m_campain->m_data.size()>i;i++)
				{
					if (m_campain->m_data[i].name == selectedMap)
					{
						auto _clear = m_campain->m_data[i].clearStatus;
						if (!_clear)
						{
							m_campain->m_data[i].clearStatus = LastMapClearState;
						}
					}
				}
			}
		}
		data->Restart();
		break;
	case releaseMap:
		_dirFinder = selectedPath + "\\" + selectedMap;
		inFile = ifstream(_dirFinder.c_str());
		if (inFile.is_open())
		{
			std::getline(inFile, _line);
			selectedMap = _line;
			std::getline(inFile, _line);
			selectedPath = _line;
			std::getline(inFile, _line);
			if (stoi(_line) == 0)
			{
				while (std::getline(inFile, _line))
				{
					_lines.push_back(_line);
				}
				inFile.close();
				_dirFinder = newPath + "\\" + selectedMap;
				ofFile = ofstream(_dirFinder.c_str());
				{
					ofFile << "NewMap.map" << endl;
					ofFile << newPath << endl;
					ofFile << 1 << endl;

					for (const auto& l : _lines) {
						ofFile << l << std::endl;
					}
				}
				
			}
			ofFile.close();
		}

		
		break;
	}
	inFile.close();
	ofFile.close();
}

void Menu::SwitchWindowsEvent(int newWindowsIndex)
{
	if (newWindowsIndex == WindowsEnum::GameScene)
	{
		data->SetPreviousWindows(data->GetWindow());
	}
	data->SetWindow(newWindowsIndex);
}

void Menu::IncreaceByIndex(int dataIndex)
{
	float _currentValue;
	switch (dataIndex)
	{
	case DataValue::volume:
		_currentValue = data->GetMusicVolume();
		_currentValue += 0.01f;
		if (_currentValue > 1.0f)
		{
			_currentValue = 1.0f;
		}
		data->SetMusicVolume(_currentValue);
		break;
	case 31:
		selectedBlockData++;
		if (selectedBlockData > maxBlockData)
		{
			selectedBlockData = 0;
		}
		dirty = true;
		break;
	case DataValue::screenIdex:
		if (++m_helpPage > m_maxHelpPage)m_helpPage = m_maxHelpPage;
		break;
	}
}

void Menu::DecreaceByIndex(int dataIndex)
{
	float _currentValue;
	switch (dataIndex)
	{
	case DataValue::volume:
		_currentValue = data->GetMusicVolume();
		_currentValue -= 0.01f;
		if (_currentValue < 0.0f)
		{
			_currentValue = 0.0f;
		}
		data->SetMusicVolume(_currentValue);
		break;
	case 31:
		selectedBlockData--;
		if (selectedBlockData < 0)
		{
			selectedBlockData = maxBlockData;
		}
		dirty = true;
		break;
	case DataValue::screenIdex:
		if (--m_helpPage < 0)m_helpPage = 0;
		break;
	}
}

void Menu::SwitchBoolEvent(int dataIndex)
{
	switch (dataIndex)
	{
	case 22:
		if (data->IsStarted())
		{
			data->Restart();
		}
		else
		{
			data->StartGame();
		}
		break;
	case 23:
		if (data->IsPause())
		{
			data->Resume();
		}
		else
		{
			data->PauseGame();
		}
		break;
	}
}

void Menu::SetVisable(bool input)
{
	visable = input;
}

bool Menu::GetVisable()
{
	return visable;
}

void Menu::SetActive(bool input)
{
	active = input;
}

bool Menu::GetActive()
{
	return active;
}

std::string Menu::GetMap()
{
	return selectedMap;
}

std::string Menu::GetPath()
{
	return selectedPath;
}

bool Menu::GetSelectMapMenuState()
{
	return IsSelectMapMenu;
}

int Menu::GetMapNum()
{
	return mapNum;
}

int Menu::GetSelectedBlockData()
{
	return selectedBlockData;
}

int Menu::GetMaxBlockData()
{
	return maxBlockData;
}

bool Menu::IsDirty()
{
	return dirty;
}

int Menu::GetBlockData()
{
	return selectedBlockData;
}

void Menu::SetDirty(bool input)
{
	dirty = input;
}

void Menu::SetColdown(int coldownInterval)
{
	currentColdown = coldownInterval;
}

bool Menu::IsCD()
{
	if (currentColdown > 0)
	{
		return true;
	}
	return false;
}

void Menu::UpdateMap()
{
	std::string _dirFinder = "delete \"" + selectedPath + "\\" + selectedMap + "\"";
	system(_dirFinder.c_str());
	_dirFinder = "copy \"" + m_dataPath + "\\CurrentMap.map\" \"" + selectedPath + "\"";
	system(_dirFinder.c_str());
	_dirFinder = "rename \"" + selectedPath + "\\CurrentMap.map\" \"" + selectedMap + "\"";
	system(_dirFinder.c_str());
}

void Menu::ReleaseMap()
{
	std::string _dirFinder;
}

void Menu::SetClearState(int input)
{
	if (input == 1)
	{
		LastMapClearState = true;
	}
	else
	{
		LastMapClearState=  false;
	}
}

void Menu::AddCampain(Campain& data)
{
	m_campain = &data;
}

bool Menu::DrawInput()
{
	return inputMode||endInput;
}

void Menu::OpenMap(int input)
{

	_dirFinder = " copy \"" + selectedPath + "\\" + selectedMap + "\" \"" + m_dataPath + "\"";
	system(_dirFinder.c_str());
	_dirFinder = "del \"" + m_dataPath + "\\CurrentMap.map\"";
	system(_dirFinder.c_str());
	_dirFinder = "rename \"" + m_dataPath + "\\" + selectedMap + "\" CurrentMap.map";
	system(_dirFinder.c_str());
	data->SetMap(selectedMap);
	data->SetPath(selectedPath);
	SwitchWindowsEvent(input);
}




