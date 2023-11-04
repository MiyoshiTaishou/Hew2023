#include "common.hlsl"

//��������̎��_�̕ϊ��s��
cbuffer LightMat : register(b11)
{
    float4x4 Lview; //��������̃r���[�ϊ��s��
    float4x4 Lproj; //��������̃v���W�F�N�V�����ϊ��s��
}

void main(in VS_IN In, out PS_IN_SHADOW Out)
{
     //���_�ʒu�̃��[���h�ϊ�
    Out.Position = float4(In.Position.xyz, 1.0f);
    Out.Position = mul(Out.Position, World);
    
    //�e�̌v�Z�p�Ɉʒu���R�s�[
    Out.shadowPos = Out.Position;
    
    //���_�ʒu�̃r���[�ϊ��ƃv���W�F�N�V�����ϊ�
    Out.Position = mul(Out.Position, View);
    Out.Position = mul(Out.Position, Projection);
    
    //�e����������̎��_�Ńr���[�ϊ��ƃv���W�F�N�V�����ϊ�
    Out.shadowPos = mul(Out.shadowPos, Lview);
    Out.shadowPos = mul(Out.shadowPos, Lproj);
    
    //�@���̃��[���h�ϊ�
    Out.Normal = mul(In.Normal.xyz, (float3x3) World);
    
    //UV�����̂܂܏o��
    Out.TexCoord = In.TexCoord;
}