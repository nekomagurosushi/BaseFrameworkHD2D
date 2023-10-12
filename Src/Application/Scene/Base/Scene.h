#pragma once
#include "Application/Scene/SceneController.h"
#include "Application/Object/Object.h"
#include "Application/TextureManager/TexManager.h"
#include "Application/Object/Camera/CameraBase.h"
using namespace std;
class PlaneTexInfo;
class Scene
{
public:
	virtual ~Scene()=default;
	
	//初期化
	virtual void Init()=0;
	//解放
	void Release();
	//シーンの更新を行い、inputに内容によってSceneの遷移を行う
	virtual Scene* Update() = 0;
	virtual void MatrixUpdate(){}

	virtual void PostUpdate();
	//シーンの描画を行う
	//通常描画（陰影アリ）
	virtual void DrawLit() const;
	//通常描画（陰影無し）
	virtual void DrawUnLit()const;
	//描画（光源）
	virtual void DrawBright() const;
	//描画（画面から見てXY平面）
	virtual void DrawSprite() const;
protected:
	Scene():
	m_texManager(make_shared<TexManager>()),
	m_objectList(make_shared<vector<shared_ptr<Object>>>()),
	m_fadeTex(nullptr),
	m_fadeTime(0),
	m_camera(nullptr)
	{}
	
	//テクスチャマネ―ジャー
	shared_ptr<TexManager> m_texManager;
	//全てのオブジェクトのリスト
	shared_ptr<vector<shared_ptr<Object>>> m_objectList;

	shared_ptr<const PlaneTexInfo> m_fadeTex;
	int m_fadeTime;
	//カメラ
	shared_ptr<CameraBase> m_camera;
};