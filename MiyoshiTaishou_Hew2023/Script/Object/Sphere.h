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

	//�_�̕`��Ɏg�p����ϐ�
	CMeshRenderer* m_MeshRenderer;
	CSphereMesh* m_Sphere;
};
