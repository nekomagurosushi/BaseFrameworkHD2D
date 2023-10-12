//カメラやライトのデータが使えるようになる
#include "../inc_KdCommon.hlsli"
//共通データ
#include "inc_KdModelShader.hlsli"

//=========================================
//頂点シェーダー　1つ1つの頂点がやってくる
//=========================================
VSOutput main(
    float4 pos : POSITION, // 頂点座標
	float2 uv : TEXCOORD0, // テクスチャUV座標
	float3 normal : NORMAL, // 法線ベクトル
	float4 color : COLOR, // 頂点色
	float3 tangent : TANGENT // 接線
)
{
    VSOutput Out;
    
    //3D頂点座標を2Dへ変換
    Out.Pos = mul(pos, g_mW); //ワールド行列で変換し↓
    Out.wPos = Out.Pos.xyz; //ワールド座標を取っておく
    Out.Pos = mul(Out.Pos, g_mView); //カメラのビュー行列で変換し↓
    Out.Pos = mul(Out.Pos, g_mProj); //射影行列で変換       //（注）m_Proj=g_mP(カメラの射影変換行列)
	
    //UVはそのままピクセルシェーダーへ
    Out.UV = uv * g_UVTiling + g_UVOffset;
    //頂点色はそのままピクセルシェーダーへ
    Out.Color = color;
    //法線をワールド座標系へ変換
    Out.wN = normalize(mul(normal, (float3x3) g_mW));
    // 接線
    Out.wT = normalize(mul(tangent, (float3x3) g_mW));
	// 従接線
    float3 binormal = cross(normal, tangent);
    Out.wB = normalize(mul(binormal, (float3x3) g_mW));
    return Out; //射影行列（2D座標）に変換したのち値を返す（行先はラスタライザー）
}