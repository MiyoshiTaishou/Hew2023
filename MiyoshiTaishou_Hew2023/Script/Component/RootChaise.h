#pragma once
#include"component.h"
#include"../Mesh/CMeshRenderer.h"
#include"../Mesh/CSphereMesh.h"
#include"../Particle/Particle.h"

#define MAX_BEJIE 10

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
	float m_MoveSpeed = 0.005f;

	//�����p�̃��b�V��
	CMeshRenderer* m_MeshRenderer[MAX_BEJIE];
	CSphereMesh* m_Sphere[MAX_BEJIE];

	//�x�W�G�̍��W
	DirectX::SimpleMath::Vector3 m_SpherePos[MAX_BEJIE];

	//����������
	bool m_Goal = false;

	using Component::Component;
	
	//���O�ύX�p�ϐ�
	char m_buffer[256] = "../asset/map/YataiRoot.csv";
};
