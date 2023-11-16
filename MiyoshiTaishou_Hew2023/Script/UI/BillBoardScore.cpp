#include "BillBoardScore.h"
#include<WICTextureLoader.h>

#include"../Component/shader.h"

//オブジェクト
#include"../Object/Player.h"
#include"../Object/camera.h"
#include"../Object/field.h"

//システム
#include"../Sysytem/manager.h"

#include"../Scene/scene.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void BillBoardScore::Init()
{
	AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\PS_OrangeScale.cso");

	VERTEX_3D vertex[4];

	vertex[0].Position = Vector3(-m_Width, m_Height, 0.0f);
	vertex[0].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = Vector2(0.0f, 0.0f);

	vertex[1].Position = Vector3(m_Width, m_Height, 0.0f);
	vertex[1].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = Vector2(1.0f, 0.0f);

	vertex[2].Position = Vector3(-m_Width, -m_Height, 0.0f);
	vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = Vector2(0.0f, 1.0f);

	vertex[3].Position = Vector3(m_Width, -m_Height, 0.0f);
	vertex[3].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = Vector2(1.0f, 1.0f);

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// テクスチャ読み込み
	DirectX::CreateWICTextureFromFile(
		Renderer::GetDevice(),
		L"../asset/texture/number.png",
		nullptr,
		&m_Texture);

	assert(m_Texture);

	m_Count = 0;

	//向きが違うので合わせる
	m_Rotation.z = 3.2f;
	m_Rotation.y = 90.0f;
}

void BillBoardScore::Uninit()
{	
	m_VertexBuffer->Release();
	m_Texture->Release();
}

void BillBoardScore::Draw()
{
	GetComponent<Shader>()->Draw();

	// ワールドマトリクス設定
	Matrix world, scale, rot, trans;
	scale = Matrix::CreateScale(m_Scale.x);
	rot = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	trans = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	int count = m_Count;

	int number = count % 10;
	count /= 10;

	//テクスチャ座標算出
	float tx = number % 5 * (1.0f / 5);
	float ty = number / 5 * (1.0f / 5);

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	HRESULT result = Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;	

	vertex[0].Position = Vector3(-m_Width, -m_Height, 0.0f);
	vertex[0].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = Vector2(tx, ty);

	vertex[1].Position = Vector3(m_Width, -m_Height, 0.0f);
	vertex[1].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = Vector2(tx + 0.2f, ty);

	vertex[2].Position = Vector3(-m_Width, m_Height, 0.0f);
	vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = Vector2(tx, ty + 0.2f);

	vertex[3].Position = Vector3(m_Width, m_Height, 0.0f);
	vertex[3].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = Vector2(tx + 0.2f, ty + 0.2f);

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);	
}

void BillBoardScore::Update()
{
	Scene* nowscene = Manager::GetScene();
	Camera* camera = nowscene->GetGameObject<Camera>();

	//常にプレイヤーの方を向く処理
	//プレイヤーへのベクトルを計算
	Vector3 dir = camera->GetPosition() - m_Position;
	m_Rotation.y = atan2(dir.x, dir.z);
}
