#pragma once
#include"component.h"
#include"../Mesh/CMeshRenderer.h"
#include"../Mesh/CSphereMesh.h"

#define MAX_BEJIE 7

//�x�W�G�Ȑ���p���Ĉړ������邽�߂̃R���|�[�l���g
class RootChaise : public Component
{
public:

	void Init();
	void Uninit();
	void Draw();
	void Update();

private:

	float m_Rate = 0.0f;
	float m_MoveSpeed = 0.01f;

	//�����p�̃��b�V��
	CMeshRenderer* m_MeshRenderer[MAX_BEJIE];
	CSphereMesh* m_Sphere[MAX_BEJIE];

	DirectX::SimpleMath::Vector3 m_SpherePos[MAX_BEJIE];

	using Component::Component;
};
