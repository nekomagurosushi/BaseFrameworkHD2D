#pragma once
using namespace std;
class CameraBase : public KdGameObject
{
public:
	CameraBase() :
		m_spCamera(make_shared<KdCamera>()),
		m_rotateMatX(Math::Matrix::Identity),
		m_rotateMatY(Math::Matrix::Identity),
		m_rotateMatZ(Math::Matrix::Identity),
		m_transMat(Math::Matrix::Identity),
		m_pov(60)
	{
		
	}
	virtual ~CameraBase()	override	{}

	void Init()				override;
	//void Update()			override;
	virtual void MatrixUpdate()=0;
	//void PreDraw()			override;

	virtual void SetPos(const Math::Vector3& a_pos);
	virtual void SetRote(const float a_deg);
	virtual const Math::Vector3 GetPos();

	/*void SetTarget(const std::shared_ptr<const KdGameObject>& target);
	*/
	std::shared_ptr<const KdCamera> WorkCamera() const 
	{ 
		return m_spCamera;
	}

	const std::shared_ptr<const KdCamera>& GetCamera() const
	{
		return m_spCamera;//前const 参照するだけ,変更不可//後const 関数内部での変更不可
	}

	const Math::Matrix GetRotationYMatrix() const
	{
		//return Math::Matrix::CreateFromYawPitchRoll//y,x,z
		//(
		//	DirectX::XMConvertToRadians(m_DegAng.y),
		//	DirectX::XMConvertToRadians(m_DegAng.x),
		//	DirectX::XMConvertToRadians(m_DegAng.z)
		//);
		return m_rotateMatY;
	}

	/*const Math::Matrix  GetRotationMatrix() const
	{
		return m_rotateMatY;
	}*/

	void SetPOV(int pov) { m_pov = pov; }
	void PlsPOV(int pls = 1);
	int GetPOV() { return m_pov; }
protected:
	shared_ptr<KdCamera>			m_spCamera = nullptr;


	Math::Matrix m_rotateMatX;
	Math::Matrix m_rotateMatY;
	Math::Matrix m_rotateMatZ;
	Math::Matrix m_transMat;

	int m_pov;
};