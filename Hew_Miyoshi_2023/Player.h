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
	DirectX::SimpleMath::Vector2 GetVelocity();

private:

	DirectX::SimpleMath::Vector3		m_Velocity{};
	class Audio* m_SE{};	

	std::list<GameObject*> m_Children;
	GameObject* mchild;

	//塊の大きさ
	float m_Size;	
	
	//頂点座標
	std::vector<DirectX::SimpleMath::Vector3> m_VertexPos;

	//速度
	DirectX::SimpleMath::Vector2 velocity{};

	//加速度
	float acc = 0.01f;

	//時間
	float time = 0.0f;

	//実際の加速度
	float vel = 0;

	//質量
	float math = 5.0f;

	//跳ね返り係数
	float coefficient = 1.0f;
};

