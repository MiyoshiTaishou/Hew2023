#include "StickObject.h"

#include"../Sysytem/manager.h"

#include"../Scene/scene.h"

#include"../Component/BoxCollider.h"

#include"field.h"
#include"camera.h"
#include"BoxObject.h"

using namespace DirectX::SimpleMath;

void StickObject::Update()
{	
	//くっついていたら処理をしない
	if (m_Stick)
	{				
		return;
	}
	
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

	float Height = filed->GetFieldHeightBySqno(m_Position);

	m_Position.y = Height;
}

//くっついたときの呼ぶ処理
void StickObject::Stick()
{
	// 現在シーンを取得
	Scene* scene = Manager::GetScene();

	//カメラ取得
	Camera* cameraObj = scene->GetGameObject<Camera>();

	m_Stick = true;
	m_Scale *= m_ScaleDown;

	//座標設定
	m_Position = cameraObj->GetForward() * m_Scale * 0.2f;
}
