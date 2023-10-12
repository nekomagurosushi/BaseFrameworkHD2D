#include "Application/Object/Stage/StageBase.h"

void StageBase::Init()
{

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape
	("StageModel", m_tex->GetTex(), KdCollider::TypeGround | KdCollider::TypeBump);

}

void StageBase::MatrixUpdate()
{
	m_mWorld = Math::Matrix::Identity;
}

void StageBase::DrawLit()
{
	if (m_tex == nullptr)return;

	KdShaderManager::Instance().m_modelShader.DrawModel(*m_tex->GetTex(), m_mWorld);
}

void StageBase::DrawUnLit()
{
	if(m_skyDome == nullptr)return;

	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_skyDome->GetTex(), m_mWorld);

}
