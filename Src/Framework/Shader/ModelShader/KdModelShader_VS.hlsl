//�J�����⃉�C�g�̃f�[�^���g����悤�ɂȂ�
#include "../inc_KdCommon.hlsli"
//���ʃf�[�^
#include "inc_KdModelShader.hlsli"

//=========================================
//���_�V�F�[�_�[�@1��1�̒��_������Ă���
//=========================================
VSOutput main(
    float4 pos : POSITION, // ���_���W
	float2 uv : TEXCOORD0, // �e�N�X�`��UV���W
	float3 normal : NORMAL, // �@���x�N�g��
	float4 color : COLOR, // ���_�F
	float3 tangent : TANGENT // �ڐ�
)
{
    VSOutput Out;
    
    //3D���_���W��2D�֕ϊ�
    Out.Pos = mul(pos, g_mW); //���[���h�s��ŕϊ�����
    Out.wPos = Out.Pos.xyz; //���[���h���W������Ă���
    Out.Pos = mul(Out.Pos, g_mView); //�J�����̃r���[�s��ŕϊ�����
    Out.Pos = mul(Out.Pos, g_mProj); //�ˉe�s��ŕϊ�       //�i���jm_Proj=g_mP(�J�����̎ˉe�ϊ��s��)
	
    //UV�͂��̂܂܃s�N�Z���V�F�[�_�[��
    Out.UV = uv * g_UVTiling + g_UVOffset;
    //���_�F�͂��̂܂܃s�N�Z���V�F�[�_�[��
    Out.Color = color;
    //�@�������[���h���W�n�֕ϊ�
    Out.wN = normalize(mul(normal, (float3x3) g_mW));
    // �ڐ�
    Out.wT = normalize(mul(tangent, (float3x3) g_mW));
	// �]�ڐ�
    float3 binormal = cross(normal, tangent);
    Out.wB = normalize(mul(binormal, (float3x3) g_mW));
    return Out; //�ˉe�s��i2D���W�j�ɕϊ������̂��l��Ԃ��i�s��̓��X�^���C�U�[�j
}