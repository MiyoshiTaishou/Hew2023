#include "field.h"
#include <WICTextureLoader.h>
#include"../Sysytem/dx11mathuntil.h"

//コンポーネント
#include "../Component/shader.h"
#include"../Component/Collider.h"

//描画
#include "../Render/modelRenderer.h"

//メッシュ
#include"../Mesh/CPlaneMesh.h"
#include"../Mesh/CMeshRenderer.h"
#include"../Mesh/CUndulationPlaneMesh.h"
#include"../Mesh/CPlane.h"

using namespace DirectX::SimpleMath;


//  床メッシュ（ジオメトリデータ）
//static CPlaneMeshWithoutCommon g_planemesh;					
// 地形プレーンを取得する場合は　必ず　ＣＰｌａｎｅＭｅｓｈを使う事
//    理由は、
//static CPlaneMesh g_planemesh;
static CUndulationPlaneMesh g_planemesh;


// 床メッシュ（レンダリングデータ）
static CMeshRenderer g_meshrenderer;

std::vector<CPlane> g_planes;

void Field::Init()
{
	// テクスチャ読み込み
	DirectX::CreateWICTextureFromFile(
		Renderer::GetDevice(),
		L"asset/texture/field.jpg",
		nullptr,
		&m_Texture);

	assert(m_Texture);

	AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\PS_OrangeScale.cso");

	m_Collider = AddComponent<Collider>();
	m_Collider->Init();

	// 床メッシュ生成
	g_planemesh.Init(
		10, 10,					// 分割数
		640,					// サイズ
		640,					// サイズ
		Color(1, 1, 1, 1),		// 頂点カラー
		Vector3(0, 0, -1),		// 法線ベクトル
		true);					// XZ平面

	// 凸凹を付ける（一様分布で）
	g_planemesh.MakeUndulation(
		0.0f,					// 最小
		30.0f);					// 最大

	// メッシュレンダラ生成（床用）
	g_meshrenderer.Init(g_planemesh);	
}

void Field::Uninit()
{
	for (auto& com : m_Component) {
		com->Uninit();
		delete com;
	}

	m_Component.clear();

	/*m_VertexBuffer->Release();
	m_Texture->Release();*/
}

void Field::Draw()
{
	GetComponent<Shader>()->Draw();
	
	// GPUに行列をセットする
	Matrix mtx;
	DX11MakeWorldMatrix(
		mtx,
		m_Scale,							// スケール
		m_Rotation,							// 姿勢
		m_Position);						// 位置

	Renderer::SetWorldMatrix(&mtx);

	// 床描画
	g_meshrenderer.Draw();

	// 入力レイアウト設定
//	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
//	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
//	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//// ワールドマトリクス設定
	//Matrix world, scale, rot, trans;
	//scale = Matrix::CreateScale(m_Scale.x);
	//rot = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	//trans = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	//world = scale * rot * trans;
	//Renderer::SetWorldMatrix(&world);

	//// 頂点バッファ設定
	//UINT stride = sizeof(VERTEX_3D);
	//UINT offset = 0;
	//Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//// マテリアル設定
	//MATERIAL material;
	//ZeroMemory(&material, sizeof(material));
	//material.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	//material.TextureEnable = true;
	//Renderer::SetMaterial(material);

	//// テクスチャ設定
	//Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//// プリミティブトポロジ設定
	//Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//// ポリゴン描画
	//Renderer::GetDeviceContext()->Draw(4, 0);

}

void Field::makepalenequatation()
{
	for (unsigned int idx = 0; idx < g_planemesh.GetIndices().size() / 3; idx++) {
		CPlaneMesh::FACE f = g_planemesh.GetTriangle(idx);

		VERTEX_3D v0 = g_planemesh.GetVertices()[f.idx[0]];
		VERTEX_3D v1 = g_planemesh.GetVertices()[f.idx[1]];
		VERTEX_3D v2 = g_planemesh.GetVertices()[f.idx[2]];

		CPlane p;
		p.MakeEquatation(v0.Position, v1.Position, v2.Position);
		g_planes.emplace_back(p);
	}
}

float Field::GetFieldHeight(DirectX::SimpleMath::Vector3 pos)
{
	static bool firstflag = true;
	if (firstflag == true) {
		makepalenequatation();
		firstflag = false;
	}

	float t;
	// 面数分
	for (unsigned int idx = 0; idx < g_planes.size(); idx++) {
		Vector3 up = { 0,1,0 };
		Vector3 startpoint = { pos.x,0,pos.z };
		Plane p = g_planes[idx].GetPlaneInfo().plane;
		Vector3 ans;

		bool sts = m_Collider->LinetoPlaneCross(p, startpoint, up, t, ans);
		if (sts) {
			sts = m_Collider->CheckInTriangle(
				g_planes[idx].GetPlaneInfo().p0,
				g_planes[idx].GetPlaneInfo().p1,
				g_planes[idx].GetPlaneInfo().p2, ans);
			if (sts) return ans.y;
		}
	}

	return 0;
}
