#pragma once
#include	<d3d11.h>
#include	<DirectXMath.h>
#include	<wrl/client.h>
#include	<vector>
#include	<string>
#include	<unordered_map>
#include	<WICTextureLoader.h>

// assimp�T�D�Q�D�O�p
#include	<assimp\Importer.hpp>
#include	<assimp\scene.h>
#include	<assimp\postprocess.h>
#include	<assimp/cimport.h>

// ���_��`
#include	"renderer.h"

#include	"utility.h"
#include	"CMaterial.h"

// assimp 5.2.0 �p���C�u����
#pragma comment(lib,"assimp-vc143-mtd.lib")


// COMPTR���g����悤��
using Microsoft::WRL::ComPtr;

class CStaticMesh {
private:
	std::vector<VERTEX_3D>		m_vertices;		// ���_���W�Q
	std::vector<unsigned int>	m_indices;		// �C���f�b�N�X�f�[�^�Q
	std::vector<SUBSET>			m_subsets;		// �T�u�Z�b�g�Q
	std::vector<MATERIAL>		m_materials;	// �}�e���A���e�[�u��

	// ���b�V���Ɋ܂܂�钸�_�����o��
	unsigned int GetVertices(const aiMesh* aimesh);
	// ���b�V���Ɋ܂܂��C���f�b�N�X�����o��
	unsigned int  GetIndices(const aiMesh* aimesh);

	// �T�u�Z�b�g���P�ɂ܂Ƃ߂邽�߂̃x�[�X���v�Z����
	void CalcMeshBaseIndex();

	// �S�e�N�X�`�����擾(�������쐬�����)
	void GetTextures(const aiScene* aiscene);

	// �����e�N�X�`�����ǂ��������ʂ���
	bool isEmbeddedTexure(const aiTexture* aitexture);

	// assimp�̓����f�[�^�ɃZ�b�g����Ă���e�N�X�`�������L�[�Ƃ��ĕۑ�
	std::unordered_map<std::string, ID3D11ShaderResourceView*> m_Texturedic;

	// �}�e���A���Ɋ܂܂��f�[�^���擾����
	void GetMaterials(const aiScene* aiscene);				// �S�}�e���A�������[�v
	void GetaMatreial(const aiMaterial* aimtrl);			// �P�̃}�e���A��

	// �e�N�X�`�����\�[�X�e�[�u��
	std::vector<ID3D11ShaderResourceView*>	m_AllTexture;

	// �e�N�X�`���t�@�C����ǂݍ����SRV�𐶐�����
	ID3D11ShaderResourceView* LoadDiffuseTexture(std::string filename);

	// ���̃��f���̃p�X��
	std::string m_filename;
public:
	// ������
	bool Init(std::string filename);

	// �I������
	void Exit();

	// ���_�f�[�^�擾
	const std::vector<VERTEX_3D>& GetVertices() {
		return m_vertices;
	}

	// �C���f�b�N�X�f�[�^�擾
	const std::vector<unsigned int>& GetIndices() {
		return m_indices;
	}

	// �T�u�Z�b�g�f�[�^�擾
	const std::vector<SUBSET>& GetSubsets() {
		return m_subsets;
	}

	// SRV�e�[�u���擾
	const std::vector<ID3D11ShaderResourceView*>& GetSRVtable() {
		return m_AllTexture;
	}

	// �}�e���A���f�[�^�擾
	const std::vector<MATERIAL>& GetMaterials() {
		return m_materials;
	}
};

