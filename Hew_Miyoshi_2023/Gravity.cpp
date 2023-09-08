#include "Gravity.h"
#include"gameObject.h"

using namespace DirectX::SimpleMath;

/**
 * @fn
 * �d�͂̌v�Z
 * @detail �I�u�W�F�N�g�̍��W��3.0f�ȉ��Ȃ珈�������Ȃ�
 */
void Gravity::Update()
{
	if (m_GameObject->GetPosition().y < 3.0f)
	{
		time = 0;
		return;
	}

	Vector3 vec = m_GameObject->GetPosition();

	vec.y -= (gravityPower.y * ((accGravity * (time*time)) / 2));

	//vec.y *= accGravity;

	m_GameObject->SetPosition(vec);

	time++;
}
