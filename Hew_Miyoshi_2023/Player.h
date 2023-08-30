#pragma once
#include "gameObject.h"
#include<SimpleMath.h>
#include<vector>
#include"GamePad.h"

class Link;

class Player :  public GameObject
{
public:
	void Init()override;	
	void Uninit()override;
	void Update()override;
	void Draw()override;		

	DirectX::GamePad::State buttonState;

private:

	DirectX::SimpleMath::Vector3		m_Velocity{};
	class Audio* m_SE{};	
	class Audio* m_MeatSE{};	
	class Audio* m_MeatSE2{};	

	std::list<GameObject*> m_Children;
	GameObject* mchild;

	//��̑傫��
	float m_Size = 0;	

	//��t����
	int reception = 60;

	//��t���ԃJ�E���g
	int receptionTime;
	
	//�_�b�V���A�N�V�����J�E���g
	int actionDashu = 5;
	int actionDashuCount = 0;
	bool timeCountStart = false;
	
	//���_���W
	std::vector<DirectX::SimpleMath::Vector3> m_VertexPos;		
};

