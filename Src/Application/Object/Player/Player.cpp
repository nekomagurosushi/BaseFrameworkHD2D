#include "Player.h"

#include "Application/TextureManager/TexInfo/Child/ModelWorkInfo.h"
#include "Application/Object/Camera/CameraBase.h"
#include "Application/Object/Weapon/Bullet/normalBullet.h"
void Player::Init()
{
	*m_transMat = Math::Matrix::CreateTranslation(0, 10.0f, 0.0f);
	MatrixUpdate();
	m_hpGauge->Init();
	m_boostGauge->Init();
	m_reticle->Init();
}

void Player::Update()
{
	
	/*if (m_boostVal <= 0)
	{
		if (m_state!=BOOST)
		{
			m_state = NEUTRAL;
		}
	}*/
	if (m_gravity > 0)
	{
		m_state = FALL;

	}

	

	m_gravity += 0.01f;
	m_mWorld._42 -= m_gravity;
	Math::Vector3 nowPos = GetPos();
	Math::Vector3 moveVec = Math::Vector3::Zero;

	static bool walk = true;
	static bool backwalk = true;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		moveVec.z = +0.1f;
		*m_hp -= 1;
	}
	
	if (GetAsyncKeyState('S') & 0x8000)
	{
		moveVec.z = -0.1f;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		moveVec.x = 0.1f;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		moveVec.x = -0.1f;
	}

	if (moveVec != Math::Vector3::Zero)
	{
		if (moveVec.z >= 0)
		{
			static KdAnimator animator;
			if (walk)
			{
				animator.SetAnimation(m_tex->GetTex()->GetAnimation("Walk"));
			}
			walk = false;
			backwalk = true;
			animator.AdvanceTime(m_tex->GetTex()->WorkNodes());
		}
		else if (moveVec.z <= 0)
		{
			static KdAnimator animator;
			if (backwalk)
			{
				animator.SetAnimation(m_tex->GetTex()->GetAnimation("BackWalk"));
			}
			backwalk = false;
			walk = true;
			animator.AdvanceTime(m_tex->GetTex()->WorkNodes());
		}
	}
	else
	{
		walk = true;
		backwalk = true;
	}
	
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		/*if (m_state != SHOT)
		{
			static KdAnimator animator;
			if (!(m_state!=WALK))
			{
				animator.SetAnimation(m_tex->GetTex()->GetAnimation("WalkShot"));
			}
			else if (!(m_state != NEUTRAL))
			{
				animator.SetAnimation(m_tex->GetTex()->GetAnimation("IdleShot"));
			}
			walk = false;

			animator.AdvanceTime(m_tex->GetTex()->WorkNodes());
		}*/
		shared_ptr<CameraBase> spCamera = m_camera.lock();

		shared_ptr<NormalBullet> bullet = make_shared<NormalBullet>
			(m_bulletModel,m_transMat->Translation()+Math::Vector3{0,0.5f,0.1f}, spCamera->GetRotationYMatrix());

		shared_ptr<vector<shared_ptr<NormalBullet>>>sp_objectList = wp_bulletList.lock();
		sp_objectList->push_back(bullet);
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!(m_state & (JUMP | FALL)))
		{
			m_state = JUMP;
			m_gravity = -0.2f;
		}
	}

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		if (!m_state& (BOOST|OVERBOOST))
		{
			m_state = BOOST;
			m_boostVal = 1.5f;
		}

		if (m_overBoostCnt <= 0&&m_state!=OVERBOOST)
		{
			m_overBoostCnt = 40;
		}
		else
		{
			m_overBoostCnt--;
			if (m_overBoostCnt <= 0)
			{
				m_overBoostCnt = 0;
				m_state = OVERBOOST;
				m_boostVal = 2.0f;
			}
		}
	}

	if (m_state &(BOOST|OVERBOOST))
	{
		m_boostVal *= 0.9f;
		moveVec *= m_boostVal;

		if (abs(m_boostVal) < 0.1f)
		{
			m_boostVal = 0;
			m_state = NEUTRAL;
		}
	}

	shared_ptr<CameraBase> spCamera = m_camera.lock();

	moveVec = moveVec.TransformNormal
	(moveVec, spCamera->GetRotationYMatrix());//移動ベクトルカメラのY軸を基準に更新している

	//moveVec.Normalize();
	nowPos += moveVec;
	*m_transMat = Math::Matrix::CreateTranslation(nowPos);


	int lg = *m_maxHp;
	lg=log10(lg);

	int lg_valu=*m_hp;
	for (int i = lg; i >= 0; i--)
	{
		int h_lg = pow(10, i);
		m_numberList[i]->SetStRect(lg_valu / h_lg);
		lg_valu %= h_lg;
	}
	
}

void Player::MatrixUpdate()
{
	std::shared_ptr<CameraBase> spCamera = m_camera.lock();
	Math::Matrix mixRoteMat=m_roteMat* spCamera->GetRotationYMatrix();

	m_mWorld = m_scaleMat * mixRoteMat * (*m_transMat);
}

void Player::PostUpdate()
{
	if (*m_hp <= 0)
	{
		*m_hp = 0;
	}
	if (*m_hp > *m_maxHp)
	{
		*m_hp = *m_maxHp;
	}
}

void Player::DrawLit()
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

void Player::DrawSprite()
{
	m_hpGauge->DrawSprite();
	m_boostGauge->DrawSprite();
	m_reticle->DrawSprite();
	for (shared_ptr<NumberList> sp_number : m_numberList)
	{
		sp_number->DrawSprite();
	}
}

float Player::GetDeg()
{
	return 0.0f;
}

const ColliType Player::GetRayInfo(shared_ptr<KdCollider::RayInfo> a_spRayInfo)
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

void Player::SetPos(const Math::Vector3& pos)
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

const bool Player::GetSphereInfo(shared_ptr<KdCollider::SphereInfo> a_spSphereInfo)
{
	a_spSphereInfo->m_sphere.Center = GetPos() + Math::Vector3(0, 0.5f, 0);
	a_spSphereInfo->m_sphere.Radius = 0.2f;
	a_spSphereInfo->m_type = KdCollider::TypeBump;

	return true;
}
