#pragma once
#include "Application/UI/Base/UIBase.h"
#include "Application/TextureManager/TexManager.h"
class Gauge :public UIBase
{
public:
	Gauge():
	UIBase()
	{}
	virtual void Update() override;
	
protected:
};