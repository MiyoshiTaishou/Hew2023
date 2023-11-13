#include "Customer.h"

//コンポーネント
#include"../Component/shader.h"

//オブジェクト
#include"field.h"

//シーン
#include"../Scene/scene.h"

//システム
#include"../Sysytem/manager.h"
#include"../Sysytem/input.h"

using namespace DirectX::SimpleMath;

void Customer::Init()
{
	AddComponent<Shader>()->Load("../shader\\vertexLightingOneSkinVS.cso", "../shader\\vertexLightingPS.cso"); //20230909-02

	m_Model = AddComponent<AnimationModel>();

	m_Model->Load("../asset\\model\\Akai.fbx");									// animation ok
	m_Model->LoadAnimation("../asset\\model\\Akai_Idle.fbx", "Idle");
	m_Model->LoadAnimation("../asset\\model\\Akai_Run.fbx", "Run");

	m_Scale = Vector3(0.1f, 0.1f, 0.1f);
	m_Position.z = 10.0f;
}

void Customer::Update()
{
	Scene* nowscene = Manager::GetScene();

	if (Input::GetKeyPress('W'))
	{
		m_BlendRate += 0.1f;
		m_Frame++;

	}
	else if (Input::GetKeyPress('S'))
	{
		m_BlendRate += 0.1f;
		m_Frame--;
	}
	else
	{
		m_BlendRate -= 0.1f;
		m_Frame++;
	}

	if (m_BlendRate > 1.0f)
		m_BlendRate = 1.0f;
	if (m_BlendRate < 0.0f)
		m_BlendRate = 0.0f;

	// フィールドオブジェクト取得
	Field* fieldobj = nowscene->GetGameObject<Field>();

	if (!fieldobj)
	{
		return;
	}

	//　範囲チェック 
	Vector3 max = fieldobj->GetMax();
	Vector3 min = fieldobj->GetMin();

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

	//接地
	float groundHeight = fieldobj->GetFieldHeightBySqno(m_Position);

	// 位置が０以下なら地面位置にセットする
	if (m_Position.y < groundHeight)
	{
		m_Position.y = groundHeight;		
	}	
}

void Customer::PreDraw()
{
	m_Model->Update("Idle", m_Frame, "Run", m_Frame, m_BlendRate);
}


