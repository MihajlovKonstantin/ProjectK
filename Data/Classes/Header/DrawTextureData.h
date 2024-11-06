#pragma once
#include "Pch.h"

class DrawTextureData
{
    std::string m_textureName;
    std::array<std::array<float, 3>, 3> m_textureMatix;//Translation, Scale, Rotation
    std::array<float, 4> m_textureRectangle;
    std::array<float, 4> m_textureColor;
public:
    void SetTexture(std::string input);
    std::string GetTexture();
    void SetTranslation(std::array<float, 3> input);
    std::array<float, 3> GetTranslation();
    void SetScale(std::array<float, 3> input);
    std::array<float, 3> GetScale();
    void SerRotation(std::array<float, 3> input);
    std::array<float, 3> GetRotation();
    void SetRectangle(std::array<float, 4> input);
    std::array<float, 4> GetRectangle();
    void SetColor(std::array<float, 4> input);
    std::array<float, 4> GetColor();
};