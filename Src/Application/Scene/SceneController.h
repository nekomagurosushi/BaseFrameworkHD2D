#pragma once

class Scene;
using namespace std;
class SceneController
{
public:
	SceneController();
	~SceneController();

	void Init();
	void SceneUpdate();
	void PostUpdate();
	void DrawLit() const;
	void DrawUnLit() const;
	void DrawBright()const;
	void DrawSprite() const;
private:
	Scene *m_scene;
};