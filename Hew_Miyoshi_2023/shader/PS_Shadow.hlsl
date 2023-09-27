#include "common.hlsl"

Texture2D tex : register(t0); //通常テクスチャ
Texture2D DepthMap : register(t1);

SamplerState DepthSampler : register(s0);

void main(in PS_IN_SHADOW In, out float4 outDiffuse : SV_Target)
{
    float4 color = tex.Sample(DepthSampler, In.TexCoord);
    
    float2 depthUV = In.shadowPos.xy / In.shadowPos.w; //影で使うUVを計算
    float pixelDepth = In.shadowPos.z / In.shadowPos.w; //深度値を取得
    
    //UV座標を-1から1の範囲から0から1の範囲に変換しY座標の向きを反転
    depthUV = max(-1.0, min(1.0, depthUV)) * 0.5f + 0.5f;
    //depthUV = depthUV * 0.5f + 0.5f;
    depthUV.y = -depthUV.y;
    
    //深度テクスチャから深度の値を取得
    float depth = DepthMap.Sample(DepthSampler, depthUV);
    
    //取得した深度値から影の補正を行う
    color.rgb *= saturate(step(pixelDepth, depth) + 0.3f);
    
    outDiffuse = color;
}