#include "JumpComponent.h"
#include"gameObject.h"
#include"input.h"
#include"ImGuiManager.h"

using namespace DirectX::SimpleMath;

/**
 * @fn
 * ジャンプの処理
 * @brief 鉛直投げ上げの計算で上にあげている
 */
void JumpComponent::Update()
{
	Vector3 vec = m_GameObject->GetPosition();		

	float y = jumpPower;

	if (Input::GetKeyPress(' ') && jumpCheck)
		jumpCheck = false;

	//!ジャンプの計算（鉛直投げ上げ）	

	vec.y = ((y * time) - ((accGravity * (time * time)) / 2) + 2.0f);

	//!時間計測
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

