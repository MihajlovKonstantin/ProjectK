#pragma once
class Block
{
protected:
	std::pair<float, float> m_localPos;
	std::pair<float, float>m_globalPos;
	std::pair<float, float> m_speed;
	std::pair<float, float> m_size;
	std::array<std::pair<float, float>, 2> m_moveBorder;
	std::array<std::pair<float, float>, 4> m_centerEdge;
	KdTexture* m_texture;
	Math::Matrix m_mTrans;
	Math::Rectangle m_rectangle;
	float m_radiusABS;
	float m_radius;
	float m_tangen;
	bool m_backStage;
	float m_angle;
public:
	void SetLocalPos(float xPos, float yPos);
	void FoundCE();
	void SetSize(float width, float height);
	void SetTexture(KdTexture* Texture);
	void SetSpeed(std::pair<float, float> speed);
	void SetMoveBorder(std::array<std::pair<float, float>, 2> moveBorder);
	void SetMoveBorder(std::array<float, 2> moveBorderDelta);
	KdTexture* GetTexture();
	float GetXPos();
	float GetYPos();
	std::pair<float, float> GetSize();
	std::pair<float, float> GetGPos();
	Math::Matrix GetMatrix();
	Math::Rectangle GetRectangle();
	void SetBackStage(bool backStage);
	bool GetBackStage();
	void SetGlobalPos();
	void SetTangen(float angle);
	float GetTan();
	float GetAngle();
	void Update();
	Block(float x, float y, float width, float height, KdTexture* texture, bool backStage, float tangen = 0);
};

