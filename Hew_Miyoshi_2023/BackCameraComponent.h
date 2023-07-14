#pragma once
#include "component.h"
#include"gameObject.h"
#include<SimpleMath.h>

class Camera;

//�v���C���[�̌�납��Ǐ]����J����
class BackCameraComponent : public Component
{
public:
	using Component::Component;

	void Init();
	void Uninit() override;
	void Update();
	
	DirectX::SimpleMath::Vector3 GetCameraPos();
	DirectX::SimpleMath::Vector3 GetCameraFocus();
	void SetTarget(GameObject& obj);
private:	
	//�Ǐ]����I�u�W�F�N�g
	GameObject* targetObj;

	DirectX::SimpleMath::Vector3 cameraPos;
	DirectX::SimpleMath::Vector3 cameraFocus;
};