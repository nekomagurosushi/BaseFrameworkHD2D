#pragma once
#include "Application/Scene/Base/Scene.h"
class ResultScene :public Scene
{
public:
	ResultScene() {}
	~ResultScene(){}
	void Init() override;
	Scene* Update()override;
};