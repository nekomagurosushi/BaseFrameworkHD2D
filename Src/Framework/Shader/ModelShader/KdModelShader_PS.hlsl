//カメラやライトのデータがつけるようになる
#include "../inc_KdCommon.hlsli"
//共通データ
#include "inc_KdModelShader.hlsli"

//テクスチャ（t0やt1は、PSSetShaderResourscesでセットしたときのスロット番号）
Texture2D g_baseTex : register(t0); //ベースカラーテスクチャ
Texture2D g_emissiveTex : register(t1); //エミッシブテクスチャ
Texture2D g_mrTex : register(t2); //メタリック/ラフネステクスチャ
Texture2D g_normalTex : register(t3); //法線マップ

//サンプラ（テクスチャから色を取得する時に使う）
SamplerState g_ss : register(s0);
//SamplerState g_clampSS : register(s1);//Clamp設定のサンプラ（KdShaderManagerでs1にセットしています）

// Blinn-Phong NDF
//・lightDir     ・・・ライトの方向
//・vCam     ・・・ピクセルからカメラへのの方向
//・normal     ・・・法線
//・specPower     ・・・反射の鋭さ

float BlinnPhong(float3 lightDir, float3 vCam, float3 normal, float specPower)
{
    float3 H = normalize(-lightDir + vCam);
    float NdotH = saturate(dot(normal, H));
    float spec = pow(NdotH, specPower);
    // 反射した光の強さを求める
	
    return spec * ((specPower + 2) / (2 * 3.1415926535));
}


//=========================================
//ピクセルシェーダー　1つ1つのピクセルがやってくる
//=========================================
float4 main(VSOutput In) : SV_Target0
{
   // カメラへの方向
    float3 vCam = g_CamPos - In.wPos;
    float camDist = length(vCam); // カメラ - ピクセル距離
    vCam = normalize(vCam);
   
    // 法線マップから法線ベクトル取得
    float3 wN = g_normalTex.Sample(g_ss, In.UV).rgb;

	// UV座標（0～1）から 射影座標（-1～1）へ変換
    wN = wN * 2.0 - 1.0;

	{
		// 3種の法線から法線行列を作成
        row_major float3x3 mTBN =
        {
            normalize(In.wT),
			normalize(In.wB),
			normalize(In.wN),
        };

		// 法線ベクトルをこのピクセル空間へ変換
        wN = mul(wN, mTBN);
    }

	// 法線正規化
    wN = normalize(wN);
    
    //テクスチャから色を取得
    float4 baseColor = g_baseTex.Sample(g_ss, In.UV) * g_material.BaseColor * In.Color;
    float4 mr = g_mrTex.Sample(g_ss, In.UV);
    
    //粗さ
    float roughness = mr.g * g_material.Roughness;
    // 金属性
    float metallic = mr.b * g_material.Metallic;
    
    //=========================================
    //ライティング
    //=========================================
    //最終的な色
    float3 outColor = 0;
    const float3 baseDiffuse = lerp(baseColor.rgb, float3(0, 0, 0), metallic);
    float3 baseSpecular = lerp(0.04, baseColor.rgb, metallic);
    //平行光は複数あるため、使用しているであろう本数だけ計算する
    {
    //=========================================
    //拡散光
    //=========================================
    // 光の方向と法線の方向との角度さが光の強さになる
    //Lambertモデル
        float lightDiffuse = dot(-g_DL_Dir, wN); //内積で角度の差を求める
        lightDiffuse = saturate(lightDiffuse); // マイナス値は0にする　0(暗)～1(明)になる
    
    //if (lightDiffuse > 0.5)lightDiffuse=1;
    //else lightDiffuse = 0;
	//物理的に正しくするため 正規化Lambert
        lightDiffuse /= 3.1415926535;
    
    
    //飛び出る光を計算し、結果に加算する
	// 光の色 * 材質の拡散色 * 透明率
        outColor += (g_DL_Color * lightDiffuse) * baseDiffuse * baseColor.a;
    }
    
    //=========================================
    //反射光
    //=========================================
    //Phongモデル
    //float3 vRef = reflect(g_DL_Dir, wN);
    //float spec = dot(vRef,vCam);
    //ラフネス(粗さ)から、SpecularPowerを求める
    //specPower~2^(13*g) グロス値ｇ＝0～1で1～8192のスベキュラ強度を求める
    //roughnessを逆転させ滑らかにする
    //roughnessを２乗するのは、その方が感覚的にリアルになるらしい
        float smoothness = 1.0f - roughness;
        float specPower = pow(2, 13 * smoothness); //1～2048
    
        float spec = BlinnPhong(g_DL_Dir, vCam, wN, specPower);
	// 光の色 * 反射光の強さ * 材質の反射色 * 透明率 * 適当な調整値
        outColor += (g_DL_Color * spec) * baseSpecular * baseColor.a;
    
    //=========================================
    //環境光
    //=========================================
    outColor += g_AmbientLight.rgb * baseColor.rgb * baseColor.a;
  
    outColor += g_emissiveTex.Sample(g_ss, In.UV).rgb * g_material.Emissive;

    //=========================================
    //コーンライト
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
	////ここでラスタライズされたピクセルに色を付ける
 //   return g_material.BaseColor;
	
}