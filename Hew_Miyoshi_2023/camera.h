#pragma once

#include	<SimpleMath.h>
#include	"gameObject.h"

//�J�����I�u�W�F�N�g�R���|�[�l���g�Ő؂�ւ����悤�ɂȂ��Ă���
class Camera : public GameObject
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
