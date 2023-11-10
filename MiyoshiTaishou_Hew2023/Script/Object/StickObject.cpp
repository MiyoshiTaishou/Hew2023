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

	float Height = filed->GetFieldHeight(m_Position);

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
	m_Position = cameraObj->GetForward() * m_Scale * 2.0f;
}
