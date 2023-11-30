#pragma once
#include"Collider.h"
#include"../Mesh/CMeshRenderer.h"
#include"../Mesh/CSphereMesh.h"

class SphereCollider : public Collider
{
public:

	void Init();
	void Uninit();
	void Draw();

	bool Hit(const SphereCollider* _sphereCol);

	void SetRadius(float _radius);

	bool m_Invisble = false;

private:

	using Collider::Collider;	

	float m_Radius;//”¼Œa	

	CMeshRenderer* m_MeshRenderer;
	CSphereMesh* m_Sphere;
	MATERIAL m_SphereMt;
};
