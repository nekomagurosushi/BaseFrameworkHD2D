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
	
	//リフト
	//乗物に乗っていたら
	//自身の行列を更新＝乗物から見たローカル行列＊乗物のワールド行列
	std::shared_ptr<KdGameObject> spGameObj = m_wpRideObject.lock();
	if (spGameObj)
	{
		m_mWorld = m_mLocalFrromRideObject * spGameObj->GetMatrix();
	}
	m_gravity += 0.01f;
	m_mWorld._42 -= m_gravity;
	// キャラクターの移動速度(真似しちゃダメですよ)
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
		(moveVec,spCamera->GetRotationYMatrix());//移動ベクトルカメラのY軸を基準に更新している
	}

	moveVec.Normalize();
	moveVec *= moveSpd;
	//
	
	nowPos.x += moveVec.x;
	nowPos.z += moveVec.z;
	
	UpdateRotate(moveVec);
	// キャラクターのワールド行列を創る処理
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
	//何も入力してない場合は処理しない
	if (srcMoveVec.LengthSquared() == 0.0f)
	{
		return;
	}

	//移動方向のベクトル
	Math::Vector3 targetDir = srcMoveVec;

	//キャラ正面方向のベクトル
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
	//地面判定

	//①当たり判定用の情報作成
	KdCollider::RayInfo rayInfo;
	//レイの発射位置設定
	rayInfo.m_pos = GetPos();
	//段差の許容範囲 少し上から飛ばす
	rayInfo.m_pos.y += 0.2f;
	//レイの発射方向
	rayInfo.m_dir = Math::Vector3::Down;
	//レイの長さ
	static float enableStepHight = 0.3f;
	rayInfo.m_range = m_gravity + enableStepHight;
	//当たり判定のタイプ
	rayInfo.m_type = KdCollider::TypeGround;

	m_wpRideObject.reset();//リセット
	for (std::weak_ptr<KdGameObject>wpGameObj : m_wpHitObjectlist)
	{
		std::shared_ptr<KdGameObject>spGameObj = wpGameObj.lock();
		if (spGameObj)
		{
			std::list<KdCollider::CollisionResult> retRayList;
			spGameObj->Intersects(rayInfo, &retRayList);//ここでぶつかっている

			//③結果を使って座標を補完する
			//レイに当たったリストから一番近いオブジェクトを検出
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

				//リフト
				//乗物から見たプレイヤーのローカル行列
				if (spGameObj->IsRideable())
				{
					Math::Matrix mInvertRideObject;
					spGameObj->GetMatrix().Invert(mInvertRideObject);//Invert... 逆行列化

					m_mLocalFrromRideObject = m_mWorld * mInvertRideObject;
					m_wpRideObject = spGameObj;

				}
			}
		}
	}
	//①当たり判定による衝突判定
	KdCollider::SphereInfo sphereInfo;
	sphereInfo.m_sphere.Center = GetPos()+Math::Vector3(0,0.5f,0);
	sphereInfo.m_sphere.Radius = 0.5f;
	sphereInfo.m_type = KdCollider::TypeBump;
	//②HIT対象オブジェクトに当たり
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