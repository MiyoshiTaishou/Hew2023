#include "common.hlsl"

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);
    
    //ピクセルのz位置をRGBのR要素としてる保存する
    color.r = In.Position.z;
    
    outDiffuse = color;
}