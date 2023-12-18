#include "FakeTakotaki.h"

//コンポーネント
#include"../Component/RigidBody.h"
#include"../Component/shadow.h"

//システム
#include"../Scene/scene.h"
#include"../Sysytem/manager.h"

//オブジェクト
#include"Player.h"
#include"field.h"

using namespace DirectX::SimpleMath;

void FakeTakoyakiObject::Init()
{
	TakoyakiObject::Init();

	AddComponent<RigidBody>()->SetGravity(false);
}

void FakeTakoyakiObject::Update()
{
	if (m_Stick)
	{
		GetComponent<Shadow>()->SetShadowView(false);
		return;
	}

	//現在のシーンを取得
	Scene* scene = Manager::GetScene();

	//プレイヤーを取得
	Player* player = scene->GetGameObject<Player>();

	if (!player)
	{
		return;
	}

	//プレイヤーへのベクトル取得
	Vector3 toPlayerVec = m_Position - player->GetPosition();

	//距離を計算
	float distance = toPlayerVec.Length();

	//範囲内なら逃げる
	if (distance < m_EscapeLength)
	{
		//正規化する
		toPlayerVec.Normalize();
		toPlayerVec.y = 0.0f;

		GetComponent<RigidBody>()->AddForce((toPlayerVec * m_Speed), ForceMode::Force);
	}
	else
	{
		return;
	}

	Field* filed = scene->GetGameObject<Field>();

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
}
