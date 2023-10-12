#pragma once
#include "CameraBase.h"

class TpsCamera : public CameraBase
{
public:
	TpsCamera() {}
	virtual ~TpsCamera()	override {}

	void Init()					override;
	void Update()				override;

private:
	void UpdateRotateByMouse();
	POINT m_FixMousePos;
};