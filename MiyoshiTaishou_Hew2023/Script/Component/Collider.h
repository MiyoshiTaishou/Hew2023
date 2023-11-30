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

	void SetRelative(DirectX::SimpleMath::Vector3 _rel);

	void SetCanHit(bool _hit);
	
	DirectX::SimpleMath::Vector3 GetPos()
	{
		return m_ColliderPos;
	}

	DirectX::SimpleMath::Vector3 GetRelative()
	{
		return m_Relative;
	}

	bool CheckInTriangle(
		const DirectX::SimpleMath::Vector3& a,
		const DirectX::SimpleMath::Vector3& b,
		const DirectX::SimpleMath::Vector3& c,
		const DirectX::SimpleMath::Vector3& p);

	bool LinetoPlaneCross(
		const DirectX::SimpleMath::Plane& plane,		//���ʂ̕�����
		const DirectX::SimpleMath::Vector3& p0,			//�����̋N�_
		const DirectX::SimpleMath::Vector3& wv,			//�����̕����x�N�g��
		float& t,			// ��_�ʒu���	
		DirectX::SimpleMath::Vector3& ans);		//��_���W

private:

	using Component::Component;

protected:
	//�����蔻���������悤�ɂ���
	bool m_View = true;

	//�����蔻��̍��W
	DirectX::SimpleMath::Vector3 m_ColliderPos;

	//���Έʒu
	DirectX::SimpleMath::Vector3 m_Relative;

	//�����蔻��̑傫��
	DirectX::SimpleMath::Vector3 m_ColliderScale;

	//�����蔻��̉�]
	DirectX::SimpleMath::Vector3 m_ColliderRot;

	//�����蔻�肪�L�����ǂ���
	bool m_CanHit = true;

};
