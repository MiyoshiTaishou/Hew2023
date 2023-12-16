
#include "common.hlsl"


Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


cbuffer TimeBuffer : register(b10)
{
    float4 timeData; // 時間データを保持するためのバッファ
}

// この中で timeData を使って経過時間に基づいた処理を行う
void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    // 経過時間に応じた透過処理などを行う
    if (Material.TextureEnable)
    {
        outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);

        // 時間経過に応じて透過度を減少させる
        float fadeAmount = 0.5f * timeData.x; // timeData.x に経過時間が格納されていると仮定
        outDiffuse.a -= fadeAmount;
        
        // アルファ値が0未満にならないように制限する
        outDiffuse.a = max(outDiffuse.a, 0.0f);
    }
    else
    {
        outDiffuse = In.Diffuse;
    }
}
