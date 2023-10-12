#pragma once
#include "Application/TextureManager/TexInfo/Child/2DTexInfo.h"
using namespace std;
class UIBase
{
public:
	virtual void Init()=0;

	virtual void Release();

	// çXêVèàóù
	virtual void Update();

	virtual void MatrixUpdate();

	virtual void DrawSprite()=0;
protected:
	UIBase() :
		m_pos(Math::Vector2::Zero),
		m_size(Math::Vector2::Zero)
	{}

	Math::Vector2 m_pos;
	Math::Vector2 m_size;
};