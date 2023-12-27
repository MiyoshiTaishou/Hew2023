#pragma once
#include"Collider.h"

class Sprite;
class SphereCollider;

// BOX’è‹`
struct AABB {
	DirectX::SimpleMath::Vector3	min;
	DirectX::SimpleMath::Vector3	max;
};

struct OBBInfo
{
	DirectX::SimpleMath::Vector3	vecAxisX;// X²
	DirectX::SimpleMath::Vector3	vecAxisY;// Y²
	DirectX::SimpleMath::Vector3	vecAxisZ;// Z²
	DirectX::SimpleMath::Vector3	center;// ’†SÀ•Wiƒ[ƒJƒ‹À•WŒnj
	DirectX::SimpleMath::Vector3	currentcenter;// BBOX‚ÌŒ»İˆÊ’u
	float	fLengthX;// ‚a‚a‚n‚w ‚wƒTƒCƒY
	float	fLengthY;// ‚a‚a‚n‚w ‚xƒTƒCƒY
	float	fLengthZ;// ‚a‚a‚n‚w ‚yƒTƒCƒY
};

class BoxCollider : public Collider
{
public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool HitBox(const BoxCollider* _boxCol);
	bool HitSphere(SphereCollider* _sphereCol);

	bool Collision(BoxCollider& _box);

	bool CompareLength(
		const OBBInfo& pboxB,
		const DirectX::SimpleMath::Vector3& pvecSeparate,// •ª—£²
		const DirectX::SimpleMath::Vector3& pvecDistance);

	//“_‚Æ‚Ì“–‚½‚è”»’è
	bool PointHit(const DirectX::SimpleMath::Vector3 point);

private:
	using Collider::Collider;	

	OBBInfo m_Info;
};