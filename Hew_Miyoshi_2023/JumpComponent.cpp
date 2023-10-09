#include "JumpComponent.h"
#include"gameObject.h"
#include"input.h"
#include"ImGuiManager.h"

using namespace DirectX::SimpleMath;

void JumpComponent::Update()
{
	Vector3 vec = m_GameObject->GetPosition();		

	float y = jumpPower;

	if (Input::GetKeyPress(' ') && jumpCheck)
		jumpCheck = false;

	//�W�����v�̌v�Z�i���������グ�j	

	vec.y = ((y * time) - ((accGravity * (time * time)) / 2) + 2.0f);

	//���Ԍv��
	if (!jumpCheck)
		time += 1.0f / 60.0f;
	
	m_GameObject->SetPosition(vec);

	//�n�ʂɕt������W�����v�ł���悤�ɂ���
	if (m_GameObject->GetPosition().y >= 2.0f)
		return;
	
	jumpCheck = true;
	time = 0;
	//vec.y = -1.0f;
	//obj.SetPosition(vec);
		
}

void JumpComponent::Draw()
{
	//���Ԍv���p
	ImGui::Begin("Jump");

	ImGui::Text("%d", time);

	ImGui::End();
}

