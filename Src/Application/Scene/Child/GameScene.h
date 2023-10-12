#pragma once
#include "Application/Scene/Base/Scene.h"
class NormalBullet;

enum SceneState
{
	NORMAL = 1 << 0,
	STOP = 1 << 1
};

class GameScene :public Scene
{
public:
	//TitleScene(SceneController& a_sceneCtr):Scene(a_sceneCtr){}
	GameScene() :
		m_frame(0),
		sp_bulletList(make_shared<vector<shared_ptr<NormalBullet>>>()),
		m_sceneState(NORMAL),
		m_tabKeyFlg(false)
	{
	}
	~GameScene() override {}

	void Init()override;
	Scene* Update()override;
	void MatrixUpdate()override;
	//�ʏ�`��i�A�e�A���j
	void DrawLit() const override;
	//�ʏ�`��i�A�e�����j
	void DrawUnLit()const override;
	//�`��i�����j
	void DrawBright() const override;
	//�`��i��ʂ��猩��XY���ʁj
	void DrawSprite()const override;
private:
	void CollisionUpdate(shared_ptr<Object> a_spObject);
	//�t�F�[�h�C���A�t�F�[�h�A�E�g�p�̕ϐ�
	int m_frame;

	shared_ptr<vector<shared_ptr<NormalBullet>>> sp_bulletList;

	SceneState m_sceneState;
	bool m_tabKeyFlg;
};