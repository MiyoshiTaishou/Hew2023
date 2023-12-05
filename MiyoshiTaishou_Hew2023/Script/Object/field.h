#pragma once
#include	<d3d11.h>
#include	<SimpleMath.h>
#include	"gameObject.h"
#include	"../Mesh/CUndulationPlaneMesh.h"
#include	"../Mesh/CMeshRenderer.h"
#include	"../Mesh/CPlane.h"

//�O���錾
class CPlane;
class Collider;

//�X�e�[�W�̃t�B�[���h
class Field : public GameObject
{
private:
	CMeshRenderer		m_renderer;						// �t�B�[���h�̃����_��

	ID3D11ShaderResourceView* m_Texture{};

	// ���ʃv���[��
	CUndulationPlaneMesh	m_planemesh;				// ���ʃ��b�V��

	std::vector<CPlane> m_planes;						// ���ʂ̕������Q

	// ���ʂ̕������𐶐�����i�S�ʁj
	void MakeEquatation();

	Collider* m_Collider;

	float dis = 0.0f;

public:
	void Init();
	void Uninit();	
	void Draw();

	// ���݈ʒu�̍��������߂�
	float  GetFieldHeight(DirectX::SimpleMath::Vector3 pos);
	//_offRigidBody�̉e����^���邩�ǂ���
	float GetFieldHeightBySqno(DirectX::SimpleMath::Vector3 pos, GameObject& obj);

	void PointPlaneCollision(DirectX::SimpleMath::Vector3 _point);

	// �@���x�N�g������΂߂̕������v�Z
	DirectX::SimpleMath::Vector3 CalculateDiagonalDirection(DirectX::SimpleMath::Vector3 normal);

	DirectX::SimpleMath::Vector3 direction;
	DirectX::SimpleMath::Vector3 normalDB;	

	// GetMAX XZ
	DirectX::SimpleMath::Vector3 GetMax() {

		DirectX::SimpleMath::Vector3 max;

		max.x = m_planemesh.GetWidth() / 2.0f;
		max.z = m_planemesh.GetHeight() / 2.0f;
		max.y = 0.0f;

		return max;
	}

	// GetMIN XZ
	DirectX::SimpleMath::Vector3 GetMin() {
		DirectX::SimpleMath::Vector3 min;

		min.x = -m_planemesh.GetWidth() / 2.0f;
		min.z = -m_planemesh.GetHeight() / 2.0f;
		min.y = 0.0f;

		return min;
	}
};