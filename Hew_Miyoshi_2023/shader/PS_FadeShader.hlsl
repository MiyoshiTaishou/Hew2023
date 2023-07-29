#include "common.hlsl"

//�萔�o�b�t�@�̒�`
cbuffer Polar : register(b6)
{
    float alpha;
    float3 dummy;
}

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    // ��ʂ̒��S���W���擾
    float2 center = float2(0.5, 0.5);

    // �s�N�Z���̈ʒu���W���擾
    float2 pixelPos = In.TexCoord;

    // ���S����̋������v�Z
    float distance = length(pixelPos - center);

    // �W�����̕���ݒ�i��ʑS�̂ɍL����悤�ɒ����j
    float lineWidth = 1.0;

    // �W�����̐F�𒆐S����̋����ɉ����ĕω�������
    float4 lineColor = float4(distance / lineWidth, distance / lineWidth, distance / lineWidth, alpha); // �ԐF

    // �W�����̕`��͈͓��ł���ΏW�����̐F��Ԃ��A����ȊO�͓����ɂ���
    // �W�����̕`��͈͓��𒆐S����̋����Ŕ��肵�܂�
    float lineRange = lineWidth;

    if (distance <= lineRange)
    {
        outDiffuse = lineColor;
    }
    else
    {
        outDiffuse = float4(0.0, 0.0, 0.0, 0.0); // �����F
    }
}
