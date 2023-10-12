#pragma once
#include "Application/UI/Base/UIBase.h"
#include "Application/TextureManager/TexManager.h"

class NumberList :public UIBase
{
public:
	NumberList(shared_ptr<TexManager> sp_texManager, const int a_lg) :
		m_tex(sp_texManager->LoadPlaneTexInfo("NumberLabel")),
		m_stRect(0),
		m_lg(a_lg),
		UIBase()
	{}
	void Init() override;
	void Update() override;
	void DrawSprite()override;

	void SetStRect(int a_stRect);
private:
	shared_ptr<PlaneTexInfo> m_tex;

	int m_stRect;
	int m_lg;
};