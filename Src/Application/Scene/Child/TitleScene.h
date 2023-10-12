#pragma once
#include "Application/Scene/Base/Scene.h"
#include "Application/UI/Child/StartButton.h"
class NormalBullet;
class TitleScene :public Scene
{
public:
	//TitleScene(SceneController& a_sceneCtr):Scene(a_sceneCtr){}
	TitleScene():
	m_titleTex(nullptr),
	m_startButton(nullptr),
	m_frame(0),
	sp_bulletList(make_shared<vector<shared_ptr<NormalBullet>>>())
	{
		m_texManager->JsonLoad("Json/System.json");
		m_titleTex = m_texManager->LoadPlaneTexInfo("Title");
		m_startButton = make_shared<StartButton>(m_texManager);
		m_startButton->Init();
	}
	~TitleScene() override{}

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
	shared_ptr<PlaneTexInfo> m_titleTex;
	shared_ptr<StartButton> m_startButton;
	int m_frame;

	shared_ptr<vector<shared_ptr<NormalBullet>>> sp_bulletList;
};