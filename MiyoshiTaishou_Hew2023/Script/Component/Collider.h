#pragma once
#include"component.h"
#include<SimpleMath.h>

//�����蔻��̐e�N���X
class Collider : public Component
{
public:

	void Init();

	void Update();

	void SetColliderScale(DirectX::SimpleMath::Vector3 _scale);

private:

	using Component::Component;

protected:
	//�����蔻���������悤�ɂ���
	bool m_View = true;

	//�����蔻��̍��W
	DirectX::SimpleMath::Vector3 m_ColliderPos;

	//�����蔻��̑傫��
	DirectX::SimpleMath::Vector3 m_ColliderScale;

	//�����蔻��̉�]
	DirectX::SimpleMath::Vector3 m_ColliderRot;
};
