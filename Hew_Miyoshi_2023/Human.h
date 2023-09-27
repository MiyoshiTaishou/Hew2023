#pragma once
#include "gameObject.h"
#include"animationModel.h"
#include	"CShader.h"
#include	"CMaterial.h"
#include	"CStaticMesh.h"

#include	"CStaticMeshRenderer.h"

//�A�j���[�V�����t���̐l
class Human : public GameObject
{
private:

	//class AnimationModel* m_Model;
	int m_Frame;
	float m_BlendRate;

	// �`��ׂ̈ɕK�v�ȏ��
// �g�p����V�F�[�_�[
	CShader		g_shader;

	// �X�^�e�B�b�N���b�V���i�W�I���g���f�[�^�j
	//CPlaneMesh g_planemesh;
	CStaticMesh g_staticmesh;

	// ���b�V�������_���[
	CStaticMeshRenderer g_staticmeshrenderer;

public:
	void Init() override;
	void Uninit()override;
	void Update() override;
	void Draw()override;
	void PreDraw() override;
};

