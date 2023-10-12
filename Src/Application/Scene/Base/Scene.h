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
	
	//������
	virtual void Init()=0;
	//���
	void Release();
	//�V�[���̍X�V���s���Ainput�ɓ��e�ɂ����Scene�̑J�ڂ��s��
	virtual Scene* Update() = 0;
	virtual void MatrixUpdate(){}

	virtual void PostUpdate();
	//�V�[���̕`����s��
	//�ʏ�`��i�A�e�A���j
	virtual void DrawLit() const;
	//�ʏ�`��i�A�e�����j
	virtual void DrawUnLit()const;
	//�`��i�����j
	virtual void DrawBright() const;
	//�`��i��ʂ��猩��XY���ʁj
	virtual void DrawSprite() const;
protected:
	Scene():
	m_texManager(make_shared<TexManager>()),
	m_objectList(make_shared<vector<shared_ptr<Object>>>()),
	m_fadeTex(nullptr),
	m_fadeTime(0),
	m_camera(nullptr)
	{}
	
	//�e�N�X�`���}�l�\�W���[
	shared_ptr<TexManager> m_texManager;
	//�S�ẴI�u�W�F�N�g�̃��X�g
	shared_ptr<vector<shared_ptr<Object>>> m_objectList;

	shared_ptr<const PlaneTexInfo> m_fadeTex;
	int m_fadeTime;
	//�J����
	shared_ptr<CameraBase> m_camera;
};