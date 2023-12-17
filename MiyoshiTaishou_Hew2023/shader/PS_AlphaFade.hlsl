#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

cbuffer TimeBuffer : register(b10)
{
    float4 timeData; // ���ԃf�[�^��ێ����邽�߂̃o�b�t�@
}

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    if (Material.TextureEnable)
    {
        outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);

        // �摜�̍����ɉ����ē��ߓx��ω�������
        float fadeAmount = saturate((timeData.x - In.TexCoord.y) * 5); // �������ɏ��X�ɓ��߂��邽�߂ɏ搔�𒲐�
        
        outDiffuse.a *= fadeAmount;
    }
    else
    {
        outDiffuse = In.Diffuse;
    }
}
