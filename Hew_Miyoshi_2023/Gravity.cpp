#include "Gravity.h"
#include"gameObject.h"

using namespace DirectX::SimpleMath;

void Gravity::Update()
{

	//座標が3以下なら処理をしない
	//現在地面に設定している部分とプレイヤーのサイズからこうなっている
	if (m_GameObject->GetPosition().y < 3.0f)
	{
		time = 0;
		return;
	}

	Vector3 vec = m_GameObject->GetPosition();

	//重力計算
	vec.y -= (gravityPower.y * ((accGravity * (time*time)) / 2));	

	m_GameObject->SetPosition(vec);

	time++;
}
