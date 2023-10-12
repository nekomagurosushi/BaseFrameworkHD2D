#pragma once
#include "Application/UI/Base/UIBase.h"
#include "Application/TextureManager/TexManager.h"

class StartButton :public UIBase
{
public:
	StartButton(shared_ptr<TexManager> sp_texManager) :
		m_tex(sp_texManager->LoadPlaneTexInfo("StartButton")),
		m_fadeCount(0.0f),
		m_maxCount(180.0f),
		UIBase()
	{}
	void Init() override;
	void Update() override;
	void DrawSprite()override;
private:
	shared_ptr<PlaneTexInfo> m_tex;

	float m_fadeCount;
	float m_maxCount;
};