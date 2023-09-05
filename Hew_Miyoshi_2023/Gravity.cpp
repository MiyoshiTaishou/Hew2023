#include "Gravity.h"
#include"gameObject.h"

using namespace DirectX::SimpleMath;

void Gravity::Update()
{

	//À•W‚ª3ˆÈ‰º‚È‚çˆ—‚ð‚µ‚È‚¢
	if (m_GameObject->GetPosition().y < 3.0f)
	{
		time = 0;
		return;
	}

	Vector3 vec = m_GameObject->GetPosition();

	//d—ÍŒvŽZ
	vec.y -= (gravityPower.y * ((accGravity * (time*time)) / 2));	

	m_GameObject->SetPosition(vec);

	time++;
}
