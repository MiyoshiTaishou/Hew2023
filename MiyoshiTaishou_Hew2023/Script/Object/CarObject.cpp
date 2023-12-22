#include "CarObject.h"

//コンポーネント
#include"../Component/shader.h"
#include"../Component/RootChaise.h"
#include"../Render/modelRenderer.h"
#include"../Component/SphereCollider.h"
#include"../Component/RigidBody.h"
#include"../Component/audio.h"

#include"../Object/Player.h"

#include"../Sysytem/manager.h"
#include"../Scene/scene.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void CarObject::Init()
{
	this->AddComponent<ModelRenderer>()->Load("../asset\\model\\Car.obj");
	this->AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\vertexLightingPS.cso");
	m_Collider = this->AddComponent<SphereCollider>();
	m_Collider->SetRadius(15.0f);
	this->SetScale(Vector3(3, 3, 3));
	this->SetPosition(Vector3(-50, 0, 0));

	//SE
	m_SE = AddComponent<Audio>();
	m_SE->Load("../asset\\audio\\あっぱれ.wav");
}

void CarObject::Update()
{
	Scene* scene = Manager::GetScene();

	Player* player = scene->GetGameObject<Player>();

	if (!player)
	{
		return;
	}

	//当たったら弾き飛ばす
	if (this->m_Collider->Hit(player->GetComponent<SphereCollider>()))
	{
		RigidBody* body = player->GetComponent<RigidBody>();
		Vector3 playerVel = body->GetVelocity();

		playerVel *= -1.1;

		playerVel.y = 0.0f;

		body->AddForce(playerVel, ForceMode::Impulse);

		m_SE->Play();
	}
}
