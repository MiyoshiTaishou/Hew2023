#include "common.hlsl"

//定数バッファの定義
cbuffer ConstantBuffer : register(b9)
{
    float2 screenSize;
    float2 circlePosition;
    float circleRadius;
}

void main(in VS_IN In, out PS_IN Out)
{    
    float2 screenPosition = In.Position.xy * circleRadius + circlePosition;
    Out.Position = float4((screenPosition.x / (screenSize.x * 0.5f)) - 1.0f,
                             1.0f - (screenPosition.y / (screenSize.y * 0.5f)),
                             0.0f, 1.0f);
    
    Out.TexCoord = In.TexCoord;
    
    float3 N = normalize(mul(In.Normal.xyz, (float3x3) World));
    float3 L = normalize(-Light.Direction.xyz);

    float diffuse = saturate(dot(N, L));
    
    Out.Diffuse = diffuse * Light.Diffuse + Light.Ambient;
}