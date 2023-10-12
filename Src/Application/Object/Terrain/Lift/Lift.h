#pragma once

class Lift : public KdGameObject
{
public:
	Lift() {}
	~Lift()		override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

	bool IsRideable() const override { return true; }

private:
	std::shared_ptr<KdModelWork>	m_spModel = nullptr;

	Math::Vector3 m_startPos;
	Math::Vector3 m_endPos;

	float m_progress=0;
	float m_speed=0;


	float m_isReverse=false;
};