#pragma once
#include	<d3d11.h>
#include	<SimpleMath.h>
#include	"gameObject.h"


//�O���錾
class CPlane;
class Collider;

//�X�e�[�W�̃t�B�[���h
class Field : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	//std::vector<CPlane> m_Planes;

	//�����蔻��R���|�[�l���g
	Collider* m_Collider;

public:
	void Init();
	void Uninit();	
	void Draw();

	void makepalenequatation();

	// ���݈ʒu�̍��������߂�
	float  GetFieldHeight(DirectX::SimpleMath::Vector3 pos);
};