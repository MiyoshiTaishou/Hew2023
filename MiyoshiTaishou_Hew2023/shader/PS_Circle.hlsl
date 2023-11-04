#include "common.hlsl"

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    // ��ʂ̒��S���W���擾
    float2 center = float2(0.5, 0.5);

    // �s�N�Z���̈ʒu���W���擾
    float2 pixelPos = In.TexCoord;

    // ���S����̋������v�Z
    float distance = length(pixelPos - center);

    // �~�̔��a��ݒ�i��ʑS�̂ɍL����悤�ɒ����j
    float circleRadius = 0.5;

    // �~�̕`��͈͓��ł���Ή~�̐F��Ԃ��A����ȊO�͓����ɂ���
    // �~�̕`��͈͓��𒆐S����̋����Ŕ��肵�܂�
    if (distance <= circleRadius)
    {
        outDiffuse = float4(0.0f, 0.0f, 0.0f, 1.0f); // �~�̐F�i���j
    }
    else
    {
        outDiffuse = float4(0.0, 0.0, 0.0, 0.0); // �����F
    }
}
