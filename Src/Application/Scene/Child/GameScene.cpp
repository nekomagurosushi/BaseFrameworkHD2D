#include "GameScene.h"
#include "Application/Scene/Child/ResultScene.h"

#include "Application/Object/Player/Player.h"
#include "Application/Object/Enemy/Base/EnemyBase.h"
#include "Application/Object/Weapon/Bullet/normalBullet.h"
#include "Application/Object/Stage/StageBase.h"

#include "Application/Object/Camera/TrackingCamera/TrackingCamera.h"

#include "Application/TextureManager/TexInfo/Child/2DTexInfo.h"
void GameScene::Init()
{
	m_texManager->JsonLoad("Json/Player.json");
	m_texManager->JsonLoad("Json/Stage.json");
	m_texManager->JsonLoad("Json/Enemy.json");
	//オブジェクト生成
	shared_ptr<Player> l_player = make_shared<Player>(m_texManager);

	shared_ptr<StageBase> l_stage = make_shared<StageBase>(m_texManager);

	//shared_ptr<EnemyBase> l_enemy = make_shared<EnemyBase>(m_texManager);

	l_stage->Init();
	m_objectList->push_back(l_stage);


	//カメラを生成＆セット
	m_camera = make_shared<TrackingCamera>(l_player);
	l_player->SetCamera(m_camera);
	l_player->SetBulletList(sp_bulletList);
	l_player->Init();
	m_objectList->push_back(l_player);

	ShowCursor(false);
	//KdShaderManager::Instance().WorkAmbientController().AddPointLight(Math::Vector3 {1,1,1},10,Math::Vector3 {1,3,-2},true);
	//KdShaderManager::Instance().WorkAmbientController().SetDirLight(Math::Vector3 {1, 1, 1}, Math::Vector3 {1, 1, 1});
	//KdShaderManager::Instance().WorkAmbientController().SetFo(Math::Vector3 {1, 1, 1}, Math::Vector3 {1, 1, 1});
}

Scene* GameScene::Update()
{
	m_frame++;
	if (m_fadeTime > 0)
	{
		m_fadeTime--;
		if (m_fadeTime <= 0)return new ResultScene;
	}
	else
	{
		switch(m_sceneState)
		{
		case NORMAL:
			for (shared_ptr<Object> sp_object : *m_objectList)
			{
				if (sp_object == nullptr)continue;
				sp_object->Update();
			}
			for (shared_ptr<NormalBullet> sp_bullet : *sp_bulletList)
			{
				if (sp_bullet == nullptr)continue;
				sp_bullet->Update();
			}
			break;
		case STOP:
			break;
		}
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000 && m_fadeTime <= 0)
	{
		m_fadeTime = 60;
		m_fadeTex = m_texManager->LoadPlaneTexInfo("Fade");
	}

	if (GetAsyncKeyState(VK_TAB) & 0x8000)
	{
		if (!m_tabKeyFlg)
		{
			if (m_sceneState != STOP)
			{
				m_sceneState = STOP;
			}
			else if (m_sceneState == STOP)
			{
				m_sceneState = NORMAL;
			}
			m_tabKeyFlg = true;
		}
	}
	else
	{
		m_tabKeyFlg = false;
	}
	return this;//make_shared<GameScene>();
}

void GameScene::MatrixUpdate()
{
	if (m_sceneState == STOP)return;
	for (shared_ptr<Object> sp_object : *m_objectList)
	{
		if (sp_object == nullptr)continue;
		sp_object->MatrixUpdate();
		m_camera->MatrixUpdate();
		/*当たり判定*/
		CollisionUpdate(sp_object);
	}
	for (shared_ptr<NormalBullet> sp_bullet : *sp_bulletList)
	{
		if (sp_bullet == nullptr)continue;
		sp_bullet->MatrixUpdate();
	}
	return;
}

void GameScene::DrawLit() const
{
	Scene::DrawLit();
	for (shared_ptr<NormalBullet> sp_bullet : *sp_bulletList)
	{
		if (sp_bullet == nullptr)continue;
		sp_bullet->DrawLit();
	}
}

void GameScene::DrawUnLit() const
{
	Scene::DrawUnLit();
}

void GameScene::DrawBright() const
{
	Scene::DrawBright();
}

void GameScene::DrawSprite() const
{
	Scene::DrawSprite();
	//if (m_titleTex)
	//{
	//	/*Math::Rectangle coverRect = { 0,0,m_titleTex->GetRectX(),m_titleTex->GetRectY(), };
	//	Math::Color coverColor = { 1, 1, 1, 1 };*/
	//	/*KdShaderManager::Instance().m_spriteShader.DrawTex(
	//		m_titleTex->GetTex(),
	//		0,
	//		cos(DirectX::XMConvertToRadians(m_frame))*30,
	//		m_titleTex->GetRectX(),
	//		m_titleTex->GetRectY(),
	//		&coverRect,
	//		&coverColor,
	//		Math::Vector2{0.5, 0.5f}
	//	);*/
	//}
	if (m_fadeTime > 0)
	{
		//if (m_fadeTex == nullptr)return;
		Math::Color a = { 0,0,0,1 - m_fadeTime / 60.0f };
		KdShaderManager::Instance().m_spriteShader.DrawBox(0, 0, 640, 360, &a, true);

	}
	else if(m_sceneState == STOP)
	{
		Math::Color a = { 0,0,0,0.5};
		KdShaderManager::Instance().m_spriteShader.DrawBox(0, 0, 640, 360, &a, true);
	}
}

