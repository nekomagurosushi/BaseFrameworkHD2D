#include "StartButton.h"

void StartButton::Init()
{
	m_size = m_tex->GetSize();
	m_pos = m_tex->GetPos();
}

void StartButton::Update()
{
	m_fadeCount++;
	if (m_fadeCount >= m_maxCount)
	{
		m_fadeCount = 0.0f;
	}
}

void StartButton::DrawSprite()
{
	if (!m_tex)return;
	Math::Rectangle srcRect = { 0,0,m_tex->GetRectX(),m_tex->GetRectY() };
	Math::Color color = { m_tex->GetColor().R(),m_tex->GetColor().G() ,m_tex->GetColor().B(),m_tex->GetColor().A() * (sin(DirectX::XMConvertToRadians(m_fadeCount))) };
	KdShaderManager::Instance().m_spriteShader.DrawTex(
		*m_tex->GetTex(),
		m_tex->GetPos().x,
		m_tex->GetPos().y,
		m_tex->GetRectX() * m_size.x,
		m_tex->GetRectY() * m_size.y,
		&srcRect,
		&color);
}
