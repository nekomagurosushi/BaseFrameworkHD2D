#include "EnemyBase.h"
#include "Application/TextureManager/TexInfo/Child/ModelWorkInfo.h"

void EnemyBase::Init()
{
	*m_transMat = Math::Matrix::CreateTranslation(0, 10.0f, 0.0f);
	MatrixUpdate();
}

void EnemyBase::MatrixUpdate()
{
	m_mWorld = m_scaleMat * m_roteMat * (*m_transMat);
}

void EnemyBase::DrawLit()
{
	static bool init = true;
	if (m_tex == nullptr)return;
	static KdAnimator animator;
	if (init)
	{
		animator.SetAnimation(m_tex->GetTex()->GetAnimation("Idle"));
	}
	init = false;

	animator.AdvanceTime(m_tex->GetTex()->WorkNodes());
	m_tex->GetTex()->CalcNodeMatrices();
	KdShaderManager::Instance().m_modelShader.DrawModel(*m_tex->GetTex(), m_mWorld);
}

void EnemyBase::DrawSprite()
{
}

const ColliType EnemyBase::GetRayInfo(shared_ptr<KdCollider::RayInfo> a_spRayInfo)
{
	//レイの発射位置設定
	a_spRayInfo->m_pos = GetPos();
	//段差の許容範囲 少し上から飛ばす
	a_spRayInfo->m_pos.y += 0.2f;
	//レイの発射方向
	a_spRayInfo->m_dir = Math::Vector3::Down;
	//レイの長さ
	static float enableStepHight = 0.3f;
	a_spRayInfo->m_range = m_gravity + enableStepHight;
	//当たり判定のタイプ
	a_spRayInfo->m_type = KdCollider::TypeGround;

	return SPECIALCOLLI;
}

void EnemyBase::SetPos(const Math::Vector3& pos)
{
	m_mWorld.Translation(pos);
	if (m_gravity >= 0)
	{
		m_gravity = 0;

		if (!(m_state != FALL))
		{
			m_state = NEUTRAL;
		}
	}
}

const bool EnemyBase::GetSphereInfo(shared_ptr<KdCollider::SphereInfo> a_spSphereInfo)
{
	a_spSphereInfo->m_sphere.Center = GetPos() + Math::Vector3(0, 0.5f, 0);
	a_spSphereInfo->m_sphere.Radius = 0.2f;
	a_spSphereInfo->m_type = KdCollider::TypeBump;

	return true;
}
