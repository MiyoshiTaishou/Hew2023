#pragma once
#include<SimpleMath.h>
#include "component.h"

//�A�b�h�t�H�[�X
enum class ForceMode
{
	Force, // ���ʂɈˑ����A�p���I�ȗ͂�^����
	Acceleration, // ���ʂɈˑ������A�p���I�ȗ͂�^����
	Impuluse, // ���ʂɈˑ����A�u�ԓI�ȗ͂�^����
	VelocityChange // ���ʂɈˑ������A�u�ԓI�ȗ͂�^����
};

class Rigidbody : public Component
{
public:
	using Component::Component;
	
	void Init(float _mass, float _drag);
	void Update() override;

	void AddForce(DirectX::SimpleMath::Vector3 _force, ForceMode forceMode);	
private:
	float mass;//�I�u�W�F�N�g�̎���
	float drag;//���C
	DirectX::SimpleMath::Vector3 velocity;//�I�u�W�F�N�g�̌��݂̑��x
	DirectX::SimpleMath::Vector3 force;//�I�u�W�F�N�g�Ɍ��݉������Ă����
};

