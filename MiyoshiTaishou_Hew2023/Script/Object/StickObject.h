#pragma once
#include"gameObject.h"


//���������I�u�W�F�N�g�͂��̃N���X���p������
class StickObject : public GameObject
{
public:
	
	void Update();

	//���������Ƃ��ɌĂԏ���
	void Stick();

private:

	//�������Ă��邩�ǂ���
	bool m_Stick = false;

	//���̃T�C�Y����ǂꂾ�����������邩�̔{��
	float m_ScaleDown = 0.1f;
};
