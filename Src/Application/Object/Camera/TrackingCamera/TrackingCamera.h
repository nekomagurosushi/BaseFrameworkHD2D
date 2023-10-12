#pragma once
#include "../CameraBase.h"

class TrackingCamera : public CameraBase
{
public:
	TrackingCamera(const shared_ptr<const KdGameObject>& a_target) :
		wp_target(a_target),
		CameraBase()
	{
		Init();
	}
	virtual ~TrackingCamera()	override {}

	void Init()					override;
	//void Update()				override;
	void MatrixUpdate() override;
	const Math::Vector3 GetPos()override;
private:

	void UpdateRotateByMouse();

	weak_ptr<const KdGameObject>	wp_target;

	POINT m_fixMousePos;
};