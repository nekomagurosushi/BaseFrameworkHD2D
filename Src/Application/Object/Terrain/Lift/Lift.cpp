#include "Lift.h"

void Lift::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Data/Sample/Terrain/Lift/Lift.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("LiftModel", m_spModel,
			KdCollider::TypeGround);
	}

	m_startPos = { -12.0f, 2.0f, 1.0f };
	m_endPos = { -12.0f, 2.0f, 9.0f };

	// 2秒間で目標地点へ移動する「進捗」スピード
	m_speed = 1.0f / (60.0f * 2);
}

void Lift::Update()
{
	// ①進捗度の制御
	m_progress += m_speed * (m_isReverse * -2 + 1);
	if (m_progress >= 1.2f)
	{
		m_isReverse = true;
	}
	else if (m_progress < -0.2f)
	{
		m_isReverse = false;
	}

	float progress = std::clamp(m_progress, 0.0f, 1.0f);
	Math::Vector3 towardEndVec = m_endPos - m_startPos;
	// ②進捗度を用いて座標を決定する
	m_mWorld.Translation
	(m_startPos + towardEndVec * EaseInOutSine(progress));
}

void Lift::DrawLit()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_spModel, m_mWorld);
}