#pragma once
#include"component.h"
#include<SimpleMath.h>

//Unity��RigidBody�ɂȂ�ׂ��߂��`��ڎw��

// �ǂ̌v�Z�����g����
enum class ForceMode
{
	Force,           ///< ���ʂɈˑ����A�p���I�ȗ͂�^����
	Acceleration,    ///< ���ʂɈˑ������A�p���I�ȗ͂�^����
	Impulse,         ///< ���ʂɈˑ����A�u�ԓI�ȗ͂�^����
	VelocityChange   ///< ���ʂɈˑ������A�u�ԓI�ȗ͂�^����
};

//�ǂ����Œ�ɂ��邩���鎞�Ɏg��
enum FrizeNum
{
	Xpos,  ///< X���W�̈ʒu���Œ�
	YPos,  ///< Y���W�̈ʒu���Œ�
	ZPos,  ///< Z���W�̈ʒu���Œ�
	XRot,  ///< X���̉�]���Œ�
	YRot,  ///< Y���̉�]���Œ�
	ZRot   ///< Z���̉�]���Œ�
};

struct Frieze
{
	bool Xpos;  ///< X���W�̈ʒu���Œ�
	bool YPos;  ///< Y���W�̈ʒu���Œ�
	bool ZPos;  ///< Z���W�̈ʒu���Œ�
	bool XRot;  ///< X���̉�]���Œ�
	bool YRot;  ///< Y���̉�]���Œ�
	bool ZRot;  ///< Z���̉�]���Œ�
};

class RigidBody : public Component
{
public:

	void Init();
	void Update();
	void Draw();

	//�͂�������
	//�����@�͂̃x�N�g��,�͂̌v�Z���[�h
	void AddForce(DirectX::SimpleMath::Vector3 _force, ForceMode forceMode);

	//���̌Œ�
	void SetFreeze(FrizeNum freez, bool _b);

	//��]��������
	void AddTorque(DirectX::SimpleMath::Vector3 _torque, ForceMode forceMode);

	//�����e���\���̐ݒ�
	void SetInetiaTensorOfSpherAngular(float _radius, DirectX::SimpleMath::Vector3 _centerOfMass);

	//�����̂̃e���\���̐ݒ�
	void SetInetiaTensorOfRectangular(float x, float y, float z, DirectX::SimpleMath::Vector3 _centerOfMass);

	//��_�ɗ͂�������
	void AddForceToPoint(DirectX::SimpleMath::Vector3 _force, DirectX::SimpleMath::Vector3 localPos, ForceMode forceMode);

private:

	Component::Component;

	//��
	
	//���̂̎���
	float m_Mass = 1.0f;			

	//�͂ɂ���ē����ۂ̋�C��R�̑傫��
	float m_Drag = -1.0f;				

	//�d�͂̉e�����󂯂�
	bool m_UseGravity = true;		

	//�d�͂̋���
	float m_GravityScale = 0.1f;   

	//�I�u�W�F�N�g�̌��݂̑��x
	DirectX::SimpleMath::Vector3 m_Velocity; 

	//�I�u�W�F�N�g�Ɍ��݉������Ă����
	DirectX::SimpleMath::Vector3 m_Force;



	//��]

	//�I�u�W�F�N�g�̏d�S�̈ʒu(���[�J�����W)
	DirectX::SimpleMath::Vector3 m_CenterOfMass;	
	
	//���݂̊p���x
	DirectX::SimpleMath::Vector3 m_AngularVelocity;

	//���݂̃g���N
	DirectX::SimpleMath::Vector3 m_Torque;
	
	//�����e���\��
	DirectX::SimpleMath::Matrix m_InetiaTensor;
	 
	
	//�g���N�ɂ���ĉ�]����ۂɁA�I�u�W�F�N�g�ɉe�������C��R�̑傫��
	float m_AngularDrag = -1.0f;

	//�Œ���
	Frieze m_Frize;


};
