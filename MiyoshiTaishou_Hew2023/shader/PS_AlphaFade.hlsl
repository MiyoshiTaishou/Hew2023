
#include "common.hlsl"


Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


cbuffer TimeBuffer : register(b10)
{
    float4 timeData; // ���ԃf�[�^��ێ����邽�߂̃o�b�t�@
}

// ���̒��� timeData ���g���Čo�ߎ��ԂɊ�Â����������s��
void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    // �o�ߎ��Ԃɉ��������ߏ����Ȃǂ��s��
    if (Material.TextureEnable)
    {
        outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);

        // ���Ԍo�߂ɉ����ē��ߓx������������
        float fadeAmount = 0.5f * timeData.x; // timeData.x �Ɍo�ߎ��Ԃ��i�[����Ă���Ɖ���
        outDiffuse.a -= fadeAmount;
        
        // �A���t�@�l��0�����ɂȂ�Ȃ��悤�ɐ�������
        outDiffuse.a = max(outDiffuse.a, 0.0f);
    }
    else
    {
        outDiffuse = In.Diffuse;
    }
}
