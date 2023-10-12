#include "TpsCamera.h"

void TpsCamera::Init()
{
	//注視点からの位置
	m_LocalPos = Math::Matrix::CreateTranslation(0, 2.0f, -5.0f);

	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;
	// どれだけ傾けているか
	m_Rotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));
	SetCursorPos(m_FixMousePos.x,m_FixMousePos.y);
	CameraBase::Init();
}

void TpsCamera::Update()
{

	// ターゲットの行列(有効な場合利用する)
	Math::Matrix targetMat = Math::Matrix::Identity;
	if (!m_wpTarget.expired())
	{
		std::shared_ptr<const KdGameObject> spTarget = m_wpTarget.lock();
		if (spTarget)
		{
			targetMat = Math::Matrix::CreateTranslation(spTarget->GetPos());
		}
	}
	UpdateRotateByMouse();
	m_Rotation = GetRotationMatrix();

	m_mWorld = m_LocalPos * m_Rotation *targetMat;

	CameraBase::Update();
}

void TpsCamera::UpdateRotateByMouse()
{
	POINT nowPos;
	GetCursorPos(&nowPos);
	POINT mouseMove;
	mouseMove.x = nowPos.x - m_FixMousePos.x;
	mouseMove.y = nowPos.y - m_FixMousePos.y;
//	SetCursorPos(m_FixMousePos.x,m_FixMousePos.y);
	m_DegAng.x += mouseMove.y * 0.15f;
	m_DegAng.y += mouseMove.x * 0.15f;

	m_DegAng.x = std::clamp(m_DegAng.x, -0.8f, 8.0f);
	//m_DegAng.y = std::clamp(m_DegAng.y, -0.8f, 8.0f); 
}
