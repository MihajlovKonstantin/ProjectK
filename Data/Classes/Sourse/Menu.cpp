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
	m_matrix = Math::Matrix::CreateTranslation(m_pos.first, m_pos.second, 0);
}

Menu::Menu()
{

}

void Menu::InitMainMenu()
{
	buttons.clear();
	Button _newButton = Button({ 200.0f, 40.0f }, { 0.0f, 170.0f }, "Start",1.0f,1,1,2);
	buttons.push_back(_newButton);
	_newButton = Button({ 200.0f, 40.0f }, { 0.0f, 50.0f }, "Setting",1.0f,1,1,3);
	buttons.push_back(_newButton);
	_newButton = Button({ 200.0f, 40.0f }, { 0.0f, -70.0f }, "Record",1.0f,3,0,0);
	buttons.push_back(_newButton);
}

void Menu::InitSetting()
{
	buttons.clear();
	Button _newButton = Button({ 60.0f, 40.0f }, { -500.0f, 200.0f }, "EXIT",1.0f,1,1,1);
	buttons.push_back(_newButton);
}
void Menu::InitInGameSetting()
{
	buttons.clear();
	Button _newButton = Button({ 100.0f, 40.0f }, { -300.0f, 0.0f }, "Exit", 1.0f, 1, 1, 1);
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
	}
}

void Menu::SwitchWindowsEvent(int newWindowsIndex)
{
	data->SetWindow(newWindowsIndex);
}

void Menu::IncreaceByIndex(int dataIndex)
{
	switch (dataIndex)
	{
	case 21:
		float _currentValue = data->GetMusicVolume();
		_currentValue += 0.1;
		if (_currentValue > 1.0f)
		{
			_currentValue = 1.0f;
		}
		data->SetMusicVolume(_currentValue);
		break;
	}
}

void Menu::DecreaceByIndex(int dataIndex)
{
	switch (dataIndex)
	{
	case 21:
		float _currentValue = data->GetMusicVolume();
		_currentValue -= 0.1;
		if (_currentValue < 0.0f)
		{
			_currentValue = 0.0f;
		}
		data->SetMusicVolume(_currentValue);
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



