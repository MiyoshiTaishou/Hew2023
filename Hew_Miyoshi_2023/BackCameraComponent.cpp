#include "BackCameraComponent.h"
#include"camera.h"
#include<SimpleMath.h>

using namespace DirectX::SimpleMath;

void BackCameraComponent::Init()
{
	
}

void BackCameraComponent::Uninit()
{
	
}

void BackCameraComponent::Update()
{
	// 追尾カメラの処理
	// ①操作キャラの前向きベクトルを取得する
	Vector3 forwardVec = targetObj->GetForward();
	// ②前向きベクトルを反転させて後ろ向きベクトルを作る
	Vector3 backVec;
	backVec.x = -forwardVec.x;
	backVec.y = -forwardVec.y;
	backVec.z = -forwardVec.z;

	Vector3 camEye;
	float camDistance = 50.0f;
	camEye.x = targetObj->GetPosition().x + backVec.x * camDistance;
	camEye.y = targetObj->GetPosition().y + backVec.y * camDistance + 5.0f;
	camEye.z = targetObj->GetPosition().z + backVec.z * camDistance;

	// ④カメラ注視点（focus）をキャラの少し前に設定
	Vector3 camFocus;
	float camFDistance = 5.0f;
	camFocus.x = targetObj->GetPosition().x + forwardVec.x * camFDistance;
	camFocus.y = targetObj->GetPosition().y + forwardVec.y * camFDistance;
	camFocus.z = targetObj->GetPosition().z + forwardVec.z * camFDistance;
	
	cameraPos = camEye;
	cameraFocus = camFocus;
}

DirectX::SimpleMath::Vector3 BackCameraComponent::GetCameraPos()
{
	return cameraPos;
}

DirectX::SimpleMath::Vector3 BackCameraComponent::GetCameraFocus()
{
	return cameraFocus;
}

void BackCameraComponent::SetTarget(GameObject& obj)
{
	targetObj = &obj;
}
