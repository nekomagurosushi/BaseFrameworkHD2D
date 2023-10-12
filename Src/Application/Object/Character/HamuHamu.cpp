#include "HamuHamu.h"
#include "Application/GameObject/Camera/CameraBase.h"
void HamuHamu::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/Sample/Character/SampleChara.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}
	m_gravity = 0;
	SetPos({ 0, 5.0f, 0 });
}

void HamuHamu::Update()
{
	
	//���t�g
	//�敨�ɏ���Ă�����
	//���g�̍s����X�V���敨���猩�����[�J���s�񁖏敨�̃��[���h�s��
	std::shared_ptr<KdGameObject> spGameObj = m_wpRideObject.lock();
	if (spGameObj)
	{
		m_mWorld = m_mLocalFrromRideObject * spGameObj->GetMatrix();
	}
	m_gravity += 0.01f;
	m_mWorld._42 -= m_gravity;
	// �L�����N�^�[�̈ړ����x(�^��������_���ł���)
	float moveSpd			= 0.05f;
	Math::Vector3 nowPos = GetPos();
	Math::Vector3 moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { moveVec.x = 1.0f;	}
	if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { moveVec.z = 1.0f;	}
	if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) { m_gravity = -0.1f; }

	std::shared_ptr<CameraBase> spCamera = m_camera.lock();
	if (spCamera)
	{
		moveVec = moveVec.TransformNormal
		(moveVec,spCamera->GetRotationYMatrix());//�ړ��x�N�g���J������Y������ɍX�V���Ă���
	}

	moveVec.Normalize();
	moveVec *= moveSpd;
	//
	
	nowPos.x += moveVec.x;
	nowPos.z += moveVec.z;
	
	UpdateRotate(moveVec);
	// �L�����N�^�[�̃��[���h�s���n�鏈��
	Math::Matrix transMat = Math::Matrix::CreateTranslation(nowPos);
	Math::Matrix rotateMat = Math::Matrix::CreateRotationY(
		DirectX::XMConvertToRadians(m_worldRot.y));
	m_mWorld = rotateMat * transMat;


	UpdataCollision();
}

void HamuHamu::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_HD2DShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void HamuHamu::DrawSprite()
{
	if (!m_spPoly) return;
	std::shared_ptr<CameraBase> spCamera=m_camera.lock();
	Math::Vector3 resultPos = Math::Vector3::Zero;
	KdDirect3D::Instance().ConvertWorldToScreenDetail(*spCamera->WorkCamera(), GetPos(), resultPos);
	//KdShaderManager::Instance().m_HD2DShader.DrawPolygon(*m_spPoly, m_mWorld);
	if (resultPos.z > 0)
	{
		/*KdShaderManager::Instance().m_spriteShader.DrawCircle(resultPos.x, resultPos.y, 10, &kRedColor);*/
		KdShaderManager::Instance().m_spriteShader.DrawCircle(resultPos.x, resultPos.y+10, 10, &kRedColor);
	}
}

void HamuHamu::UpdateRotate(Math::Vector3& srcMoveVec)
{
	//�������͂��ĂȂ��ꍇ�͏������Ȃ�
	if (srcMoveVec.LengthSquared() == 0.0f)
	{
		return;
	}

	//�ړ������̃x�N�g��
	Math::Vector3 targetDir = srcMoveVec;

	//�L�������ʕ����̃x�N�g��
	Math::Vector3 nowDir = GetMatrix().Backward();

	targetDir.Normalize();
	nowDir.Normalize();

	float nowAng = atan2(nowDir.x, nowDir.z);
	nowAng = DirectX::XMConvertToDegrees(nowAng);
	float targetAng = atan2(targetDir.x, targetDir.z);
	targetAng = DirectX::XMConvertToDegrees(targetAng);

	float betweenAng = targetAng - nowAng;
	if (betweenAng>180)
	{
		betweenAng -= 360;
	}
	else if (betweenAng<-180)
	{
		betweenAng += 360;
	}

	float rotateAng = std::clamp(betweenAng, -8.0f, 8.0f);
	m_worldRot.y += rotateAng;
}

void HamuHamu::UpdataCollision()
{
	//�n�ʔ���

	//�@�����蔻��p�̏��쐬
	KdCollider::RayInfo rayInfo;
	//���C�̔��ˈʒu�ݒ�
	rayInfo.m_pos = GetPos();
	//�i���̋��e�͈� �����ォ���΂�
	rayInfo.m_pos.y += 0.2f;
	//���C�̔��˕���
	rayInfo.m_dir = Math::Vector3::Down;
	//���C�̒���
	static float enableStepHight = 0.3f;
	rayInfo.m_range = m_gravity + enableStepHight;
	//�����蔻��̃^�C�v
	rayInfo.m_type = KdCollider::TypeGround;

	m_wpRideObject.reset();//���Z�b�g
	for (std::weak_ptr<KdGameObject>wpGameObj : m_wpHitObjectlist)
	{
		std::shared_ptr<KdGameObject>spGameObj = wpGameObj.lock();
		if (spGameObj)
		{
			std::list<KdCollider::CollisionResult> retRayList;
			spGameObj->Intersects(rayInfo, &retRayList);//�����łԂ����Ă���

			//�B���ʂ��g���č��W��⊮����
			//���C�ɓ����������X�g�����ԋ߂��I�u�W�F�N�g�����o
			float maxOverLap = 0;
			Math::Vector3 hitPos = {};
			bool hit = false;

			for (auto& ret : retRayList)
			{
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap = ret.m_overlapDistance;
					hitPos = ret.m_hitPos;
					hit = true;
				}
			}
			if (hit)
			{
				SetPos(hitPos);
				m_gravity = 0;

				//���t�g
				//�敨���猩���v���C���[�̃��[�J���s��
				if (spGameObj->IsRideable())
				{
					Math::Matrix mInvertRideObject;
					spGameObj->GetMatrix().Invert(mInvertRideObject);//Invert... �t�s��

					m_mLocalFrromRideObject = m_mWorld * mInvertRideObject;
					m_wpRideObject = spGameObj;

				}
			}
		}
	}
	//�@�����蔻��ɂ��Փ˔���
	KdCollider::SphereInfo sphereInfo;
	sphereInfo.m_sphere.Center = GetPos()+Math::Vector3(0,0.5f,0);
	sphereInfo.m_sphere.Radius = 0.5f;
	sphereInfo.m_type = KdCollider::TypeBump;
	//�AHIT�ΏۃI�u�W�F�N�g�ɓ�����
	for (std::weak_ptr<KdGameObject>wpGameObject : m_wpHitObjectlist)
	{
		std::shared_ptr<KdGameObject> spGameObject = wpGameObject.lock();;
		if (spGameObject)
		{
			std::list<KdCollider::CollisionResult> retBumpList;
			spGameObject->Intersects(sphereInfo,&retBumpList);

			for (auto& ret:retBumpList)
			{
				Math::Vector3 nowPos = GetPos() + (ret.m_hitDir * ret.m_overlapDistance);
				SetPos(nowPos);
			}
		}
	}
}