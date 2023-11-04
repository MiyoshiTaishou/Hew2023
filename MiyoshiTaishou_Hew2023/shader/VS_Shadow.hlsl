#include "common.hlsl"

//光源からの視点の変換行列
cbuffer LightMat : register(b11)
{
    float4x4 Lview; //光源からのビュー変換行列
    float4x4 Lproj; //光源からのプロジェクション変換行列
}

void main(in VS_IN In, out PS_IN_SHADOW Out)
{
     //頂点位置のワールド変換
    Out.Position = float4(In.Position.xyz, 1.0f);
    Out.Position = mul(Out.Position, World);
    
    //影の計算用に位置をコピー
    Out.shadowPos = Out.Position;
    
    //頂点位置のビュー変換とプロジェクション変換
    Out.Position = mul(Out.Position, View);
    Out.Position = mul(Out.Position, Projection);
    
    //影を光源からの視点でビュー変換とプロジェクション変換
    Out.shadowPos = mul(Out.shadowPos, Lview);
    Out.shadowPos = mul(Out.shadowPos, Lproj);
    
    //法線のワールド変換
    Out.Normal = mul(In.Normal.xyz, (float3x3) World);
    
    //UVをそのまま出力
    Out.TexCoord = In.TexCoord;
}