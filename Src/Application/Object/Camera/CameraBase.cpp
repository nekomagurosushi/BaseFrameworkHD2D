#include "CameraBase.h"

void CameraBase::Init()
{
	/*if (!m_spCamera)
	{
		m_spCamera = std::make_shared<KdCamera>();
	}*/
}

//void CameraBase::Update()
//{
//	if (!m_spCamera) { return; }
//
//	m_spCamera->SetCameraMatrix(m_mWorld);
//}

//void CameraBase::PreDraw()
//{
//	if (!m_spCamera) { return; }
//
//	m_spCamera->SetToShader();
//}

void CameraBase::SetPos(const Math::Vector3& a_pos)
{
	return m_transMat.Translation(a_pos);
}

void CameraBase::SetRote(const float a_deg)
{
	m_rotateMatX = Math::Matrix::CreateRotationX(a_deg);

}

const Math::Vector3 CameraBase::GetPos()
{
	m_transMat = Math::Matrix::CreateTranslation(0, 5, -4);//ˆÊ’uî•ñ‚Ì‚İ‚Ìs—ñ

	return m_transMat.Translation();
}

//void CameraBase::SetTarget(const std::shared_ptr<const KdGameObject>& target)
//{
//	if (!target) { return; }
//
//	m_wpTarget = target;
//}

void CameraBase::PlsPOV(int pls)
{
	m_pov += pls;
	if (m_pov >= 70)
	{
		m_pov = 70;
	}
}
