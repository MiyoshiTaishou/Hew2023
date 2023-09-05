#include "Gravity.h"
#include"gameObject.h"

using namespace DirectX::SimpleMath;

void Gravity::Update()
{

	//���W��3�ȉ��Ȃ珈�������Ȃ�
	if (m_GameObject->GetPosition().y < 3.0f)
	{
		time = 0;
		return;
	}

	Vector3 vec = m_GameObject->GetPosition();

	//�d�͌v�Z
	vec.y -= (gravityPower.y * ((accGravity * (time*time)) / 2));	

	m_GameObject->SetPosition(vec);

	time++;
}
