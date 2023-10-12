#pragma once
#include "Application/Object/Object.h"
#include "Application/TextureManager/TexManager.h"
#include "Application/UI/Child/Gauge/Cild/HpGauge.h"
#include "Application/UI/Child/Gauge/Cild/BoostGauge.h"
#include "Application/UI/Child/Reticle.h"
#include "Application/UI/Child/NumberList.h"
class CameraBase;
class ModelWorkInfo;
class NormalBullet;

class Player :public Object
{
public:
	//最初に必ずTexInfo型変数を渡しておくこと、基本的にTextureManagerから読込む
	/*(注意)マジックナンバー*/
	Player(shared_ptr<TexManager> a_texManager) :
		m_tex(a_texManager->LoadModelWorkInfo("player")),
		m_bulletModel(a_texManager->LoadModelWorkInfo("normalBullet")),
		m_moveVal(Math::Vector3 { 0.1f, 0.1f, 0.1f }),
		m_dir(Math::Vector3::Zero),
		m_deg(0),
		m_gravity(0),
		m_state(NEUTRAL),
		m_maxHp(make_shared<int>()),
		m_hp(make_shared<int>()),
		m_maxEnergy(make_shared<int>()),
		m_energy(make_shared<int>()),
		Object()
	{
		*m_maxHp = 100;
		*m_hp = 100;
		*m_maxEnergy = 100000;
		*m_energy = 100000;
		m_hpGauge = make_shared<HpGauge>(a_texManager, m_hp,m_maxHp);
		m_boostGauge = make_shared<BoostGauge>(a_texManager, m_energy,m_maxEnergy);
		m_reticle = make_shared<Reticle>(a_texManager);
		m_brightFlg = false;
		m_mWorld.CreateTranslation(0, 30.0f, 0);

		int lg = *m_maxHp;
		lg=log10(lg);
		for (int i = 0; i <= lg; i++)
		{
			shared_ptr<NumberList> number = make_shared<NumberList>(a_texManager,i);
			number->Init();
			m_numberList.push_back(number);
		}
	}
	~Player() {}

	void Init()override;

	void Update()override;
	void MatrixUpdate()override;
	void PostUpdate()override;

	void DrawLit()override;
	void DrawSprite()override;

	float GetDeg() override;
	void SetCamera(std::weak_ptr<CameraBase> a_camera) { m_camera = a_camera; }
	void SetBulletList(weak_ptr<vector<shared_ptr<NormalBullet>>> asp_objectList) { wp_bulletList = asp_objectList;}

	const ColliType GetRayInfo(shared_ptr<KdCollider::RayInfo> a_spRayInfo)override;
	void SetPos(const Math::Vector3& pos)override;
	const bool GetSphereInfo(shared_ptr<KdCollider::SphereInfo> a_spSphereInfo)override;

	//void SetSlahtex(shared_ptr<SqPolyInfo> a_slashTex);
private:
	shared_ptr<ModelWorkInfo> m_tex;
	shared_ptr<ModelWorkInfo> m_bulletModel;

	shared_ptr<HpGauge> m_hpGauge;
	shared_ptr<BoostGauge> m_boostGauge;
	shared_ptr<Reticle> m_reticle;

	std::weak_ptr<CameraBase> m_camera;

	//移動量
	Math::Vector3 m_moveVal;

	float m_boostVal;
	int m_overBoostCnt;

	Math::Vector3 m_dir;

	//マウスの方向
	float m_deg;

	float m_gravity;

	StateType m_state;

	weak_ptr<vector<shared_ptr<NormalBullet>>> wp_bulletList;

	vector<shared_ptr<NumberList>> m_numberList;
	//ステータス
	shared_ptr<int> m_maxHp;
	shared_ptr<int> m_hp;
	shared_ptr<int> m_maxEnergy;
	shared_ptr<int> m_energy;
};