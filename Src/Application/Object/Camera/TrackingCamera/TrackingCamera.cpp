#include "TrackingCamera.h"

void TrackingCamera::Init()
{
	// 基準点(ターゲット)からどれだけ離れているか
	m_transMat = Math::Matrix::CreateTranslation(0.0f, 2.0f, -5.0f);

	m_fixMousePos.x = 640;
	m_fixMousePos.y = 360;

	// どれだけ傾けているか
	m_rotateMatX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(10));

	m_mWorld = (m_transMat * m_rotateMatX * m_rotateMatY);

	SetCursorPos(m_fixMousePos.x, m_fixMousePos.y);
	//CameraBase::Init();
}

//void TrackingCamera::Update()
//{
//	//// ターゲットの行列(有効な場合利用する)
//	//Math::Matrix targetMat = Math::Matrix::Identity;
//	//if (!m_wpTarget.expired())
//	//{
//	//	std::shared_ptr<const KdGameObject> spTarget = m_wpTarget.lock();
//	//	if (spTarget)
//	//	{
//	//		targetMat = spTarget->GetMatrix();
//	//	}
//	//}
//
//	//m_mWorld = m_Rotation * m_LocalPos * targetMat;
//
//	//CameraBase::Update();
//
//	//shared_ptr<const KdGameObject> sp_target = wp_target.lock();
//	//Math::Matrix targetTransMat = Math::Matrix::CreateTranslation(sp_target->GetPos());
//	//m_mixMat = (m_rotateMatX * m_transMat) * targetTransMat;
//	//m_camera->SetCameraMatrix(m_mixMat);
//	//m_camera->SetProjectionMatrix(m_pov);
//	////m_camera->SetFocus(7.0f,3.0f,4.0f);
//	///*KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false,true);
//	//KdShaderManager::Instance().WorkAmbientController().SetDistanceFog
//	//(
//	//	{ 0.5,0,0 },
//	//	0.1f
//	//);*/
//	///*KdShaderManager::Instance().WorkAmbientController().SetheightFog
//	//(
//	//	{ 1,1,1 },
//	//	1,
//	//	-5,
//	//	0.1f
//	//);*/
//	//m_camera->SetToShader();
//}

void TrackingCamera::MatrixUpdate()
{
	if (!wp_target.expired())
	{
		shared_ptr<const KdGameObject> sp_target = wp_target.lock();
		Math::Matrix targetTransMat = Math::Matrix::CreateTranslation(sp_target->GetPos());
		
		UpdateRotateByMouse();

		Math::Matrix mInvertCameraObject;
		m_mWorld.Invert(mInvertCameraObject);//Invert... 逆行列化

		Math::Matrix localCameraMath=targetTransMat* mInvertCameraObject;

		if (abs(localCameraMath.Translation().x)>=2.5f)
		{
			
			float fixPosX = -localCameraMath.Translation().x;
			fixPosX = std::clamp(fixPosX, -2.5f, 2.5f);
			m_transMat = Math::Matrix::CreateTranslation(fixPosX, 2.0f, -5.0f);


			m_mWorld = (m_transMat * m_rotateMatX * m_rotateMatY) * targetTransMat;
		}
		else
		{
			Math::Matrix TrMath = Math::Matrix::CreateTranslation(-localCameraMath.Translation().x, m_transMat.Translation().y, m_transMat.Translation().z);
			
			m_mWorld = TrMath *m_rotateMatX * m_rotateMatY * targetTransMat;
		}
		
	}
	m_spCamera->SetCameraMatrix(m_mWorld);
	m_spCamera->SetProjectionMatrix(m_pov);
	//m_camera->SetFocus(7.0f,3.0f,4.0f);
	/*KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false,true);
	KdShaderManager::Instance().WorkAmbientController().SetDistanceFog
	(
		{ 0.5,0,0 },
		0.1f
	);*/
	/*KdShaderManager::Instance().WorkAmbientController().SetheightFog
	(
		{ 1,1,1 },
		1,
		-5,
		0.1f
	);*/

	m_spCamera->SetToShader();
}

const Math::Vector3 TrackingCamera::GetPos()
{
	shared_ptr<const KdGameObject> sp_target = wp_target.lock();
	Math::Matrix targetTransMat = Math::Matrix::CreateTranslation(sp_target->GetPos());
	
	UpdateRotateByMouse();
	Math::Matrix mInvertCameraObject;
	m_mWorld.Invert(mInvertCameraObject);//Invert... 逆行列化

	Math::Matrix localCameraMath = targetTransMat * mInvertCameraObject;

	if (abs(localCameraMath.Translation().x) >= 2.5f)
	{

		float fixPosX = -localCameraMath.Translation().x;
		fixPosX = std::clamp(fixPosX, -2.5f, 2.5f);
		m_transMat = Math::Matrix::CreateTranslation(fixPosX, 2.0f, -5.0f);


		m_mWorld = (m_transMat * m_rotateMatX * m_rotateMatY) * targetTransMat;
	}
	else
	{
		Math::Matrix TrMath = Math::Matrix::CreateTranslation(-localCameraMath.Translation().x, m_transMat.Translation().y, m_transMat.Translation().z);

		m_mWorld = TrMath * m_rotateMatX * m_rotateMatY * targetTransMat;
	}

	return m_transMat.Translation() + targetTransMat.Translation();

}

void TrackingCamera::UpdateRotateByMouse()
{
	POINT nowPos;
	GetCursorPos(&nowPos);
	POINT mouseMove;
	mouseMove.x = nowPos.x - m_fixMousePos.x;
	mouseMove.y = nowPos.y - m_fixMousePos.y;
	SetCursorPos(m_fixMousePos.x, m_fixMousePos.y);

	m_rotateMatX*= Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(mouseMove.y * 0.15f));
	m_rotateMatY *= Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(mouseMove.x*0.15f));

	//=std::clamp();

}
