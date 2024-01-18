#pragma once
#include"Collider.h"

class Sprite;
class SphereCollider;

// BOX定義
struct AABB {
	DirectX::SimpleMath::Vector3	min;
	DirectX::SimpleMath::Vector3	max;
};

struct OBBInfo
{
	DirectX::SimpleMath::Vector3	vecAxisX;// X軸
	DirectX::SimpleMath::Vector3	vecAxisY;// Y軸
	DirectX::SimpleMath::Vector3	vecAxisZ;// Z軸
	DirectX::SimpleMath::Vector3	center;// 中心座標（ローカル座標系）
	DirectX::SimpleMath::Vector3	currentcenter;// BBOXの現在位置
	float	fLengthX;// ＢＢＯＸ Ｘサイズ
	float	fLengthY;// ＢＢＯＸ Ｙサイズ
	float	fLengthZ;// ＢＢＯＸ Ｚサイズ
};

class BoxCollider : public Collider
{
public:

	void Init();
	void Update();
	void Draw();

	//ボックス同士
	bool HitBox(const BoxCollider* _boxCol);

	//ボックスとスフィア
	bool HitSphere(SphereCollider* _sphereCol);

	bool Collision(BoxCollider& _box);

	bool CompareLength(
		const OBBInfo& pboxB,
		const DirectX::SimpleMath::Vector3& pvecSeparate,// 分離軸
		const DirectX::SimpleMath::Vector3& pvecDistance);

	//点との当たり判定
	bool PointHit(const DirectX::SimpleMath::Vector3 point);

private:
	using Collider::Collider;	

	OBBInfo m_Info;
};