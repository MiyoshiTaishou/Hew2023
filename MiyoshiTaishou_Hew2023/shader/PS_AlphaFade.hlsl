#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

cbuffer TimeBuffer : register(b10)
{
    float4 timeData; // 時間データを保持するためのバッファ
}

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    if (Material.TextureEnable)
    {
        outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);

        // 画像の高さに応じて透過度を変化させる
        float fadeAmount = saturate((timeData.x - In.TexCoord.y) * 5); // 下から上に徐々に透過するために乗数を調整
        
        outDiffuse.a *= fadeAmount;
    }
    else
    {
        outDiffuse = In.Diffuse;
    }
}
