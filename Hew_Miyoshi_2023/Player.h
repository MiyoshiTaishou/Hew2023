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

	//塊の大きさ
	float m_Size = 0;	

	//受付時間
	int reception = 60;

	//受付時間カウント
	int receptionTime;
	
	//ダッシュアクションカウント
	int actionDashu = 5;
	int actionDashuCount = 0;
	bool timeCountStart = false;
	
	//頂点座標
	std::vector<DirectX::SimpleMath::Vector3> m_VertexPos;		
};

