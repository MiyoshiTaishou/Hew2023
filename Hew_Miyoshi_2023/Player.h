#pragma once
#include "gameObject.h"
#include<SimpleMath.h>
#include<vector>

class Link;

class Player :  public GameObject
{
public:
	void Init()override;	
	void Uninit()override;
	void Update()override;
	void Draw()override;	

private:

	DirectX::SimpleMath::Vector3		m_Velocity{};
	class Audio* m_SE{};	

	std::list<GameObject*> m_Children;
	GameObject* mchild;

	//塊の大きさ
	float m_Size;	
	
	//頂点座標
	std::vector<DirectX::SimpleMath::Vector3> m_VertexPos;

	//初速度
	float velocity = 0.1f;

	//加速度
	float acc = 0.01f;

	//時間
	float time = 0.0f;

	//実際の加速度
	float vel = 0;
};

