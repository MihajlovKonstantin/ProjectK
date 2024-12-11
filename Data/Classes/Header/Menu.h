#pragma once
#include"Pch.h"
#include <optional>
using namespace std;
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

