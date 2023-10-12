#pragma once
#include "Application/UI/Base/UIBase.h"
#include "Application/TextureManager/TexManager.h"
class Reticle :public UIBase
{
public:
	Reticle(shared_ptr<TexManager> sp_texManager) :
		m_tex(sp_texManager->LoadPlaneTexInfo("Reticle")),
		UIBase()
	{}
	void Init() override;
	void Update() override;
	void DrawSprite()override;
private:
	shared_ptr<PlaneTexInfo> m_tex;
};