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
	DirectX::SimpleMath::Vector2 GetVelocity();

	DirectX::GamePad::State buttonState;

private:

	DirectX::SimpleMath::Vector3		m_Velocity{};
	class Audio* m_SE{};	
	class Audio* m_MeatSE{};	

	std::list<GameObject*> m_Children;
	GameObject* mchild;

	//âÚÇÃëÂÇ´Ç≥
	float m_Size;	
	
	//í∏ì_ç¿ïW
	std::vector<DirectX::SimpleMath::Vector3> m_VertexPos;		
};

