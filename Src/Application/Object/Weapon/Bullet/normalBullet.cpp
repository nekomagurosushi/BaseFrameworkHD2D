#include "normalBullet.h"
#include "Application/TextureManager/TexInfo/Child/ModelWorkInfo.h"
void NormalBullet::Init()
{
	
}

void NormalBullet::Update()
{
	Math::Vector3 nowPos=m_transMat->Translation();
	nowPos += m_moveVec*m_moveVal;
	*m_transMat = Math::Matrix::CreateTranslation(nowPos);
}

void NormalBullet::MatrixUpdate()
{
	m_mWorld = m_scaleMat * m_roteMat * (*m_transMat);
}

void NormalBullet::DrawLit()
{
	if (sp_model->GetTex() == nullptr)return;
	sp_model->GetTex()->CalcNodeMatrices();
	KdShaderManager::Instance().m_modelShader.DrawModel(*sp_model->GetTex(), m_mWorld);
}

void NormalBullet::Hit()
{
	m_flg = false;
}
