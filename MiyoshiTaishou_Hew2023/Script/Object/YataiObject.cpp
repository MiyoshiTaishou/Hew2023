#include "YataiObject.h"

//コンポーネント
#include"../Component/shader.h"
#include"../Component/RootChaise.h"
#include"../Render/modelRenderer.h"
#include"../Component/SphereCollider.h"
#include"../Component/RigidBody.h"

#include"../Object/Player.h"

#include"../Sysytem/manager.h"
#include"../Scene/scene.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void YataiObject::Init()
{
	this->AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\vertexLightingPS.cso");
	this->AddComponent<ModelRenderer>()->Load("../asset\\model\\Yatai2.obj");
	SphereCollider* sphere = AddComponent<SphereCollider>();
	sphere->SetRadius(8.0f);
	this->SetScale(Vector3(1, 1, 1) * 0.03f);	
	this->SetPosition(Vector3(50, 10, 10));	
	this->AddComponent<RootChaise>();
	this->SetRotation(Vector3(0, 90, 0));
}

void YataiObject::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	if (!player)
	{
		return;
	}

	if (GetComponent<SphereCollider>()->Hit(player->GetComponent<SphereCollider>()))
	{
		player->GetComponent<RigidBody>()->AddForce(Vector3(0, 50, 0), ForceMode::Impulse);
	}
}