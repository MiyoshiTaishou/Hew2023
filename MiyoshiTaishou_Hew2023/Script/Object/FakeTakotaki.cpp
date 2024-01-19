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

#define MAX_FILED 20

void FakeTakoyakiObject::Init()
{
	TakoyakiObject::Init();

	RigidBody* body = AddComponent<RigidBody>();
	body->SetGravity(false);
	body->SetFreeze(FrizeNum::XRot, true);
	body->SetFreeze(FrizeNum::ZRot, true);
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

	Field* filed = scene->GetGameObject<Field>();

	//　範囲チェック 
	Vector3 max = filed->GetMax();
	Vector3 min = filed->GetMin();

	if (m_Position.x <= min.x + MAX_FILED) {
		m_Position.x = min.x + MAX_FILED;
	}
	if (m_Position.x >= max.x - MAX_FILED) {
		m_Position.x = max.x - MAX_FILED;
	}

	if (m_Position.z <= min.z + MAX_FILED) {
		m_Position.z = min.z + MAX_FILED;
	}
	if (m_Position.z >= max.z - MAX_FILED) {
		m_Position.z = max.z - MAX_FILED;
	}

	m_Position.y = filed->GetFieldHeightBySqno(m_Position, *this);
	m_Position.y += 2.0f;

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
}
