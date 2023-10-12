#pragma once

#include "Application/TextureManager/TexInfo/Child/ModelWorkInfo.h"
#include "Application/Object/Object.h"
#include "Application/TextureManager/TexManager.h"
class StageBase:public Object
{
public:
	StageBase(shared_ptr<TexManager> sp_texManager):
	m_tex(sp_texManager->LoadModelWorkInfo("firstStage")),
	m_skyDome(sp_texManager->LoadModelWorkInfo("firstStageSkyDome"))
	{
		m_brightFlg = false;
	}
	~StageBase(){};
	void Init()override;

	void MatrixUpdate()override;

	void DrawLit()override;
	void DrawUnLit()override;
private:
	shared_ptr<ModelWorkInfo> m_tex;
	shared_ptr<ModelWorkInfo> m_skyDome;

};