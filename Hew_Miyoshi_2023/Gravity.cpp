#include "Gravity.h"
#include"gameObject.h"

using namespace DirectX::SimpleMath;

void Gravity::Update()
{

	//���W��3�ȉ��Ȃ珈�������Ȃ�
	//���ݒn�ʂɐݒ肵�Ă��镔���ƃv���C���[�̃T�C�Y���炱���Ȃ��Ă���
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
