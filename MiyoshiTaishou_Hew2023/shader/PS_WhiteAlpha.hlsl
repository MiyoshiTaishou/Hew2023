#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureDepth : register(t1);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float2 texCoord = In.TexCoord;
    
    texCoord.xy /= In.Position.w;
    texCoord.x = 0.5 * (texCoord.x + 1.0f);
    texCoord.y = -0.5 * (texCoord.y - 1.0f);
    float vz = In.Position.z / In.Position.w;
    float z = g_TextureDepth.Sample(g_SamplerState, texCoord.xy);
    float d = abs(vz - z);
    float threshold = 0.00075;
    if (d < threshold)
    {
        d = d / threshold;
    }
    else
    {
        d = 1.0f;
    }
    
    float4 color = g_Texture.Sample(g_SamplerState, In.TexCoord);
    
    color.a *= d;
    
    outDiffuse = color;
}
