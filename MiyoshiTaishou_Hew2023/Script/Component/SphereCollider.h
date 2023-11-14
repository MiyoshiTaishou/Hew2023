#pragma once
#include"Collider.h"

class SphereCollider : public Collider
{
public:

	bool Hit(const SphereCollider* _sphereCol);

	void SetRadius(float _radius);

private:

	using Collider::Collider;	

	float m_Radius;//”¼Œa
};
