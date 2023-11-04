#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

//定数バッファの定義
cbuffer Polar : register(b7)
{
    float bloom;
    float power;
    float2 dummy;
}

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    // サンプリングしたピクセルの輝度を取得
    float4 color = g_Texture.Sample(g_SamplerState, In.TexCoord);
    float luminance = dot(color.rgb, float3(0.299, 0.587, 0.114));

    //ブルームの強度を設定 (適切な値を調整)
    float bloomIntensity = bloom; // 例として0.5に設定

    // ブルームエフェクトを拡散させる
    // 例としてガウシアンブラーを使用する場合
    float2 blurOffsets[5] = { float2(-1, -1), float2(0, -1), float2(1, -1), float2(-1, 0), float2(0, 0) };
    float4 blurredColor = float4(0.0, 0.0, 0.0, 0.0);
    for (int i = 0; i < 5; ++i)
    {
        blurredColor += g_Texture.Sample(g_SamplerState, In.TexCoord + bloomIntensity * blurOffsets[i]);
    }
    blurredColor /= power;

    outDiffuse = color + blurredColor;
}