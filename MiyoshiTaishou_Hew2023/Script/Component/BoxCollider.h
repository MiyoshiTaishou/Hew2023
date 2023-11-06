#pragma once
#include"Collider.h"

class Sprite;

// BOX��`
struct AABB {
	DirectX::SimpleMath::Vector3	min;
	DirectX::SimpleMath::Vector3	max;
};

struct OBBInfo
{
	DirectX::SimpleMath::Vector3	vecAxisX;// X��
	DirectX::SimpleMath::Vector3	vecAxisY;// Y��
	DirectX::SimpleMath::Vector3	vecAxisZ;// Z��
	DirectX::SimpleMath::Vector3	center;// ���S���W�i���[�J�����W�n�j
	DirectX::SimpleMath::Vector3	currentcenter;// BBOX�̌��݈ʒu
	float	fLengthX;// �a�a�n�w �w�T�C�Y
	float	fLengthY;// �a�a�n�w �x�T�C�Y
	float	fLengthZ;// �a�a�n�w �y�T�C�Y
};

class BoxCollider : public Collider
{
public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool Hit(const BoxCollider* _boxCol);

	bool Collision(BoxCollider& _box);

	bool CompareLength(
		const OBBInfo& pboxB,
		const DirectX::SimpleMath::Vector3& pvecSeparate,// ������
		const DirectX::SimpleMath::Vector3& pvecDistance);


private:
	using Collider::Collider;	

	OBBInfo m_Info;
};