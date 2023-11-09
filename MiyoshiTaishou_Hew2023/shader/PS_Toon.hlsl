#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
    
    float3 N = normalize(In.Normal.xyz);
    float3 L = normalize(Light.Direction.xyz);
    L = -L;
    
    float diffuse = saturate(dot(N, L));
    
     //diffueの値を階調化(0~1->0,0.5,1.0)
    diffuse *= 2.0f; //一度数値の範囲を広げる
        //切り捨ての関係上,2になるのは1の時だけ(0.9 * 2 = 1.8,切り捨ては1となる)
    diffuse += 0.5f;
        //小数を切り捨てた値を取得
    diffuse = floor(diffuse);
        //広げた範囲と同等の数値で割る
    diffuse /= 2.0f;
    
      //テクスチャの色を考慮して影をつける
    float4 texColor = g_Texture.Sample(g_SamplerState, In.TexCoord);
    color.rgb = texColor.rgb * (diffuse + Light.Ambient.rgb);
    
    outDiffuse = color;
}