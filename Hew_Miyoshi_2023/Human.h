#pragma once
#include "gameObject.h"
#include"animationModel.h"
#include	"CShader.h"
#include	"CMaterial.h"
#include	"CStaticMesh.h"

#include	"CStaticMeshRenderer.h"

//アニメーション付きの人
class Human : public GameObject
{
private:

	//class AnimationModel* m_Model;
	int m_Frame;
	float m_BlendRate;

	// 描画の為に必要な情報
// 使用するシェーダー
	CShader		g_shader;

	// スタティックメッシュ（ジオメトリデータ）
	//CPlaneMesh g_planemesh;
	CStaticMesh g_staticmesh;

	// メッシュレンダラー
	CStaticMeshRenderer g_staticmeshrenderer;

public:
	void Init() override;
	void Uninit()override;
	void Update() override;
	void Draw()override;
	void PreDraw() override;
};