void GameScene::CollisionUpdate(shared_ptr<Object> a_spObject)
{
	//地面判定
	shared_ptr<KdCollider::RayInfo> rayInfo=make_shared<KdCollider::RayInfo>();

	KdCollider::RayInfo toCamRayInfo;
	static float enableStepHight;
	//レイの発射方向
	Math::Vector3 rayDir;
	switch (a_spObject->GetRayInfo(rayInfo))
	{
	case SPECIALCOLLI:
		
		//レイの発射位置設定
		toCamRayInfo.m_pos = a_spObject->GetPos();
		//段差の許容範囲 少し上から飛ばす
		toCamRayInfo.m_pos.y += 1.0f;
		//レイの発射方向
		rayDir = m_camera->GetPos()- toCamRayInfo.m_pos;
		
		//レイの長さ
		enableStepHight = rayDir.Length();
		toCamRayInfo.m_range = enableStepHight;

		rayDir.Normalize();
		toCamRayInfo.m_dir = rayDir;
		
		
		
		//当たり判定のタイプ
		toCamRayInfo.m_type = KdCollider::TypeGround;
		//m_wpRideObject.reset();//リセット
		for (shared_ptr<Object>spGameObj : *m_objectList)
		{
			if (spGameObj != nullptr && (a_spObject != spGameObj))
			{
				std::list<KdCollider::CollisionResult> retRayList;
				spGameObj->Intersects(toCamRayInfo, &retRayList);//ここでぶつかっている

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
						hitPos = ret.m_hitPos ;
						hit = true;
					}
				}
				if (hit)
				{

					m_camera->SetPos( hitPos - a_spObject->GetPos());
					//m_camera->SetRote(atan2(hitPos.y,hitPos.x));
					////リフト
					////乗物から見たプレイヤーのローカル行列
					//if (spGameObj->IsRideable())
					//{
					//	Math::Matrix mInvertRideObject;
					//	spGameObj->GetMatrix().Invert(mInvertRideObject);//Invert... 逆行列化

					//	m_mLocalFrromRideObject = a_spObject->GetMatrix() * mInvertRideObject;
					//	m_wpRideObject = spGameObj;

					//}
				}
			}
		}
	case COLLI:
		//m_wpRideObject.reset();//リセット
		for (shared_ptr<Object>spGameObj : *m_objectList)
		{
			if (spGameObj != nullptr && (a_spObject != spGameObj))
			{
				std::list<KdCollider::CollisionResult> retRayList;
				spGameObj->Intersects(*rayInfo, &retRayList);//ここでぶつかっている

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
					a_spObject->SetPos(hitPos);

					////リフト
					////乗物から見たプレイヤーのローカル行列
					//if (spGameObj->IsRideable())
					//{
					//	Math::Matrix mInvertRideObject;
					//	spGameObj->GetMatrix().Invert(mInvertRideObject);//Invert... 逆行列化

					//	m_mLocalFrromRideObject = a_spObject->GetMatrix() * mInvertRideObject;
					//	m_wpRideObject = spGameObj;

					//}
				}
			}
		}
		break;
	default:
		break;
	}
	
	
	//②HIT対象オブジェクトに当たり
	shared_ptr<KdCollider::SphereInfo> sphereInfo = make_shared<KdCollider::SphereInfo>();

	if (!a_spObject->GetSphereInfo(sphereInfo))return;
	for (shared_ptr<Object> spGameObject : *m_objectList)
	{
		if (spGameObject != nullptr && (a_spObject != spGameObject))
		{
			std::list<KdCollider::CollisionResult> retBumpList;
			spGameObject->Intersects(*sphereInfo, &retBumpList);

			for (auto& ret : retBumpList)
			{
				Math::Vector3 nowPos = a_spObject->GetPos() + (ret.m_hitDir * ret.m_overlapDistance);
				a_spObject->SetPos(Math::Vector3 {nowPos.x, nowPos.y, 0});
			}
		}
	}
}

//void GameScene::CollisionUpdate(shared_ptr<AttackHitBox> a_spCollider)
//{
//	//for (shared_ptr<Object> spGameObject : *m_objectList)
//	//{
//	//	if (spGameObject != nullptr)
//	//	{
//	//		std::list<KdCollider::CollisionResult> retBumpList;
//	//		spGameObject->Intersects(*a_spCollider, &retBumpList);
//
//	//		for (auto& ret : retBumpList)
//	//		{
//	//			Math::Vector3 nowPos = spGameObject->GetPos() - (ret.m_hitDir * ret.m_overlapDistance);
//	//			spGameObject->SetPos(Math::Vector3 {nowPos.x, nowPos.y, 0});
//	//			
//	//			if (spGameObject->GetStopTime()<=0)
//	//			{
//	//				a_spCollider->Hit();
//	//				spGameObject->Hit(a_spCollider->GetVec());
//	//				spGameObject->SetStopTime(a_spCollider->GetStopTime());
//	//				KdEffekseerManager::GetInstance().Play(
//	//					"slashHit.efk",
//	//					Math::Vector3 {nowPos.x, nowPos.y, 0} + Math::Vector3{0, 0.5f, 0},
//	//					0.3,
//	//					1,
//	//					false
//	//				);
//	//			}
//	//		}
//	//			
//	//			/*a_spCollider->Hit();
//	//			spGameObject->Hit();*/
//	//	}
//	//}
//}