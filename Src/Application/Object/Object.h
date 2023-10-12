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

	// 初期設定
	virtual void Init() = 0;
	// 解放
	virtual void Release();

	// 更新処理
	virtual void Update();
	virtual void Update(const POINT a_mousePos);
	//

	//virtual void PosUpdate()=0;
	virtual void MatrixUpdate() = 0;

	virtual float GetDeg() { return 0.0f; }

	void SetStopTime(int time) { stopTime = time; }

	int GetStopTime() { return stopTime; }
	//光源フラグゲッター
	virtual const bool GetBrightFlg()const;

	//当たり判定系
	virtual const ColliType GetRayInfo(shared_ptr<KdCollider::RayInfo> a_spRayInfo) { return NONE; };


	//当たり判定系
	virtual const bool GetSphereInfo(shared_ptr<KdCollider::SphereInfo> a_spSphereInfo) { return false; }

	virtual const float GetAnime()const { return 0; }

	virtual void Hit() {};
	virtual void Hit(Math::Vector3 hitVec) {}
protected:
	//最初に必ず画像情報を渡しておくこと、基本的にTextureManagerから読込む
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

	//回転行列
	Math::Matrix m_roteMat;
	//拡縮行列
	Math::Matrix m_scaleMat;
	//座標行列
	shared_ptr<Math::Matrix> m_transMat;
	//光源フラグ
	bool m_brightFlg;

	int stopTime;
};