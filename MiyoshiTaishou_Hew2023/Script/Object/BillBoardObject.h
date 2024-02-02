#pragma once
#include "../Object/gameObject.h"
#include"../Mesh/CMeshRenderer.h"
#include"../Mesh/CSphereMesh.h"

//ビルボード処理の3Dオブジェクト
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
	//テクスチャ指定可能
	void Init(const char* TextureName);
	void Uninit();
	void Draw();	
	void Update();	
};