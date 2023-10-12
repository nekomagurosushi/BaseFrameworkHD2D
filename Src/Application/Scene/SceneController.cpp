#include "SceneController.h"
#include "Application/Scene/Child/TitleScene.h"

SceneController::SceneController():
    m_scene(new TitleScene)
{}

SceneController::~SceneController()
{
    delete m_scene;
}

void SceneController::Init()
{
    if (m_scene == nullptr)return;
    m_scene->Init();
}

void SceneController::SceneUpdate()
{
    if (m_scene == nullptr)return;
    Scene* p = m_scene->Update();
    m_scene->MatrixUpdate();
    if (p != m_scene) {
        p->Init();
       m_scene=p;
    }
}

void SceneController::PostUpdate()
{
    if (m_scene == nullptr)return;
    m_scene->PostUpdate();
}

void SceneController::DrawLit() const
{
    if (m_scene == nullptr)return;
    m_scene->DrawLit();
}

void SceneController::DrawUnLit() const
{
    if (m_scene == nullptr)return;
    m_scene->DrawUnLit();
}

void SceneController::DrawBright() const
{
    if (m_scene == nullptr)return;
    m_scene->DrawBright();
}

void SceneController::DrawSprite() const
{
    if (m_scene == nullptr)return;
    m_scene->DrawSprite();
}
