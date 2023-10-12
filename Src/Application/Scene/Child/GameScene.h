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
	//通常描画（陰影アリ）
	void DrawLit() const override;
	//通常描画（陰影無し）
	void DrawUnLit()const override;
	//描画（光源）
	void DrawBright() const override;
	//描画（画面から見てXY平面）
	void DrawSprite()const override;
private:
	void CollisionUpdate(shared_ptr<Object> a_spObject);
	//フェードイン、フェードアウト用の変数
	int m_frame;

	shared_ptr<vector<shared_ptr<NormalBullet>>> sp_bulletList;

	SceneState m_sceneState;
	bool m_tabKeyFlg;
};