#pragma once
#include"gameObject.h"

//�v���C���[�̑���Ŏ��_���ړ��ł���J����
class DebugCamera : public GameObject
{
private:

	DirectX::SimpleMath::Vector3	m_Target{};
	DirectX::SimpleMath::Matrix		m_ViewMatrix{};

	DirectX::SimpleMath::Vector3 m_Foward{};

public:
	void Init();	
	void Update();
	void Draw();

	void SetTarget(DirectX::SimpleMath::Vector3 target);

	DirectX::SimpleMath::Matrix GetViewMatrix()
	{
		return m_ViewMatrix;
	}
};

