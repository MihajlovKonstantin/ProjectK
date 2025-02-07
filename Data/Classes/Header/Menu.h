#pragma once
#include "Pch.h"
#include <optional>
#include "Src/Application/WindowsEnum.h"
using namespace std;
enum SceneSelect { Title = 1, Game = 2, Option, StartScreen, SelectPlaybleMap, SelectEditMap, CampainMenu, Help };
enum DataValue { volume = 21, screenIndex = 10 };
enum OptionSelect 
{
    goScene = 1, increaseByIndex = 2, decreaseByIndex = 3, setEndFlg = 4, switchBool = 5,
    selectMap = 6, openMap = 7, newMap = 8, updateMap = 9, releaseMap
};
enum ChangeSelect { change = 1, nochange = 3 };
class Menu
{
private:
    std::vector<Button> buttons;
    Button testButton;
    WindowsControlData* data;
    Campain* m_campain;
    bool visable;
    bool active;
    KdTexture* m_texture;
    Math::Rectangle m_rect = { 0,0,3840,720 };
    Math::Matrix m_matrix;
    std::pair<float, float> m_pos = { 0.0f,0.0f };
    std::string selectedMap;
    std::string selectedPath;
    std::string  m_dataPath;
    std::string newPath;
    int selectedBlockData = 0; //31 index
    int maxBlockData = 1;
    int mapNum;
    bool IsSelectMapMenu = false;
    bool IsCampainMenu = false;
    bool dirty = true;
    bool LastMapClearState = false;
    bool inputMode = false;
    bool endInput = false;
    int currentColdown = 0;
    int m_helpPage = 0;
    int m_maxHelpPage = 9;
    

    string _dirFinder;
    std::ofstream ofFile;
    std::ifstream inFile;
    std::string _line;
    std::vector<std::string> _lines;
public:
    std::string inputUser = "";
    KdTexture* GetTexture();
    void SetTexture(KdTexture* texture);
    Math::Matrix GetMatrix();
    Math::Rectangle GetRect();
    void Update();
    Menu();
    void InitMainMenu(std::string dataPath);
    void InitSetting();
    void InitInGameSetting();
    void InitSelectMapPlayeble(std::vector<std::string > mapList, std::string path, std::string dataPath);
    void InitSelectEditingMap(std::vector<std::string > mapList, std::string path, std::string dataPath);
    void InitCampainMenu(std::vector<std::string> mapList, std::string dataPath);
    void InitHelp();
    void InitStartScrene(std::string dataPath);
    Button GetButton();
    Button GetButton(int cnt);
    int GetButtonsCNT();
    void AddData(WindowsControlData& inputData)
    {
        data = &inputData;
    }
    void EventClick(array<int, 2> eventData);
    void SwitchWindowsEvent(int newWindowsIndex);
    void IncreaceByIndex(int dataIndex);
    void DecreaceByIndex(int dataIndex);
    void SwitchBoolEvent(int dataIndex);
    void SetVisable(bool input);
    bool GetVisable();
    void SetActive(bool input);
    bool GetActive();
    std::string GetMap();
    std::string GetPath();
    bool GetSelectMapMenuState();
    int GetMapNum();
    int GetSelectedBlockData();
    int GetMaxBlockData();
    bool IsDirty();
    int GetBlockData();
    void SetDirty(bool input);
    void SetColdown(int coldownInterval);
    bool IsCD();
    void UpdateMap();
    void ReleaseMap();
    void SetClearState(int input);
    void AddCampain(Campain& data);
    bool DrawInput();
    void OpenMap(int input);
    int GetHelpPage();
};
