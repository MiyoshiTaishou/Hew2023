#include "common.hlsl"

Texture2D tex : register(t0); //�ʏ�e�N�X�`��
Texture2D DepthMap : register(t1);

SamplerState DepthSampler : register(s0);

void main(in PS_IN_SHADOW In, out float4 outDiffuse : SV_Target)
{
    float4 color = tex.Sample(DepthSampler, In.TexCoord);
    
    float2 depthUV = In.shadowPos.xy / In.shadowPos.w; //�e�Ŏg��UV���v�Z
    float pixelDepth = In.shadowPos.z / In.shadowPos.w; //�[�x�l���擾
    
    //UV���W��-1����1�͈̔͂���0����1�͈̔͂ɕϊ���Y���W�̌����𔽓]
    depthUV = max(-1.0, min(1.0, depthUV)) * 0.5f + 0.5f;
    //depthUV = depthUV * 0.5f + 0.5f;
    depthUV.y = -depthUV.y;
    
    //�[�x�e�N�X�`������[�x�̒l���擾
    float depth = DepthMap.Sample(DepthSampler, depthUV);
    
    //�擾�����[�x�l����e�̕␳���s��
    color.rgb *= saturate(step(pixelDepth, depth) + 0.3f);
    
    outDiffuse = color;
}