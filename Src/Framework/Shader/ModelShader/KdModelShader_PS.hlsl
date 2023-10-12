//�J�����⃉�C�g�̃f�[�^������悤�ɂȂ�
#include "../inc_KdCommon.hlsli"
//���ʃf�[�^
#include "inc_KdModelShader.hlsli"

//�e�N�X�`���it0��t1�́APSSetShaderResoursces�ŃZ�b�g�����Ƃ��̃X���b�g�ԍ��j
Texture2D g_baseTex : register(t0); //�x�[�X�J���[�e�X�N�`��
Texture2D g_emissiveTex : register(t1); //�G�~�b�V�u�e�N�X�`��
Texture2D g_mrTex : register(t2); //���^���b�N/���t�l�X�e�N�X�`��
Texture2D g_normalTex : register(t3); //�@���}�b�v

//�T���v���i�e�N�X�`������F���擾���鎞�Ɏg���j
SamplerState g_ss : register(s0);
//SamplerState g_clampSS : register(s1);//Clamp�ݒ�̃T���v���iKdShaderManager��s1�ɃZ�b�g���Ă��܂��j

// Blinn-Phong NDF
//�ElightDir     �E�E�E���C�g�̕���
//�EvCam     �E�E�E�s�N�Z������J�����ւ̂̕���
//�Enormal     �E�E�E�@��
//�EspecPower     �E�E�E���˂̉s��

float BlinnPhong(float3 lightDir, float3 vCam, float3 normal, float specPower)
{
    float3 H = normalize(-lightDir + vCam);
    float NdotH = saturate(dot(normal, H));
    float spec = pow(NdotH, specPower);
    // ���˂������̋��������߂�
	
    return spec * ((specPower + 2) / (2 * 3.1415926535));
}


//=========================================
//�s�N�Z���V�F�[�_�[�@1��1�̃s�N�Z��������Ă���
//=========================================
float4 main(VSOutput In) : SV_Target0
{
   // �J�����ւ̕���
    float3 vCam = g_CamPos - In.wPos;
    float camDist = length(vCam); // �J���� - �s�N�Z������
    vCam = normalize(vCam);
   
    // �@���}�b�v����@���x�N�g���擾
    float3 wN = g_normalTex.Sample(g_ss, In.UV).rgb;

	// UV���W�i0�`1�j���� �ˉe���W�i-1�`1�j�֕ϊ�
    wN = wN * 2.0 - 1.0;

	{
		// 3��̖@������@���s����쐬
        row_major float3x3 mTBN =
        {
            normalize(In.wT),
			normalize(In.wB),
			normalize(In.wN),
        };

		// �@���x�N�g�������̃s�N�Z����Ԃ֕ϊ�
        wN = mul(wN, mTBN);
    }

	// �@�����K��
    wN = normalize(wN);
    
    //�e�N�X�`������F���擾
    float4 baseColor = g_baseTex.Sample(g_ss, In.UV) * g_material.BaseColor * In.Color;
    float4 mr = g_mrTex.Sample(g_ss, In.UV);
    
    //�e��
    float roughness = mr.g * g_material.Roughness;
    // ������
    float metallic = mr.b * g_material.Metallic;
    
    //=========================================
    //���C�e�B���O
    //=========================================
    //�ŏI�I�ȐF
    float3 outColor = 0;
    const float3 baseDiffuse = lerp(baseColor.rgb, float3(0, 0, 0), metallic);
    float3 baseSpecular = lerp(0.04, baseColor.rgb, metallic);
    //���s���͕������邽�߁A�g�p���Ă���ł��낤�{�������v�Z����
    {
    //=========================================
    //�g�U��
    //=========================================
    // ���̕����Ɩ@���̕����Ƃ̊p�x�������̋����ɂȂ�
    //Lambert���f��
        float lightDiffuse = dot(-g_DL_Dir, wN); //���ςŊp�x�̍������߂�
        lightDiffuse = saturate(lightDiffuse); // �}�C�i�X�l��0�ɂ���@0(��)�`1(��)�ɂȂ�
    
    //if (lightDiffuse > 0.5)lightDiffuse=1;
    //else lightDiffuse = 0;
	//�����I�ɐ��������邽�� ���K��Lambert
        lightDiffuse /= 3.1415926535;
    
    
    //��яo������v�Z���A���ʂɉ��Z����
	// ���̐F * �ގ��̊g�U�F * ������
        outColor += (g_DL_Color * lightDiffuse) * baseDiffuse * baseColor.a;
    }
    
    //=========================================
    //���ˌ�
    //=========================================
    //Phong���f��
    //float3 vRef = reflect(g_DL_Dir, wN);
    //float spec = dot(vRef,vCam);
    //���t�l�X(�e��)����ASpecularPower�����߂�
    //specPower~2^(13*g) �O���X�l����0�`1��1�`8192�̃X�x�L�������x�����߂�
    //roughness���t�]�������炩�ɂ���
    //roughness���Q�悷��̂́A���̕������o�I�Ƀ��A���ɂȂ�炵��
        float smoothness = 1.0f - roughness;
        float specPower = pow(2, 13 * smoothness); //1�`2048
    
        float spec = BlinnPhong(g_DL_Dir, vCam, wN, specPower);
	// ���̐F * ���ˌ��̋��� * �ގ��̔��ːF * ������ * �K���Ȓ����l
        outColor += (g_DL_Color * spec) * baseSpecular * baseColor.a;
    
    //=========================================
    //����
    //=========================================
    outColor += g_AmbientLight.rgb * baseColor.rgb * baseColor.a;
  
    outColor += g_emissiveTex.Sample(g_ss, In.UV).rgb * g_material.Emissive;

    //=========================================
    //�R�[�����C�g
    //=========================================
    {
        float3 toDir = g_ConeLight.pos - In.wPos;
        float len=length(toDir);
        
        if (len<g_ConeLight.range)
        {
            toDir = normalize(toDir);
            
            float rad = acos(saturate(dot(toDir, -g_ConeLight.dir)));
            
            if(rad=g_ConeLight.angle)
            {
                float atte = saturate(1 - len / g_ConeLight.range);
                
                float lightDiffuse = saturate(dot(normalize(wN), toDir));
                
                lightDiffuse *= atte;
                outColor += (g_ConeLight.color * lightDiffuse) * baseDiffuse * baseColor.rgb;
                
                float spec = BlinnPhong(-toDir, vCam, wN, specPower);
                spec += atte;
                outColor += (g_ConeLight.color*spec)*baseSpecular*baseColor.a;

            }
        }

    }
    return float4(outColor, baseColor.a);
	////�����Ń��X�^���C�Y���ꂽ�s�N�Z���ɐF��t����
 //   return g_material.BaseColor;
	
}