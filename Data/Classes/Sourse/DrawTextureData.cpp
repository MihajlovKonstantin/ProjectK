#include "Data/Classes/Header/DrawTextureData.h"
void DrawTextureData::SetTexture(std::string input) 
{
    m_textureName = input;
};
std::string DrawTextureData::GetTexture() {
    return m_textureName;
}
void DrawTextureData::SetTranslation(std::array<float, 3> input)
{
    for (int i = 0; i < 3; i++)
    {
        m_textureMatix[0][i] = input[i];
    }
};
std::array<float, 3> DrawTextureData::GetTranslation()
{
    return std::array<float, 3>();
}
void DrawTextureData::SetScale(std::array<float, 3> input)
{
    for (int i = 0; i < 3; i++)
    {
        m_textureMatix[1][i] = input[i];
    }
}
std::array<float, 3> DrawTextureData::GetScale()
{
    return std::array<float, 3>();
}
void DrawTextureData::SerRotation(std::array<float, 3> input)
{
    for (int i = 0; i < 3; i++)
    {
        m_textureMatix[2][i] = input[i];
    }
}
std::array<float, 3> DrawTextureData::GetRotation()
{
    return std::array<float, 3>();
}
void DrawTextureData::SetRectangle(std::array<float, 4> input)
{
    for (int i = 0; i < 4; i++)
    {
        m_textureRectangle[i] = input[i];
    }
}
std::array<float, 4> DrawTextureData::GetRectangle()
{
    return m_textureRectangle;
}
void DrawTextureData::SetColor(std::array<float, 4> input)
{
    for (int i = 0; i < 4; i++)
    {
        m_textureColor[i] = input[i];
    }
}
std::array<float, 4> DrawTextureData::GetColor()
{
    return m_textureColor;
}
;