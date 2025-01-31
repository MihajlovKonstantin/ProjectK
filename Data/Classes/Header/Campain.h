#pragma once
class Campain
{
	struct CampainMapStatus
	{
		std::string name;
		int visableStatus;
		int clearStatus;
	};
	
public:
	std::vector <CampainMapStatus> m_data;
	Campain();
	void CreateCampain(std::vector<std::string> data);
	bool CheckData(std::vector<std::string> data);
};

