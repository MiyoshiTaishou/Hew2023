#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{    
    Out.Position = float4(In.Position.xyz, 1.0f);
    Out.Position = mul(Out.Position, World);
    Out.Position = mul(Out.Position, View);
    Out.Position = mul(Out.Position, Projection);

    Out.TexCoord = In.TexCoord;

    float3 N = normalize(mul(In.Normal.xyz, (float3x3) World));
    float3 L = normalize(-Light.Direction.xyz);

    float diffuse = saturate(dot(N, L));
    Out.Diffuse = diffuse * Light.Diffuse + Light.Ambient;    
}