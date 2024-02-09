#pragma once
#include"Collider.h"

class SphereCollider2D : public Collider
{
public:
	
	//“ñ‚Â‚Ì‰~‚Ì‚ß‚è‚İ‚Ì‰ğÁ
	DirectX::SimpleMath::Vector3 Hit(const SphereCollider2D* _sphereCol);

	void SetRadius(float _radius) { m_Radius = _radius; }
	
private:

	using Collider::Collider;

	float m_Radius;//”¼Œa		
};
