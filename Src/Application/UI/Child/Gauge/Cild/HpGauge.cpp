#include "HpGauge.h"

void HpGauge::Init()
{
	m_size = m_tex->GetSize();
	m_pos = m_tex->GetPos();
}

void HpGauge::Update()
{
	
}

void HpGauge::DrawSprite()
{
	float late = float(*m_value) / float(*m_maxValue);
	if (!m_coverTex)return;
	Math::Rectangle coverSrcRect = { 0,0,m_coverTex->GetRectX(),m_coverTex->GetRectY() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(
		*m_coverTex->GetTex(),
		m_coverTex->GetPos().x,
		m_coverTex->GetPos().y*m_size.y,
		&coverSrcRect);
	if (!m_tex)return;
	Math::Rectangle srcRect = { 0,0,m_tex->GetRectX(),m_tex->GetRectY() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(
		*m_tex->GetTex(),
		(m_tex->GetPos().x-(m_coverTex->GetRectX()- m_coverTex->GetRectX()*late)/2.0f),
		m_tex->GetPos().y*m_size.y,
		m_tex->GetRectX()*late,
		m_tex->GetRectY(),
		&srcRect);
}