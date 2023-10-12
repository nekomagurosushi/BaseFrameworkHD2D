#pragma once
#include "Application/Object/Object.h"
class ModelWorkInfo;
class NormalBullet:public Object
{
public:
	NormalBullet(shared_ptr<ModelWorkInfo> asp_model,Math::Vector3 shotPos,Math::Matrix cameraRote):
		sp_model(asp_model),
		m_damage(10.0f),
		m_moveVec(Math::Vector3::TransformNormal(Math::Vector3::Backward, cameraRote)),
		m_moveVal(1.0f),
		Object()
	{
		*m_transMat = Math::Matrix::CreateTranslation(shotPos);
		m_roteMat = m_roteMat * cameraRote;
	}
	void Init()override;

	void Update()override;
	void MatrixUpdate()override;

	void DrawLit()override;

	void Hit();
private:
	shared_ptr<ModelWorkInfo> sp_model;
	//Math::Vector3 m_shotPos;

	int m_damage=10;

	Math::Vector3 m_moveVec;
	int m_moveVal=2.0f;
};