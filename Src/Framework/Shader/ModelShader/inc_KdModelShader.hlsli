//定数バッファ（b0は「0番目のバッファを使う」という意味）
//（注）セットしたデータと、同じメモリに配置する必要があるので注意
cbuffer cbObject : register(b0)
{
    float2 g_UVOffset;
    float2 g_UVTiling;
   
}

// 定数バッファ(メッシュ単位)
cbuffer cbMesh : register(b1)
{
	// オブジェクト情報
    row_major float4x4 g_mW; // ワールド変換行列
};

//分かりやすくするため、マテリアルデータを構造体にまとめます
struct Material
{
    float4 BaseColor; //ベース色
    float3 Emissive; //自己発光色
    float Metallic; //金属度
    float Roughness; //粗さ
};

//マテリアル定数バッファ
cbuffer cbMaterial : register(b2)
{
    Material g_material;
}

// ボーン行列配列
cbuffer cbBones : register(b3)
{
    row_major float4x4 g_mBones[300];
};

//頂点シェーダーから出力するデータ
struct VSOutput
{
    float4 Pos : SV_Position; // 射影座標
    float2 UV : TEXCOORD0; // UV座標
    float3 wN : TEXCOORD1; // ワールド法線
    float4 Color : TEXCOORD2; // 色
    float3 wPos : TEXCOORD3; // ワールド3D座標
    float3 wT : TEXCOORD4;
    float3 wB : TEXCOORD5;
};
