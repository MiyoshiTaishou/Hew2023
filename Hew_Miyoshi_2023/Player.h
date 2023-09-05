#pragma once
#include "gameObject.h"
#include<SimpleMath.h>
#include<vector>
#include"GamePad.h"

//操作するキャラ
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

	//子オブジェクト
	std::list<GameObject*> m_Children;
	GameObject* mchild;

	//塊の大きさ
	float m_Size;	

	//ダッシュ用変数
	int loopCount = 0;
	int reception = 60;
	int actionCount = 0;
	int actionDashu = 5;
	bool actionCheck = false;

	//壁登り用変数
	bool wallUp = false;
	
	//頂点座標
	std::vector<DirectX::SimpleMath::Vector3> m_VertexPos;		
};

