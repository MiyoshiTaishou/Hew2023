#pragma once
#include"scene.h"

class Player;
class Camera;

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
	char m_bufferField[256] = "test.csv";
	char m_bufferMap[256] = "test.csv";

	Player* m_Player;
	Camera* m_Camera;
};


