#pragma once
#include"component.h"
#include<SimpleMath.h>


//�l�p�`�̓����蔻��̃R���|�[�l���g
class BoxCollider : public Component
{
public:
	using Component::Component;

	void Init()override;
	void Update()override;
	void Draw()override;

	bool HitCheck(BoxCollider other);

	DirectX::SimpleMath::Vector3 GetHitBox();
	DirectX::SimpleMath::Vector3 GetScale();

private:

	//�����蔻��̍��W
	DirectX::SimpleMath::Vector3 mHitBox = { 0,0,0 };

	//�R���C�_�[�̃T�C�Y
	DirectX::SimpleMath::Vector3 mScale = { 1.0f,1.0f,1.0f };	
};

