#pragma once
#include"component.h"
#include"../Mesh/CMeshRenderer.h"
#include"../Mesh/CSphereMesh.h"
#include"../Particle/Particle.h"

#define MAX_BEJIE 10

//ベジエ曲線を用いて移動をするためのコンポーネント
class RootChaise : public Component
{
public:

	void Init();
	void Uninit();
	void Draw();
	void Update();

private:

	float m_Rate = 0.0f;
	float m_MoveSpeed = 0.005f;

	//可視化用のメッシュ
	CMeshRenderer* m_MeshRenderer[MAX_BEJIE];
	CSphereMesh* m_Sphere[MAX_BEJIE];

	//ベジエの座標
	DirectX::SimpleMath::Vector3 m_SpherePos[MAX_BEJIE];

	//到着したか
	bool m_Goal = false;

	using Component::Component;
	
	//名前変更用変数
	char m_buffer[256] = "../asset/map/YataiRoot.csv";
};
