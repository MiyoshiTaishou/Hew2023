#pragma once
#include"gameObject.h"

//プレイヤーの操作で視点を移動できるカメラ
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

