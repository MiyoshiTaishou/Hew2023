#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

//�萔�o�b�t�@�̒�`
cbuffer Polar : register(b6)
{
    float maxDistance;
    float3 objectPos; //�e�̎�����̍��W
}


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    if (Material.TextureEnable)
    {
        outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
        outDiffuse *= In.Diffuse;
    }
    else
    {
        outDiffuse.xyz = In.Diffuse.xyz;
        outDiffuse = In.Diffuse;
        //outDiffuse.a = 1.0f;
    }
     // ���[���h���W��Ԃł̃J�����ʒu
    float3 cameraPosition = float3(0, 0, 0); // �J�����ʒu��ݒ�
    
    // ���_���W�����[���h���W��Ԃɕϊ�
    float3 worldPosition = mul(In.Position, World).xyz;
    
    // �J�������璸�_�܂ł̋������v�Z
    float distance = length(worldPosition - cameraPosition);
    
    // �����x�������Ɋ�Â��Čv�Z
    //float maxDistance = 10.0; // �����ɂȂ鋗���̐ݒ�
    float nowDistance = distance / maxDistance; // 0����1�͈̔͂ɐ��K��
    
    // �����x�����̐F�ƍ������邽�߂ɁA���̐F��ݒ�
    float4 originalColor = float4(0.8, 0.8, 0.8, 1.0); // ��: �ԐF�̌��̐F
    
    // �����x���l�����čŏI�I�ȐF���v�Z  
    outDiffuse.a = originalColor.a * (1.0 - nowDistance); // �����x��K�p 
    //outDiffuse.a = 0.0f;
}