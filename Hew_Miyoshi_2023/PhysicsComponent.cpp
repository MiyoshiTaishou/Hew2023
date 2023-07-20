#include "PhysicsComponent.h"
#include"gameObject.h"
#include"input.h"
#include<SimpleMath.h>
#include"ImGuiManager.h"
#include"scene.h"
#include"manager.h"
#include"camera.h"
#include"Player.h"

using namespace DirectX::SimpleMath;

void PhysicsComponent::Init()
{

}

void PhysicsComponent::Uninit()
{
}

void PhysicsComponent::Update()
{
	//シーンにあるオブジェを取る
	Scene* nowscene = Manager::GetScene();
	Camera* cameraObj = nowscene->GetGameObject<Camera>();
	Player* playerObj = nowscene->GetGameObject<Player>();

	//カメラのマトリックスを取る
	Matrix viewmtx = cameraObj->GetViewMatrix();
	Vector3 ZAxis = Vector3(viewmtx._13, 0.0f, viewmtx._33);
	Vector3 XAxis = Vector3(viewmtx._11, 0.0f, viewmtx._31);

	//プレイヤーの速度を取る
	float vel = playerObj->GetVelocity().x;


}

void PhysicsComponent::Draw()
{
	
}
