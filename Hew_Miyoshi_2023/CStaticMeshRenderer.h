#pragma once
#include	<vector>
#include	"renderer.h"
#include	"CVertexBuffer.h"
#include	"CIndexBuffer.h"
#include	"CStaticMesh.h"
#include	"CShader.h"

class CStaticMeshRenderer {
public:
	void Draw();
	void Init(CStaticMesh& mesh);
	void Uninit();
private:
	std::vector<ID3D11ShaderResourceView*>	m_DiffuseSRVtable;		// ディフューズテクスチャSRV
	std::vector<SUBSET>	m_Subsets;					// サブセット情報

	std::vector<CMaterial*>		m_Materials;		// マテリアル群
	CVertexBuffer<VERTEX_3D>	m_VertexBuffer;		// 頂点バッファ
	CIndexBuffer				m_IndexBuffer;		// インデックスバッファ
};
