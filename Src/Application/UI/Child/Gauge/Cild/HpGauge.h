#pragma once
#include "Application/UI/Child/Gauge/Base/Gauge.h"
class HpGauge :public Gauge
{
public:
	HpGauge(shared_ptr<TexManager> sp_texManager, shared_ptr<int> sp_value, shared_ptr<int> sp_maxValue) :
		m_tex(sp_texManager->LoadPlaneTexInfo("HpGauge")),
		m_coverTex(sp_texManager->LoadPlaneTexInfo("HpGaugeCover")),
		m_value(sp_value),
		m_maxValue(sp_maxValue),
		Gauge()
	{}
	void Init() override;
	void Update() override;
	void DrawSprite()override;
private:
	shared_ptr<PlaneTexInfo> m_tex;
	shared_ptr<PlaneTexInfo> m_coverTex;

	shared_ptr<int> m_value;
	shared_ptr<int> m_maxValue;
};