#include "Data/Classes/Header/InformPanel.h"

InformPanel::InformPanel()
{
}

InformPanel::InformPanel(std::pair<float, float> pos, int index)
{
	m_gPos = pos;
	m_index = index;
	switch (m_index)
	{
	case 0:
		text = "移動するのため矢印キーを押す";
		break;
	case 1:
		text = "JumpのためにSpaceを押す";
		break;
	case 2: 
		text = "CreateModeを開くのためEキー押す";
		break;
	case 3:
		text = "Spaceを押しながら描く、消す、など";
		break;
	case 4:
		text = "Lavaや敵など当たり判定があるとダメージを受ける";
		break;
	case 5:
		text = "Laderに上るのため矢印キーを押す";
		break;
	}
}

std::string InformPanel::GetText()
{
	return text;
}

std::pair<float, float> InformPanel::GetGPos()
{
	return m_gPos;
}

int InformPanel::GetIndex()
{
	return m_index;
}

