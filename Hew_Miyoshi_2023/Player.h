#pragma once
#include "gameObject.h"
#include<SimpleMath.h>
#include<vector>
#include"GamePad.h"

//���삷��L����
class Player :  public GameObject
{
public:
	void Init()override;	
	void Update()override;
	void Draw()override;		

	DirectX::GamePad::State buttonState;

private:

	DirectX::SimpleMath::Vector3		m_Velocity{};

	//SE
	class Audio* m_SE{};	
	class Audio* m_MeatSE{};	
	class Audio* m_MeatSE2{};	

	//�q�I�u�W�F�N�g
	std::list<GameObject*> m_Children;
	GameObject* mchild;

	//��̑傫��
	float m_Size;	

	//�_�b�V���p�ϐ�
	int loopCount = 0;
	int reception = 60;
	int actionCount = 0;
	int actionDashu = 5;
	bool actionCheck = false;

	//�Ǔo��p�ϐ�
	bool wallUp = false;
	
	//���_���W
	std::vector<DirectX::SimpleMath::Vector3> m_VertexPos;		
};

