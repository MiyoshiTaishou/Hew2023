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
	std::vector<ID3D11ShaderResourceView*>	m_DiffuseSRVtable;		// �f�B�t���[�Y�e�N�X�`��SRV
	std::vector<SUBSET>	m_Subsets;					// �T�u�Z�b�g���

	std::vector<CMaterial*>		m_Materials;		// �}�e���A���Q
	CVertexBuffer<VERTEX_3D>	m_VertexBuffer;		// ���_�o�b�t�@
	CIndexBuffer				m_IndexBuffer;		// �C���f�b�N�X�o�b�t�@
};
