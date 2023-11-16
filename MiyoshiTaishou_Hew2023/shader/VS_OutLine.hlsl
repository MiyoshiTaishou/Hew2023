#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{
	// ローカル座標をスクリーン座標へ変換
    Out.Position = In.Position; // ローカル座標
    
     //輪郭線として表示するために、法線方向へ頂点を移動
    Out.Position.xyz += normalize(In.Normal) * 0.03f;
    
    Out.Position = mul(Out.Position, World); // ワールド座標
    Out.Position = mul(Out.Position, View); // ビュー座標
    Out.Position = mul(Out.Position, Projection); // プロジェクション座標

	// ピクセルシェーダーで利用するUV座標を渡す
    Out.TexCoord = In.TexCoord;

	// ピクセルシェーダーで利用する法線を渡す
	// 法線はオブジェクトの回転に併せて回転させないとおかしな見た目になる。
	// ワールド行列には移動成分も含まれるが、移動を法線に適用してもおかしく
	// なるので、回転成分のみの行列となるように縮小して計算する。
    Out.Normal.xyz = mul(In.Normal.xyz, (float3x3) World);
}