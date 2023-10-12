#include "Terrain.h"

void Terrain::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Data/Sample/Terrain/StageMap.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape
		("StageModel", m_spModel, KdCollider::TypeGround|KdCollider::TypeBump);
		//m_pCollider->RegisterCollisionShape
		//("StageModel", m_spModel, KdCollider::TypeBump);
		/*m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Data/Sample/Terrain/Terrain.gltf");*/
	}
}

void Terrain::Update()
{
}

void Terrain::DrawLit()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_spModel);
}

