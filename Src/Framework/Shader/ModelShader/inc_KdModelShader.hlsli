//�萔�o�b�t�@�ib0�́u0�Ԗڂ̃o�b�t�@���g���v�Ƃ����Ӗ��j
//�i���j�Z�b�g�����f�[�^�ƁA�����������ɔz�u����K�v������̂Œ���
cbuffer cbObject : register(b0)
{
    float2 g_UVOffset;
    float2 g_UVTiling;
   
}

// �萔�o�b�t�@(���b�V���P��)
cbuffer cbMesh : register(b1)
{
	// �I�u�W�F�N�g���
    row_major float4x4 g_mW; // ���[���h�ϊ��s��
};

//������₷�����邽�߁A�}�e���A���f�[�^���\���̂ɂ܂Ƃ߂܂�
struct Material
{
    float4 BaseColor; //�x�[�X�F
    float3 Emissive; //���Ȕ����F
    float Metallic; //�����x
    float Roughness; //�e��
};

//�}�e���A���萔�o�b�t�@
cbuffer cbMaterial : register(b2)
{
    Material g_material;
}

// �{�[���s��z��
cbuffer cbBones : register(b3)
{
    row_major float4x4 g_mBones[300];
};

//���_�V�F�[�_�[����o�͂���f�[�^
struct VSOutput
{
    float4 Pos : SV_Position; // �ˉe���W
    float2 UV : TEXCOORD0; // UV���W
    float3 wN : TEXCOORD1; // ���[���h�@��
    float4 Color : TEXCOORD2; // �F
    float3 wPos : TEXCOORD3; // ���[���h3D���W
    float3 wT : TEXCOORD4;
    float3 wB : TEXCOORD5;
};
