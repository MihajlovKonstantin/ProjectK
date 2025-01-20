#pragma once
#include "Pch.h"
#include <optional>
using namespace std;
enum SceneSelect { Title = 1, Game = 2, Option ,Records,SelectPlaybleMap,SelectEditMap};
enum DataValue { volume = 21 };
enum OptionSelect { goScene = 1, increaseByIndex = 2, decreaseByIndex = 3 ,setEndFlg=4,switchBool=5,selectMap=6,openMap=7,newMap=8,updateMap=9, releaseMap};
enum ChangeSelect { change = 1, nochange = 3 };
class Menu
{
private:
    std::vector<Button> buttons;
    Button testButton;
    WindowsControlData* data;
    bool visable;
    bool active;
    KdTexture* m_texture;
    Math::Rectangle m_rect = { 0,0,3840,780 };
    Math::Matrix m_matrix;
    std::pair<float, float> m_pos = {0.0f,0.0f};
    std::string selectedMap;
    std::string selectedPath;
    std::string  m_dataPath;
    std::string newPath;
    int selectedBlockData = 0; //31 index
    int maxBlockData = 1;
    int mapNum;
    bool IsSelectMapMenu = false;
    bool dirty = true;
    int currentColdown = 0;
    int coldownInterval = 300;
public:
    KdTexture* GetTexture();
    void SetTexture(KdTexture* texture);
    Math::Matrix GetMatrix();
    Math::Rectangle GetRect();
    void Update();
    Menu();
    void InitMainMenu(std::string dataPath);
    void InitSetting();
    void InitInGameSetting();
    void InitSelectMapPlayeble(std::vector<std::string > mapList,std::string path,std::string dataPath);
    void InitSelectEditingMap(std::vector<std::string > mapList, std::string path, std::string dataPath);
    Button GetButton();
    Button GetButton(int cnt);
    int GetButtonsCNT();
    void AddData(WindowsControlData& inputData)
    {
        data =& inputData;
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
    void SetColdown();
    bool IsCD();
    void UpdateMap();
    void ReleaseMap();
};

