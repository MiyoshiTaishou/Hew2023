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
        float fadeAmount = saturate(In.TexCoord.y - timeData.x); // UV座標のy値を使用
        
        outDiffuse.a *= fadeAmount;
    }
    else
    {
        outDiffuse = In.Diffuse;
    }
}
