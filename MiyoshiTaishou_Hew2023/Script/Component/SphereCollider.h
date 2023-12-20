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

	//“–‚½‚è”»’è‚ğ‰Â‹‰»
	//bool m_Invisble = false;
	bool m_Invisble = true;

private:

	using Collider::Collider;	

	float m_Radius;//”¼Œa	

	//‰Â‹‰»—p‚ÌƒƒbƒVƒ…
	CMeshRenderer* m_MeshRenderer;
	CSphereMesh* m_Sphere;
	MATERIAL m_SphereMt;
};
