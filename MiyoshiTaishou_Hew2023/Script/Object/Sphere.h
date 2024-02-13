#pragma once
#include"gameObject.h"

class CMeshRenderer;
class CSphereMesh;

class Sphere : public GameObject
{
public:

	void Init();
	void Draw();

private:	

	//“_‚Ì•`‰æ‚Ég—p‚·‚é•Ï”
	CMeshRenderer* m_MeshRenderer;
	CSphereMesh* m_Sphere;
};
