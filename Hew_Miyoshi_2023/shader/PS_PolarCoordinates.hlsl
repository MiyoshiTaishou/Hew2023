#include "common.hlsl"


//�΂̒�`
static const float pi = 3.1415926535f;

//�萔�o�b�t�@�̒�`
cbuffer Polar : register(b5)
{
    float gauge1; //�Q�[�W�̉����l
    float gauge2; //�Q�[�W�̏���l
    float inner; //�`�悷������̉~�̔��a
    float outer; //�`�悷��O���̉~�̔��a
    float4 baseColor; //�x�[�X�J���[
    float4 diffColor; //�Q�[�W��gauge1��gauge2�̊Ԃ̎��̐F
    float4 lostColor; //�Q�[�W��gauge2�𒴂����Ƃ��̐F
}

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f); //�����F�̐ݒ�i���j
    float2 uv = In.TexCoord - 0.5f; //uv���W�̒��S���ʒu
    float angle = atan2(uv.y, uv.x); //�ɍ��W�h�o�̊p�x���v�Z

	//�p�x����/2�������炷
    angle += pi / 2.0f;

	//�Q�[�W�̊p�x���v�Z�i0.0f~1.0f�j
	//frac�͏���������Ԃ�
    float gauge = frac(angle * -0.5f / pi);

	//�Q�[�W��gauge2�𒴂�����lostColor�����Z
	//step�͈�ڂ̈�������ڂ����傫���Ȃ�1����ȊO�Ȃ�0
    color.rgb += lostColor.rgb * step(gauge2, gauge);

	//�Q�[�W��guage1��gauge2�̊ԂȂ�diffColor�����Z
    color.rgb += diffColor.rgb * (1.0f - step(gauge2, gauge)) * step(gauge1, gauge);

	//�Q�[�W��gauge1�����Ȃ�baseColor�����Z
    color.rgb += baseColor.rgb * (1.0f - step(gauge1, gauge));
	
	//uv���W�̌��_����̋������v�Z(0.0~1.0)
	//length()�̓x�N�g���̒�����Ԃ������̎����ɍ��킹�Čv�Z����
    float dist = length(uv) / 0.5f;

	//�`�悷��͈�(inner~outer)�ȊO�ł͓����ɂ���
    color.a = (1 - step(outer, dist)) * step(inner, dist);


    outDiffuse = color;
}