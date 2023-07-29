#include "common.hlsl"

//定数バッファの定義
cbuffer Polar : register(b6)
{
    float alpha;
    float3 dummy;
}

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    // 画面の中心座標を取得
    float2 center = float2(0.5, 0.5);

    // ピクセルの位置座標を取得
    float2 pixelPos = In.TexCoord;

    // 中心からの距離を計算
    float distance = length(pixelPos - center);

    // 集中線の幅を設定（画面全体に広がるように調整）
    float lineWidth = 1.0;

    // 集中線の色を中心からの距離に応じて変化させる
    float4 lineColor = float4(distance / lineWidth, distance / lineWidth, distance / lineWidth, alpha); // 赤色

    // 集中線の描画範囲内であれば集中線の色を返し、それ以外は透明にする
    // 集中線の描画範囲内を中心からの距離で判定します
    float lineRange = lineWidth;

    if (distance <= lineRange)
    {
        outDiffuse = lineColor;
    }
    else
    {
        outDiffuse = float4(0.0, 0.0, 0.0, 0.0); // 透明色
    }
}
