#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

//RGBÇè≠ÇµÇ∏ÇÁÇ∑
void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
    color = g_Texture.Sample(g_SamplerState, In.TexCoord);
    
    color.r = g_Texture.Sample(g_SamplerState, In.TexCoord + 0.02f).r;
    color.g = g_Texture.Sample(g_SamplerState, In.TexCoord - 0.02f).g;

    outDiffuse = color;
}
