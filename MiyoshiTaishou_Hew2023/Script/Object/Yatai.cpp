#include "Yatai.h"

//コンポーネント
#include"../Component/shader.h"
#include"../Component/RootChaise.h"
#include"../Render/modelRenderer.h"
#include"../Component/SphereCollider.h"
#include"../Component/RigidBody.h"

#include"../Object/Player.h"

#include"../Sysytem/manager.h"
#include"../Scene/scene.h"

using namespace DirectX::SimpleMath;

void Yatai::Init()
{
	this->AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\vertexLightingPS.cso");
	this->AddComponent<ModelRenderer>()->Load("../asset\\model\\Yatai.obj");
	SphereCollider* sphere = AddComponent<SphereCollider>();
	sphere->SetRadius(8.0f);
	this->SetScale(Vector3(10, 10, 10) * 0.002);
	this->AddComponent<RootChaise>();
	this->SetRotation(Vector3(0, 90, 0));
}

void Yatai::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	if (GetComponent<SphereCollider>()->Hit(player->GetComponent<SphereCollider>()))
	{
		player->GetComponent<RigidBody>()->AddForce(Vector3(0, 50, 0), ForceMode::Impulse);
	}
}
