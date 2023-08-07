#include "common.hlsl"

//�萔�o�b�t�@�̒�`
cbuffer Polar : register(b8)
{
    float2 rotationAngle;
}

void main(in VS_IN In, out PS_IN Out)
{
    Out.Position = float4(In.Position.xyz, 1.0f);
    Out.Position = mul(Out.Position, World);
    Out.Position = mul(Out.Position, View);
    Out.Position = mul(Out.Position, Projection);
    
   // ��]���S�����_(0, 0)�Ƃ��ĉ�]������
    float2 rotatedTexCoord = float2(
        In.TexCoord.x * cos(rotationAngle.x) - In.TexCoord.y * sin(rotationAngle.x),
        In.TexCoord.x * sin(rotationAngle.y) + In.TexCoord.y * cos(rotationAngle.y)
    );
    
    Out.TexCoord = rotatedTexCoord;
    
    float3 N = normalize(mul(In.Normal.xyz, (float3x3) World));
    float3 L = normalize(-Light.Direction.xyz);

    float diffuse = saturate(dot(N, L));
    
    Out.Diffuse = diffuse * Light.Diffuse + Light.Ambient;
}