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

enum class Freeze
{
	Xpos,
	YPos,
	ZPos,
	XRot,
	YRot,
	ZRot
};

class Rigidbody : public Component
{
public:
	using Component::Component;
	
	void Init(float _mass, float _drag,float _gravityScale);
	void Update() override;
	void Draw() override;

	void AddForce(DirectX::SimpleMath::Vector3 _force, ForceMode forceMode);	

	DirectX::SimpleMath::Vector3 GetVelocity();
	void SetVelocity(DirectX::SimpleMath::Vector3 _vel);

	void SetForce(DirectX::SimpleMath::Vector3 _force);

	void SetFreeze(Freeze freez,bool _b);
	bool GetFreeze(Freeze freez);

	void SetDrag(float _drag);
	void InitDrag();

private:
	float mass;//�I�u�W�F�N�g�̎���
	float drag;//���C
	float saveDrag;//�ۑ��p
	float gravityScale;//�d�͂̋���
	DirectX::SimpleMath::Vector3 velocity;//�I�u�W�F�N�g�̌��݂̑��x
	DirectX::SimpleMath::Vector3 force;//�I�u�W�F�N�g�Ɍ��݉������Ă����	
	
	bool mXPos = false;
	bool mYPos = false;
	bool mZPos = false;
	bool mXRot = false;
	bool mYRot = false;
	bool mZRot = false;
};

