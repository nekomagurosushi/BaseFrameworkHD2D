#pragma once
#include "CameraBase.h"

class FpsCamera : public CameraBase
{
public:
	FpsCamera() {}
	virtual ~FpsCamera()	override {}

	void Init()					override;
	void Update()				override;
private:
	void UpdateRotateByMouse();
	POINT m_FixMousePos;
};