#pragma once

#include"../Object/gameObject.h"

//UI�̏�Ԃ��Ǘ�����
enum STATEUI
{
	Stop,   //�����J�n�O
	AddRun,	//���Z������
	SubRun, //���Z������
};

class Sprite;

class HitUI : public GameObject
{
public:

	void Init();
	void Init(int x, int y, int Width, int Height, const char* TextureName);
	void Update();
	void Draw();
	//UI�\��
	void Indication();

private:

	MATERIAL m_MT;
	STATEUI m_State = Stop;
	Sprite* m_Sprite;
	DirectX::SimpleMath::Color m_Color;	

	//�v������
	float m_Time = 0.0f;

	//���Ԃɑ����l���̒l�ŏオ����𒲐�
	float m_AddTime = 0.005f;
};