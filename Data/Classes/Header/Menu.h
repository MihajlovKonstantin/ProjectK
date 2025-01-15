#pragma once
#include"Pch.h"
#include <optional>
using namespace std;
enum SceneSelect { title = 1, game = 2, option = 3, volume = 21 };
enum OptionSelect { goScene = 1, volumeUp = 2, volumeDown = 3 };
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
public:
    KdTexture* GetTexture();
    void SetTexture(KdTexture* texture);
    Math::Matrix GetMatrix();
    Math::Rectangle GetRect();
    void Update();
    Menu();
    void InitMainMenu();
    void InitSetting();
    void InitInGameSetting();
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
};

