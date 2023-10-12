#include "NumberList.h"

void NumberList::Init()
{
	m_size = m_tex->GetSize();
	m_pos = m_tex->GetPos();
	m_stRect = 0;
}

void NumberList::Update()
{
	
}

void NumberList::DrawSprite()
{
	if (!m_tex)return;
	Math::Rectangle srcRect = { m_stRect* m_tex->GetRectX(),0,m_tex->GetRectX(),m_tex->GetRectY() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(
		*m_tex->GetTex(),
		m_tex->GetPos().x-m_tex->GetRectX()*m_lg,
		m_tex->GetPos().y,
		m_tex->GetRectX() * m_size.x,
		m_tex->GetRectY() * m_size.y,
		&srcRect);
}

void NumberList::SetStRect(int a_stRect)
{
	m_stRect = a_stRect;
}
