//カメラやライトのデータがつけるようになる
#include "../inc_KdCommon.hlsli"
//共通データ
#include "inc_KdModelShader.hlsli"


//=========================================
//ピクセルシェーダー　1つ1つのピクセルがやってくる
//=========================================
float4 main(VSOutput In) : SV_Target0
{
    
    return float4(0, 0, 0, 1);
	
}