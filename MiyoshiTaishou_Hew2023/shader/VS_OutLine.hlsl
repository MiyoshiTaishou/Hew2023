#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{
	// ���[�J�����W���X�N���[�����W�֕ϊ�
    Out.Position = In.Position; // ���[�J�����W
    
     //�֊s���Ƃ��ĕ\�����邽�߂ɁA�@�������֒��_���ړ�
    Out.Position.xyz += normalize(In.Normal) * 0.03f;
    
    Out.Position = mul(Out.Position, World); // ���[���h���W
    Out.Position = mul(Out.Position, View); // �r���[���W
    Out.Position = mul(Out.Position, Projection); // �v���W�F�N�V�������W

	// �s�N�Z���V�F�[�_�[�ŗ��p����UV���W��n��
    Out.TexCoord = In.TexCoord;

	// �s�N�Z���V�F�[�_�[�ŗ��p����@����n��
	// �@���̓I�u�W�F�N�g�̉�]�ɕ����ĉ�]�����Ȃ��Ƃ������Ȍ����ڂɂȂ�B
	// ���[���h�s��ɂ͈ړ��������܂܂�邪�A�ړ���@���ɓK�p���Ă���������
	// �Ȃ�̂ŁA��]�����݂̂̍s��ƂȂ�悤�ɏk�����Čv�Z����B
    Out.Normal.xyz = mul(In.Normal.xyz, (float3x3) World);
}