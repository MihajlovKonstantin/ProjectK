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
	case 1:
		text = "�ړ�����̂��ߖ��L�[������";
		break;
	case 2:
		text = "Jump�̂��߂�Space������";
		break;
	case 3: 
		text = "CreateMode���J���̂���E�L�[����";
		break;
	case 4:
		text = "Space�������Ȃ���`���A�����A�Ȃ�";
		break;
	case 5:
		text = "Lava��G�ȂǓ����蔻�肪����ƃ_���[�W���󂯂�";
		break;
	case 6:
		text = "Lader�ɏ��̂��ߖ��L�[������";
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

