#include "BoostGauge.h"

void BoostGauge::Init()
{
	m_size = m_tex->GetSize();
	m_pos = m_tex->GetPos();
}

void BoostGauge::Update()
{
}

void BoostGauge::DrawSprite()
{
	if (!m_coverTex)return;
	Math::Rectangle coverSrcRect = { 0,0,m_coverTex->GetRectX(),m_coverTex->GetRectY() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(
		*m_coverTex->GetTex(),
		m_coverTex->GetPos().x,
		m_coverTex->GetPos().y,
		&coverSrcRect);
	if (!m_tex)return;
	Math::Rectangle srcRect = { 0,0,m_tex->GetRectX(),m_tex->GetRectY() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(
		*m_tex->GetTex(),
		m_tex->GetPos().x,
		m_tex->GetPos().y,
		&srcRect);
}
