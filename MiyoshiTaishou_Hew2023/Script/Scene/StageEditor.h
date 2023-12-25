#pragma once
#include"scene.h"

class StageEditor : public Scene
{
public:
	void Init()override;
	void Update()override;
	void Draw()override;

private:
	//�I�u�W�F�N�g�̐���
	void CreateObj();

	//�I�u�W�F�N�g�l�����֐�
	void ObjListManger();

	//���X�g�̃I�u�W�F�N�g��Index
	int selectedObjectIndex = -1;

	GameObject* obj;

	//���O�ύX�p�ϐ�
	char m_buffer[256] = "test.csv";
};


