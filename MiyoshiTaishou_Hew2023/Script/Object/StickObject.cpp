#include "StickObject.h"

#include"../Sysytem/manager.h"

#include"../Scene/scene.h"

//コンポーネント
#include"../Component/BoxCollider.h"
#include"../Component/RigidBody.h"
#include"../Component/SphereCollider.h"
#include"../Component/audio.h"

//オブジェクト
#include"field.h"
#include"camera.h"
#include"BoxObject.h"
#include"Player.h"

using namespace DirectX::SimpleMath;

void StickObject::Init()
{
	m_HitSE = AddComponent<Audio>();
	m_HitSE->Load("../asset\\audio\\ぷよん_2.wav");
}

void StickObject::Update()
{			
	Scene* scene = Manager::GetScene();

	Field* filed = scene->GetGameObject<Field>();

	if (!filed)
	{
		return;
	}	

	//　範囲チェック 
	Vector3 max = filed->GetMax();
	Vector3 min = filed->GetMin();

	if (m_Position.x <= min.x) {
		m_Position.x = min.x;
	}
	if (m_Position.x >= max.x) {
		m_Position.x = max.x;
	}

	if (m_Position.z <= min.z) {
		m_Position.z = min.z;
	}
	if (m_Position.z >= max.z) {
		m_Position.z = max.z;
	}

	//くっついていたら親オブジェクトを上げる
	if (m_Stick)
	{
		//// 親オブジェクト(Player)を取得
		//Player* player = scene->GetGameObject<Player>();

		//// 親オブジェクトのローカル座標系におけるオフセットを求める
	 // // マトリクス設定
		//DirectX::SimpleMath::Matrix world, scale, rot, trans;
		//scale = DirectX::SimpleMath::Matrix::CreateScale(player->GetScale().x, player->GetScale().y, player->GetScale().z);
		//rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(player->GetRotation().y, player->GetRotation().x, player->GetRotation().z);
		//trans = DirectX::SimpleMath::Matrix::CreateTranslation(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
		//world = scale * rot * trans;

		//// 親オブジェクトのローカル座標系のY軸ベクトルを取得
		//DirectX::SimpleMath::Vector3 parentLocalYAxis(0.0f, 1.0f, 0.0f); // 親オブジェクトのローカルY軸（例として上向きを仮定）

		//// 親オブジェクトのローカル座標系のY軸ベクトルを回転行列で変換
		//DirectX::SimpleMath::Vector3 rotatedParentLocalYAxis = DirectX::SimpleMath::Vector3::TransformNormal(parentLocalYAxis, world);

		//// hitPositionLocalが親オブジェクトの下方向にあるかどうかをチェック
		//float dotProduct = m_Position.Dot(rotatedParentLocalYAxis);

		////下方向
		//if (dotProduct < 0.0f) 
		//{
		//	float Height = filed->GetFieldHeightBySqno(m_Position, true);			
		//	Vector3 pos = player->GetPosition();
		//	pos.y = Height + 4;
		//	player->SetPosition(pos);
		//}		
		//else
		//{
		//	Vector3 pos = player->GetPosition();
		//	float Height = filed->GetFieldHeightBySqno(pos, true);
		//	pos.y = Height;
		//	player->SetPosition(pos);
		//}
	}
	else
	{
		float Height = filed->GetFieldHeightBySqno(m_Position, *this);

		m_Position.y = Height + 2.0f;
	}	
}

//くっついたときの呼ぶ処理
void StickObject::Stick(Vector3 _pos)
{
	// 現在シーンを取得
	Scene* scene = Manager::GetScene();

	////カメラ取得
	//Camera* cameraObj = scene->GetGameObject<Camera>();

	m_Stick = true;
	m_Scale *= m_ScaleDown;

	//座標設定
	//m_Position = cameraObj->GetForward() * m_Scale * 0.2f;

	//慣性テンソルを足す
	Player* player = scene->GetGameObject<Player>();	

	// 親オブジェクトのローカル座標系におけるオフセットを求める
	  // マトリクス設定
	DirectX::SimpleMath::Matrix world, scale, rot, trans;
	scale = DirectX::SimpleMath::Matrix::CreateScale(player->GetScale().x, player->GetScale().y, player->GetScale().z);
	rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(player->GetRotation().y, player->GetRotation().x, player->GetRotation().z);
	trans = DirectX::SimpleMath::Matrix::CreateTranslation(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
	world = scale * rot * trans;

	// 親オブジェクト（Playerなど）の逆行列を取得してローカル座標系に変換する
	DirectX::SimpleMath::Matrix parentWorldMatrixInverse = world.Invert();
	DirectX::SimpleMath::Vector3 hitPositionLocal = DirectX::SimpleMath::Vector3::Transform(_pos, parentWorldMatrixInverse);

	// 子オブジェクトの位置を計算された世界座標系のオフセットに設定
	m_Position = hitPositionLocal;

	RigidBody* body = player->GetComponent<RigidBody>();
	body->AddInetiaTensorOfSpherAngular(body->GetInetiaTensor() / 100);
	body->SetMass((body->GetMass() + 0.01f));	

	m_HitSE->Play();
}
