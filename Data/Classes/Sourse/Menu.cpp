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
	m_pos.first -= 0.05f;
	if (m_pos.first < -1280.0f)
	{
		m_pos.first = 0;
	}
	if (GetSelectMapMenuState())
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
			if (((dataBlockIndex+1) * 9 > lastMapIndex) && (dataBlockIndex != 0))
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
	Button _newButton = Button({ 200.0f, 40.0f }, { 0.0f, 170.0f }, "Start",1.0f,1,1,5);
	buttons.push_back(_newButton);
	_newButton = Button({ 200.0f, 40.0f }, { 0.0f, 50.0f }, "Setting",1.0f,1,1,3);
	buttons.push_back(_newButton);
	_newButton = Button({ 200.0f, 40.0f }, { 0.0f, -70.0f }, "Record",1.0f,3,0,0);
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
	_newButton = Button({ 100.0f,40.0f }, { 350.0f,170.0f }, "Push", 1.0f, 1, 9, 0);
	buttons.push_back(_newButton);
}

void Menu::InitSetting()
{
	buttons.clear();
	Button _newButton = Button({ 60.0f, 40.0f }, { -500.0f, 200.0f }, "EXIT",1.0f,1,1,1);
	Button _musicButton = Button({ 80.0f,40.0f }, { 300.0f,100.0f }, "Music-", 1.0f, 3, 3, 21);
	buttons.push_back(_newButton);
	buttons.push_back(_musicButton);
	_musicButton = Button({ 80.0f,40.0f }, { 300.0f,230.0f }, "Music+", 1.0f, 3, 2, 21);
	buttons.push_back(_musicButton);
}
void Menu::InitInGameSetting()
{
	buttons.clear();
	Button _newButton = Button({ 100.0f, 40.0f }, { -300.0f, 0.0f }, "Exit", 1.0f, 1, 1, 1);
	buttons.push_back(_newButton);
}
void Menu::InitSelectMap(std::vector<std::string> mapList, std::string path,std::string dataPath)
{
	IsSelectMapMenu = true;
	m_dataPath = dataPath;
	buttons.clear();
	Button _newButton;
	selectedPath = path;
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
	_newButton = Button({60.0f,40.0f }, { -500.0f,-200.0f }, "Open", 1.0f, 1025, 7, 2);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f,40.0f }, { -350.0f,-200.0f }, "New", 1.0f, 1025, 8, 2);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f, 40.0f }, { -500.0f, 200.0f }, "EXIT", 1.0f, 1026, 1, 1);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f,40.0f }, { 0.0f,300.0f }, "Last", 1.0f, 1027, 3, 31);
	buttons.push_back(_newButton);
	_newButton = Button({ 60.0f,40.0f }, { 0.0f,-300.0f }, "Next", 1.0f, 1027, 2, 31);
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

void Menu::EventClick(array<int, 2> eventData)
{
	string _dirFinder;
	std::ofstream ofFile;
	std::ifstream inFile;
	std::string _line;
	//char current_work_dir[FILENAME_MAX];
	//_getcwd(current_work_dir, sizeof(current_work_dir));
	switch (eventData[0])
	{
	case 1:
		SwitchWindowsEvent(eventData[1]);
		break;
	case 2:
		IncreaceByIndex(eventData[1]);
		break;
	case 3:
		DecreaceByIndex(eventData[1]);
		break;
	case 4:
		data->SetEndState(true);
		break;
	case 5:
		SwitchBoolEvent(eventData[1]);
		break;
	case 6:
		selectedMap = buttons[eventData[1]].GetText();
		break;
	case 7:
		
		_dirFinder = " copy \"" + selectedPath + "\\" + selectedMap + "\" \"" + m_dataPath + "\"";
		system(_dirFinder.c_str());
		_dirFinder = "del \"" + m_dataPath + "\\CurrentMap.map\"";
		system(_dirFinder.c_str());
		_dirFinder = "rename \"" + m_dataPath + "\\" + selectedMap + "\" CurrentMap.map";
		system(_dirFinder.c_str());
		data->SetMap(selectedMap);
		data->SetPath(selectedPath);
		SwitchWindowsEvent(eventData[1]);
		break;
	case 8:
		_dirFinder = "echo. > \""+selectedPath+"\\NewMap.map\"";
		system(_dirFinder.c_str());
		_dirFinder = "" + selectedPath + "\\NewMap.map";
		ofFile = ofstream(_dirFinder);
		ofFile << "NewMap.map" << endl;
		ofFile << selectedPath << endl;
		ofFile << 0 << endl;
		ofFile << 0<< endl;
		ofFile << 0 << endl;
		ofFile << 0 << endl;
		ofFile.close();
		selectedMap = "NewMap.map";
		_dirFinder = " copy \"" + selectedPath + "\\" + selectedMap + "\" \"" + m_dataPath + "\"";
		system(_dirFinder.c_str());
		_dirFinder = "del \"" + m_dataPath + "\\CurrentMap.map\"";
		system(_dirFinder.c_str());
		_dirFinder = "rename \"" + m_dataPath + "\\" + selectedMap + "\" CurrentMap.map";
		system(_dirFinder.c_str());
		data->SetMap(selectedMap);
		data->SetPath(selectedPath);
		SwitchWindowsEvent(eventData[1]);
		break;
	case 9:
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
		}

		
		break;
	}

}

void Menu::SwitchWindowsEvent(int newWindowsIndex)
{
	data->SetWindow(newWindowsIndex);
}

void Menu::IncreaceByIndex(int dataIndex)
{
	float _currentValue;
	switch (dataIndex)
	{
	case 21:
		_currentValue = data->GetMusicVolume();
		_currentValue += 0.001f;
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
	}
}

void Menu::DecreaceByIndex(int dataIndex)
{
	float _currentValue;
	switch (dataIndex)
	{
	case 21:
		_currentValue = data->GetMusicVolume();
		_currentValue -= 0.001f;
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

void Menu::SetColdown()
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

void Menu::SendMap()
{
	std::string _dirFinder = "delete \"" + selectedPath + "\\" + selectedMap + "\"";
	system(_dirFinder.c_str());
	_dirFinder = "copy \"" + m_dataPath + "\\CurrentMap.map\" \"" + selectedPath + "\"";
	system(_dirFinder.c_str());
	_dirFinder = "rename \"" + selectedPath + "\\CurrentMap.map\" \"" + selectedMap + "\"";
	system(_dirFinder.c_str());
}



