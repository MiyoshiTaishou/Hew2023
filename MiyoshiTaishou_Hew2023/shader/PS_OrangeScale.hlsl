#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float4 texColor = g_Texture.Sample(g_SamplerState, In.TexCoord);

    // �I�����W�F�̃e�B���g�������邽�߂�R��G�̒l�����߂ɂ���B�̒l�͕ς��Ȃ�
    float3 orangeTint = float3(1.5f, 1.2f, 1.0f);
    texColor.rgb *= orangeTint;

    outDiffuse = texColor;
}
