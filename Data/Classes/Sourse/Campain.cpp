#include "Pch.h"

Campain::Campain()
{
}

void Campain::CreateCampain(std::vector<std::string> data,std::vector<int> visData)
{
	m_data.clear();
	CampainMapStatus _newData;
	for (size_t i = 0; i < data.size(); i++)
	{
		_newData = { data[i],visData[i],0};
		m_data.push_back(_newData);
	}
	m_data[0].visableStatus = 1;
}

bool Campain::CheckData(std::vector<std::string> data)
{
	if (m_data.size() != data.size())
	{
		return false;
	}
	for (size_t i = 0; i < data.size();i++)
	{
		if (m_data[i].name != data[i])
		{
			return false;
		}
	}
	return true;
}
