#include "common.hlsl"

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);
    
    //�s�N�Z����z�ʒu��RGB��R�v�f�Ƃ��Ă�ۑ�����
    color.r = In.Position.z;
    
    outDiffuse = color;
}