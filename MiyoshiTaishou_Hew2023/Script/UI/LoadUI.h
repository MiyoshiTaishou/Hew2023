#pragma once


#include "../Object/gameObject.h"

class Audio;

class LoadUI : public GameObject
{
private:

	//lerp����������������
	bool m_Goal = true;

	//0~1��lerp�̐i�s���Ǘ�
	float m_Rate = 0;
	
	//�����ʒu
	DirectX::SimpleMath::Vector3 m_StratPos;

	//���Ԓn�_
	DirectX::SimpleMath::Vector3 m_IntermediatePos;

	//�ړI�n
	DirectX::SimpleMath::Vector3 m_GoalPos;

public:
	void Init();		
	void Update();
	//���[�h���ɂ��鏈��
	void LoadAction(Audio* _audio);
};