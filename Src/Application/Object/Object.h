#pragma once
//#include "Application/TextureManager/TexInfo/Base/TexInfo.h"
using namespace std;
enum DegNum
{
	ZERO,
	HALF=180
};
enum StateType
{
	NEUTRAL = 1 << 0,
	WALK = 1 << 1,
	JUMP = 1 << 2,
	FALL = 1 << 3,
	SHOT = 1 << 4,
	GUARD = 1 << 5,
	HITTAKE=1<<6,
	DEATH=1<<7,
	BOOST = 1 << 8,
	OVERBOOST=1<<9
};
enum ColliType
{
	NONE,
	COLLI,
	SPECIALCOLLI
};
class Object :public KdGameObject
{
public:

	// �����ݒ�
	virtual void Init() = 0;
	// ���
	virtual void Release();

	// �X�V����
	virtual void Update();
	virtual void Update(const POINT a_mousePos);
	//

	//virtual void PosUpdate()=0;
	virtual void MatrixUpdate() = 0;

	virtual float GetDeg() { return 0.0f; }

	void SetStopTime(int time) { stopTime = time; }

	int GetStopTime() { return stopTime; }
	//�����t���O�Q�b�^�[
	virtual const bool GetBrightFlg()const;

	//�����蔻��n
	virtual const ColliType GetRayInfo(shared_ptr<KdCollider::RayInfo> a_spRayInfo) { return NONE; };


	//�����蔻��n
	virtual const bool GetSphereInfo(shared_ptr<KdCollider::SphereInfo> a_spSphereInfo) { return false; }

	virtual const float GetAnime()const { return 0; }

	virtual void Hit() {};
	virtual void Hit(Math::Vector3 hitVec) {}
protected:
	//�ŏ��ɕK���摜����n���Ă������ƁA��{�I��TextureManager����Ǎ���
	Object() :
		m_flg(true),
		m_roteMat(Math::Matrix::Identity),
		m_scaleMat(Math::Matrix::Identity),
		m_transMat(make_shared<Math::Matrix>()),
		m_brightFlg(false),
		stopTime(0)
	{
		*m_transMat = Math::Matrix::Identity;
	};
	~Object() {};
	bool m_flg;

	//��]�s��
	Math::Matrix m_roteMat;
	//�g�k�s��
	Math::Matrix m_scaleMat;
	//���W�s��
	shared_ptr<Math::Matrix> m_transMat;
	//�����t���O
	bool m_brightFlg;

	int stopTime;
};