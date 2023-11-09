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
    
     //diffue�̒l���K����(0~1->0,0.5,1.0)
    diffuse *= 2.0f; //��x���l�͈̔͂��L����
        //�؂�̂Ă̊֌W��,2�ɂȂ�̂�1�̎�����(0.9 * 2 = 1.8,�؂�̂Ă�1�ƂȂ�)
    diffuse += 0.5f;
        //������؂�̂Ă��l���擾
    diffuse = floor(diffuse);
        //�L�����͈͂Ɠ����̐��l�Ŋ���
    diffuse /= 2.0f;
    
      //�e�N�X�`���̐F���l�����ĉe������
    float4 texColor = g_Texture.Sample(g_SamplerState, In.TexCoord);
    color.rgb = texColor.rgb * (diffuse + Light.Ambient.rgb);
    
    outDiffuse = color;
}