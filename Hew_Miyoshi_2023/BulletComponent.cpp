#include "BulletComponent.h"
#include"gameObject.h"
#include"ImGuiManager.h"

using namespace DirectX::SimpleMath;

void BulletComponent::Update()
{	
	if (!bShot)return;

	//Œü‚¢‚Ä‚½•ûŒü‚É‹…‚ð”ò‚Î‚·
	Vector3 vec3 = shotVec * (speed * time) + m_GameObject->GetPosition();	
	m_GameObject->SetPosition(vec3);

	time += 1.0f / 60.0f;
}

void BulletComponent::Shot(Vector3 vec,GameObject& obj,Vector3 pos)
{
	bShot = true;
	obj.SetPosition(pos);
	shotVec = vec;
	time = 0.0f;
}
