#include "Reticle.h"

void Reticle::Init()
{
	m_size = m_tex->GetSize();
	m_pos = m_tex->GetPos();
}

void Reticle::Update()
{

}

void Reticle::DrawSprite()
{
	if (!m_tex)return;
	Math::Rectangle srcRect = { 0,0,m_tex->GetRectX(),m_tex->GetRectY() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(
		*m_tex->GetTex(),
		m_tex->GetPos().x,
		m_tex->GetPos().y,
		m_tex->GetRectX()*m_size.x,
		m_tex->GetRectY()*m_size.y,
		&srcRect);
}