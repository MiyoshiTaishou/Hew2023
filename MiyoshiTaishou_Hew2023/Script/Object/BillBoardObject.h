#pragma once
#include "../Object/gameObject.h"
#include"../Mesh/CMeshRenderer.h"
#include"../Mesh/CSphereMesh.h"

class BillBoardObject : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};	

	CMeshRenderer* m_MeshRenderer;
	CSphereMesh* m_Sphere;
	MATERIAL m_SphereMt;

public:
	void Init();
	void Uninit();
	void Draw();	
	void Update();	
};