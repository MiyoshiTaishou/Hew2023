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

	//ジャンプの計算（鉛直投げ上げ）	

	vec.y = ((y * time) - ((accGravity * (time * time)) / 2) + 2.0f);

	//時間計測
	if (!jumpCheck)
		time += 1.0f / 60.0f;
	
	m_GameObject->SetPosition(vec);

	//地面に付いたらジャンプできるようにする
	if (m_GameObject->GetPosition().y >= 2.0f)
		return;
	
	jumpCheck = true;
	time = 0;
	//vec.y = -1.0f;
	//obj.SetPosition(vec);
		
}

void JumpComponent::Draw()
{
	//時間計測用
	ImGui::Begin("Jump");

	ImGui::Text("%d", time);

	ImGui::End();
}

