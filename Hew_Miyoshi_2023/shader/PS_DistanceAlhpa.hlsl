#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

//定数バッファの定義
cbuffer Polar : register(b6)
{
    float maxDistance;
    float3 objectPos; //影の持ち主の座標
}


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    if (Material.TextureEnable)
    {
        outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
        outDiffuse *= In.Diffuse;
    }
    else
    {
        outDiffuse.xyz = In.Diffuse.xyz;
        outDiffuse = In.Diffuse;
        //outDiffuse.a = 1.0f;
    }
     // ワールド座標空間でのカメラ位置
    float3 cameraPosition = float3(0, 0, 0); // カメラ位置を設定
    
    // 頂点座標をワールド座標空間に変換
    float3 worldPosition = mul(In.Position, World).xyz;
    
    // カメラから頂点までの距離を計算
    float distance = length(worldPosition - cameraPosition);
    
    // 透明度を距離に基づいて計算
    //float maxDistance = 10.0; // 透明になる距離の設定
    float nowDistance = distance / maxDistance; // 0から1の範囲に正規化
    
    // 透明度を元の色と合成するために、元の色を設定
    float4 originalColor = float4(0.8, 0.8, 0.8, 1.0); // 例: 赤色の元の色
    
    // 透明度を考慮して最終的な色を計算  
    outDiffuse.a = originalColor.a * (1.0 - nowDistance); // 透明度を適用 
    //outDiffuse.a = 0.0f;
}