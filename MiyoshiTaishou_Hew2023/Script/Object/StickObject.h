#pragma once
#include"gameObject.h"

class Audio;

//���������I�u�W�F�N�g�͂��̃N���X���p������
class StickObject : public GameObject
{
public:

	void Init();
	void Update();

	//���������Ƃ��ɌĂԏ���
	void Stick(DirectX::SimpleMath::Vector3 _pos);

private:

	//�������Ă��邩�ǂ���
	bool m_Stick = false;

	//���̃T�C�Y����ǂꂾ�����������邩�̔{��
	float m_ScaleDown = 0.1f;

	Audio* m_HitSE;
};
