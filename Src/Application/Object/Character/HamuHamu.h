#pragma once
class CameraBase;
class HamuHamu : public KdGameObject
{
public:
	HamuHamu() {}
	virtual ~HamuHamu()		override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;
	void DrawSprite()			override;
	void SetCamera(std::weak_ptr<CameraBase> a_camera) { m_camera = a_camera;}
	
	void RegestHitObject(const std::shared_ptr<KdGameObject>& object)
	{
		m_wpHitObjectlist.push_back(object);
	}
private:
	void UpdateRotate(Math::Vector3& srcMoveVec);
	void UpdataCollision();
	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;
	std::weak_ptr<CameraBase> m_camera;
	std::vector<std::weak_ptr<KdGameObject>> m_wpHitObjectlist;

	Math::Vector3 m_worldRot;

	float								m_gravity = 0;

	//èÊÇËï®êßå‰ä÷åW
	Math::Matrix						m_mLocalFrromRideObject;
	std::weak_ptr<KdGameObject>			m_wpRideObject;
};