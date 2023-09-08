#include "JumpComponent.h"
#include"gameObject.h"
#include"input.h"
#include"ImGuiManager.h"

using namespace DirectX::SimpleMath;

/**
 * @fn
 * �W�����v�̏���
 * @brief ���������グ�̌v�Z�ŏ�ɂ����Ă���
 */
void JumpComponent::Update()
{
	Vector3 vec = m_GameObject->GetPosition();		

	float y = jumpPower;

	if (Input::GetKeyPress(' ') && jumpCheck)
		jumpCheck = false;

	//!�W�����v�̌v�Z�i���������グ�j	

	vec.y = ((y * time) - ((accGravity * (time * time)) / 2) + 2.0f);

	//!���Ԍv��
	if (!jumpCheck)
		time += 1.0f / 60.0f;
	
	m_GameObject->SetPosition(vec);

	if (m_GameObject->GetPosition().y >= 2.0f)
		return;
	
	jumpCheck = true;
	time = 0;
}

void JumpComponent::Draw()
{
	ImGui::Begin("Jump");

	ImGui::Text("%d", time);

	ImGui::End();
}

