#include "CarObject.h"

//ƒRƒ“ƒ|[ƒlƒ“ƒg
#include"../Component/shader.h"
#include"../Component/RootChaise.h"
#include"../Render/modelRenderer.h"
#include"../Component/SphereCollider.h"
#include"../Component/BoxCollider.h"
#include"../Component/RigidBody.h"
#include"../Component/audio.h"
#include"../Component/RootChaise.h"

#include"../Object/Player.h"

#include"../Sysytem/manager.h"
#include"../Scene/scene.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void CarObject::Init()
{
	this->AddComponent<ModelRenderer>()->Load("../asset\\model\\Car.obj");
	this->AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\vertexLightingPS.cso");
	m_Collider = this->AddComponent<BoxCollider>();
	m_Collider->SetCollScale(Vector3(10,10,10));
	this->SetScale(Vector3(3, 3, 3));
	this->SetPosition(Vector3(-50, 0, 0));
	this->AddComponent<RootChaise>();

	//SE
	m_SE = AddComponent<Audio>();
	m_SE->Load("../asset\\audio\\‚ ‚Á‚Ï‚ê.wav");
}

void CarObject::Update()
{
	Scene* scene = Manager::GetScene();

	Player* player = scene->GetGameObject<Player>();

	if (!player)
	{
		return;
	}

	//“–‚½‚Á‚½‚ç’e‚«”ò‚Î‚·
	if (this->m_Collider->HitSphere(player->GetComponent<SphereCollider>()))
	{
		// ˆÚ“®•ûŒü‚ðŒvŽZ‚·‚é
		Vector3 collisionDirection = m_Position - player->GetPosition();

		Vector3 playerPos = player->GetPosition();

		//‚Ç‚¿‚ç‚Ì•ûŒü‚©‚ç“–‚½‚Á‚Ä‚¢‚é‚©”»’f‚·‚é
		if (std::abs(collisionDirection.x) > std::abs(collisionDirection.z))
		{
			if (collisionDirection.x > 0)
			{
				playerPos.x = m_Collider->GetPos().x - m_Collider->GetCollScale().x / 1.4;
			}
			else if (collisionDirection.x < 0)
			{
				playerPos.x = m_Collider->GetPos().x + m_Collider->GetCollScale().x / 1.4;
			}
		}
		else
		{
			if (collisionDirection.z > 0)
			{
				playerPos.z = m_Collider->GetPos().z - m_Collider->GetCollScale().z / 1.4;
			}
			else if (collisionDirection.z < 0)
			{
				playerPos.z = m_Collider->GetPos().z + m_Collider->GetCollScale().z / 1.4;
			}
		}

		player->SetPosition(playerPos);
		player->GetComponent<RigidBody>()->SetVelocity(Vector3::Zero);
	}
}
