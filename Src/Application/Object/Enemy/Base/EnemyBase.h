#pragma once
#include "Application/Object/Object.h"
#include "Application/TextureManager/TexManager.h"
class CameraBase;
class ModelWorkInfo;

class EnemyBase:public Object
{
public:
	void Init()override;

	void MatrixUpdate()override;

	void DrawLit()override;
	void DrawSprite()override;

	const ColliType GetRayInfo(shared_ptr<KdCollider::RayInfo> a_spRayInfo)override;
	void SetPos(const Math::Vector3& pos)override;
	const bool GetSphereInfo(shared_ptr<KdCollider::SphereInfo> a_spSphereInfo)override;

protected:
	EnemyBase() :
		m_tex(nullptr),
		m_moveVal(Math::Vector3 { 0.1f, 0.1f, 0.1f }),
		m_dir(Math::Vector3::Zero),
		m_deg(0),
		m_gravity(0),
		m_state(NEUTRAL),
		Object()
	{
		m_brightFlg = false;
		m_mWorld.CreateTranslation(0, 30.0f, 10);
	}
	
	shared_ptr<ModelWorkInfo> m_tex;

	std::weak_ptr<CameraBase> m_camera;

	//ˆÚ“®—Ê
	Math::Vector3 m_moveVal;

	Math::Vector3 m_dir;

	//ƒ}ƒEƒX‚Ì•ûŒü
	float m_deg;

	float m_gravity;

	StateType m_state;
};