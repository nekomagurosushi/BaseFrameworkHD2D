#include "FpsCamera.h"

void FpsCamera::Init()
{
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;

	// 基準点(ターゲット)からどれだけ離れているか
	m_LocalPos = Math::Matrix::CreateTranslation(0.0f, 0.5f, -0.3f);

	// どれだけ傾けているか
	m_Rotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	CameraBase::Init();
}

void FpsCamera::Update()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix targetMat = Math::Matrix::Identity;
	if (!m_wpTarget.expired())
	{
		std::shared_ptr<const KdGameObject> spTarget = m_wpTarget.lock();
		if (spTarget)
		{
			targetMat = spTarget->GetMatrix();
		}
	}

	UpdateRotateByMouse();
	m_Rotation = GetRotationMatrix();
	
	Math::Matrix fixRoteMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(180));

	m_mWorld = fixRoteMat*m_LocalPos* m_Rotation * targetMat;

	CameraBase::Update();
}

void FpsCamera::UpdateRotateByMouse()
{
	POINT nowPos;
	GetCursorPos(&nowPos);
	POINT mouseMove;
	mouseMove.x = nowPos.x - m_FixMousePos.x;
	mouseMove.y = nowPos.y - m_FixMousePos.y;
	SetCursorPos(m_FixMousePos.x,m_FixMousePos.y);
	m_DegAng.x += mouseMove.y * 0.15f;
	m_DegAng.y += mouseMove.x * 0.15f;

	m_DegAng.x = std::clamp(m_DegAng.x, -0.8f, 8.0f);
	//m_DegAng.y = std::clamp(m_DegAng.y, -0.8f, 8.0f); 
}