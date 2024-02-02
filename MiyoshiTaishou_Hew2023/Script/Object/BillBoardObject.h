#pragma once
#include "../Object/gameObject.h"
#include"../Mesh/CMeshRenderer.h"
#include"../Mesh/CSphereMesh.h"

//�r���{�[�h������3D�I�u�W�F�N�g
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
	//�e�N�X�`���w��\
	void Init(const char* TextureName);
	void Uninit();
	void Draw();	
	void Update();	
};