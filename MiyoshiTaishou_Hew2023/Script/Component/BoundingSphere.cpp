#define NOMINMAX

#include"BoundingSphere.h"
#include"../Render/modelRenderer.h"

using namespace DirectX::SimpleMath;

// ワールド座標を計算する（対象オブジェクトの行列（RTS）が入った）
Vector3 BoundingSphere::CalcWorldPos(DirectX::SimpleMath::Matrix mtx) 
{
	return Vector3::Transform(m_center, mtx);
}

// BS情報を生成する
void BoundingSphere::Caliculate() 
{

	std::vector<float > lengthlist;

	Vector3 max;
	Vector3 min;

	// 最大値と最小値を求める	
	m_min = ModelRenderer::Min;
	m_max = ModelRenderer::Max;
	
	// 中心を求める
	m_center = (max + min) * 0.5f;

	float iter = (max - m_center).Length();

	m_radius = iter;
}

// 半径を戻す
float BoundingSphere::GetRadius()
{
	return m_radius;	
}

// 中心座標を戻す
Vector3 BoundingSphere::GetCenter()
{
	return m_center;
}

// BS情報生成
BoundingSphere BoundingSphere::MakeBS(
	Matrix mtx,			// オブジェクトの行列（RTS情報）
	Vector3 scale)			// オブジェクトのスケール値
{

	BoundingSphere bs;

	// 中心座標計算
	Vector3 wpos = CalcWorldPos(mtx);
	bs.m_center = wpos;

	// 半径の再計算（拡縮がある為）
	float maxsclae = std::max(std::max(scale.x, scale.y), scale.z);
	bs.m_radius = m_radius * maxsclae;

	return bs;
}

// BS描画用のワールド変換行列を生成する
Matrix BoundingSphere::MakeWorldMtx(
	Vector3 scale,
	Matrix wmtx) 
{

	// 単純に３Ｄジオメトリ情報からＢＳ情報を作成してる
	//（拡縮が考慮されていない）
	float smax;
	smax = std::max(std::max(scale.x, scale.y), scale.z);

	// 最大の拡大率で行列生成
	Matrix mtx = Matrix::CreateScale(smax, smax, smax);
	Vector3 bspos = CalcWorldPos(wmtx);

	// バウンディングスフィア用のワールド変換行列にする（中心がずれてるので修正）
	mtx._41 = bspos.x;
	mtx._42 = bspos.y;
	mtx._43 = bspos.z;

	return mtx;
}

// 最大値取得
Vector3 BoundingSphere::GetMax() {
	return m_max;
}

// 最小値取得
Vector3 BoundingSphere::GetMin() {
	return m_min;
}
