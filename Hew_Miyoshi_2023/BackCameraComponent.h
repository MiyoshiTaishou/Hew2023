#pragma once
#include "component.h"
#include"gameObject.h"
#include<SimpleMath.h>

class Camera;

//プレイヤーの後ろから追従するカメラコンポーネント
class BackCameraComponent : public Component
{
public:
	using Component::Component;

	void Update();
	
	DirectX::SimpleMath::Vector3 GetCameraPos();
	DirectX::SimpleMath::Vector3 GetCameraFocus();
	void SetTarget(GameObject& obj);

private:	
	//追従するオブジェクト
	GameObject* targetObj;

	DirectX::SimpleMath::Vector3 cameraPos;
	DirectX::SimpleMath::Vector3 cameraFocus;
};