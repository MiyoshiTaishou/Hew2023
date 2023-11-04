#include "common.hlsl"

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    // 画面の中心座標を取得
    float2 center = float2(0.5, 0.5);

    // ピクセルの位置座標を取得
    float2 pixelPos = In.TexCoord;

    // 中心からの距離を計算
    float distance = length(pixelPos - center);

    // 円の半径を設定（画面全体に広がるように調整）
    float circleRadius = 0.5;

    // 円の描画範囲内であれば円の色を返し、それ以外は透明にする
    // 円の描画範囲内を中心からの距離で判定します
    if (distance <= circleRadius)
    {
        outDiffuse = float4(0.0f, 0.0f, 0.0f, 1.0f); // 円の色（白）
    }
    else
    {
        outDiffuse = float4(0.0, 0.0, 0.0, 0.0); // 透明色
    }
}
