#pragma once
class KdModelShader
{

	struct cbBones;
public:
	// ���[���h�s��Z�b�g
	void SetWorldMatrix(const Math::Matrix& m)
	{
		m_cb1_Mesh.Work().mW = m;
	}

	// bone�p�萔�o�b�t�@�����̂܂ܕԂ�
	KdConstantBuffer<cbBones>& BoneCB()
	{
		return m_cb3_Bone;
	}

	//=========================================
	//�������E���
	//=========================================

	//������
	bool Init();

	//���
	void Release();

	//�f�X�g���N�^�Ŏ����ŉ������悤�ɂ���
	~KdModelShader() { Release(); }

	//=========================================
	//�`��
	//=========================================

	//���̃V�F�[�_�[���g�p�ł���悤�Ƀf�o�C�X�փZ�b�g
	void SetToDevice();

	//1�̃��b�V����`��
	//�Emesh			�E�E�E�`�悷�郁�b�V��
	//�Ematerials		�E�E�E�g�p����ގ��z��
	void DrawMesh(const KdMesh* mesh, const std::vector<KdMaterial>& materails, Math::Matrix mWorld);

	//�m�[�h�A�E�g���C�i�[���̂��ׂẴ��b�V����`�悷��
	//�܂��ADrawMesh�Ƃ͉����֐�����SetWorldMatrix�����s�����
	//1:nodeOL			�`�悷��A�E�g���C�i�[
	//2:materials		�`��Ɏg�p����}�e���A���z��
	//3:mWorld			���[���h�ϊ��s��@�e�m�[�h�͂��̍s���ŕϊ�����`�悷��
	//rModel����1��2��n���Ă���������S���Ă���H

	//�A�j���[�V�����Ȃ�
	void DrawModel(const KdModelData& rModel, const Math::Matrix mWorld);
	//�A�j���[�V��������i���͎g��Ȃ����X�L�����b�V���A�j���[�V�������ŏI�ڕW�Ȃ̂œ���Ă����j
	void DrawModel(KdModelWork& rModel, const Math::Matrix mWorld);


	//=========================================
	//�֊s�`��
	//=========================================
	//�֊s�`��Ƃ��ăf�o�C�X�փZ�b�g
	void SetToDevice_Outline();
	//1�̃��b�V����`��
	void DrawMesh_Outline(const KdMesh* mesh, const std::vector<KdMaterial>& materails, Math::Matrix mWorld);
	// 1�̃��b�V����`��
	void DrawModel_Outline(const KdModelData& rModel, const Math::Matrix mWorld);

	static const int maxBoneBufferSize = 300;
private:
	void SetMaterial(const KdMaterial& material);

	ID3D11VertexShader* m_VS = nullptr; //���_�V�F�[�_�[
	ID3D11InputLayout* m_inputlayout = nullptr; //���_���̓��C�A�E�g
	ID3D11VertexShader* m_VS_Skin = nullptr; //�i�X�L�����b�V���j���_�V�F�[�_�[
	ID3D11InputLayout* m_inputlayout_Skin = nullptr; //(�X�L�����b�V��)���_���̓��C�A�E�g

	ID3D11PixelShader* m_PS = nullptr; //�s�N�Z���V�F�[�_�[

	//�֊s�`��p
	ID3D11VertexShader* m_outlineVS = nullptr; //���_�V�F�[�_�[
	ID3D11PixelShader* m_outlinePS = nullptr; //�s�N�Z���V�F�[�_�[


	//�萔�o�b�t�@�p�̍\����
	struct cbObject
	{
		// UV����
		Math::Vector2	UVOffset = { 0.0f, 0.0f };
		Math::Vector2	UVTiling = { 1.0f, 1.0f };

	};
	//�萔�o�b�t�@
	KdConstantBuffer<cbObject> m_cb0;

	// �萔�o�b�t�@(���b�V���P�ʍX�V)
	struct cbMesh
	{
		Math::Matrix	mW;//���[���h�s��
	};
	KdConstantBuffer<cbMesh>		m_cb1_Mesh;

	//�萔�o�b�t�@�i�}�e���A���P�ʍX�V�j
	struct cbMaterial
	{
		Math::Vector4 BaseColor;
		Math::Vector3 Emissive;
		float Metallic;
		float Roughness;

		float tmp[3];
	};
	KdConstantBuffer<cbMaterial> m_cb2_Material;



	// �萔�o�b�t�@(�{�[���P�ʍX�V)
	struct cbBones
	{
		Math::Matrix	mat[300];//���[���h�s��
	};
	KdConstantBuffer<cbBones>		m_cb3_Bone;
};