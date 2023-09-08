/**
 * @file modelRender.h
 * @brief ���f�������[�h����N���X
 * @author ��ؐ搶
 */

#pragma once
#include <string>
#include <unordered_map>
#include "component.h"
#include "utftosjisconv.h"
#include<SimpleMath.h>



/**
 * @enum MODEL_MATERIAL
 * �}�e���A���\����
 */
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
	ID3D11ShaderResourceView*	Texture;

};


/**
 * @enum SUBSET
 * �`��T�u�Z�b�g�\����
 */
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};


/**
 * @enum SUBSET
 * ���f���\����
 */
struct MODEL_OBJ
{
	VERTEX_3D		*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	SUBSET			*SubsetArray;
	unsigned int	SubsetNum;
};


struct MODEL
{
	ID3D11Buffer*	VertexBuffer;
	ID3D11Buffer*	IndexBuffer;

	SUBSET*			SubsetArray;
	unsigned int	SubsetNum;
};

class ModelRenderer : public Component
{
private:

	static std::unordered_map<std::string, MODEL*> m_ModelPool;

	static void LoadModel(const char *FileName, MODEL *Model);
	static std::vector<DirectX::SimpleMath::Vector3> LoadModelVertex(const char *FileName, MODEL *Model);
	static void LoadObj( const char *FileName, MODEL_OBJ *ModelObj );	
	static std::vector<DirectX::SimpleMath::Vector3> LoadObjVertex(const char* FileName, MODEL_OBJ* ModelObj);
	static void LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum );	

	MODEL* m_Model{};	

public:

	static void Preload( const char *FileName );
	static void UnloadAll();


	using Component::Component;

	void Load( const char *FileName );		
	std::vector<DirectX::SimpleMath::Vector3> LoadVertex( const char *FileName );

	std::vector<VERTEX_3D> GetVertex(const char* FileName);
	int GetIndexNum();

	void Draw() override;
};