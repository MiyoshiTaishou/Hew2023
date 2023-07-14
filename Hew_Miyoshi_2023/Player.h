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

	//‰ò‚Ì‘å‚«‚³
	float m_Size;	
	
	std::vector<DirectX::SimpleMath::Vector3> m_VertexPos;
};

