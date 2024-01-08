#include "field.h"
#include <WICTextureLoader.h>

//マネージャー
#include"../Sysytem/dx11mathuntil.h"
#include"../Sysytem/manager.h"

//シーン
#include"../Scene/scene.h"

//オブジェクト
#include"../Object/Player.h"

//コンポーネント
#include "../Component/shader.h"
#include"../Component/Collider.h"
#include"../Component/RigidBody.h"

//描画
#include "../Render/modelRenderer.h"

//メッシュ
#include"../Mesh/CPlaneMesh.h"
#include"../Mesh/CMeshRenderer.h"
#include"../Mesh/CPlaneMeshTexture.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void Field::Init()
{
	AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\vertexLightingPS.cso");
	m_Collider = AddComponent<Collider>();

	// 床メッシュ生成
	m_planemesh.Init(
		25, 25,					// 分割数
		320,						// サイズ
		320,						// サイズ
		Color(1, 1, 1, 1),			// 頂点カラー
		Vector3(0, 0, -1),			// 法線ベクトル
		true);						// XZ平面

	// 凸凹を付ける（一様分布で）
//	m_planemesh.MakeUndulation(
//		0.0f,						// 最小
//		3.0f);						// 最大

	//m_planemesh.MakeUndulationPerlinnoise(
	//	10.0f,			// 最大の高さ
	//	10,				// オクターブ数
	//	0.28f);			// パーシステンス

	m_planemesh.LoadUndulation("saveMap.csv");

	// 平面の方程式を生成（全面）
	MakeEquatation();

	// レンダラー初期化
	m_renderer.Init(m_planemesh);

	// テクスチャ読み込み
	DirectX::CreateWICTextureFromFile(
		Renderer::GetDevice(),
		L"../asset/texture/Stone.jpg",
		nullptr,
		&m_Texture);

	assert(m_Texture);
}

void Field::Uninit()
{
	for (auto& com : m_Component) {
		com->Uninit();
		delete com;
	}

	m_Component.clear();
	
	m_Texture->Release();
}

void Field::Draw()
{
	GetComponent<Shader>()->Draw();

	// ワールドマトリクス設定
	Matrix world, scale, rot, trans;
	scale = Matrix::CreateScale(m_Scale.x);
	rot = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	trans = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//レンダラで描画
	m_renderer.Draw();

	//ImGui::Begin("Debug");
	//ImGui::Text("Dir %f,%f,%f", direction.x, direction.y, direction.z);
	//ImGui::Text("Normal %f,%f,%f", normalDB.x, normalDB.y, normalDB.z);
	//ImGui::Text("Dis %f", dis);
	//ImGui::End();

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


	m_planemesh.MakeUndulationSelf();

	// 平面の方程式を生成（全面）
	MakeEquatation();

	// レンダラー初期化
	m_renderer.Init(m_planemesh);

	ImGui::Begin("FiledCreate");	
	if (ImGui::Button(("Save")))
	{
		m_planemesh.SaveUndulation("saveMap.csv");
	}
	ImGui::End();
}

void Field::MakeEquatation()
{
	// 面数を取得
	int numface;
	numface = m_planemesh.GetIndices().size() / 3;

	std::vector<VERTEX_3D> vertices;
	vertices = m_planemesh.GetVertices();

	// 面数分ループ
	for (unsigned int idx = 0; idx < numface; idx++) {

		CPlaneMesh::FACE f = m_planemesh.GetTriangle(idx);

		VERTEX_3D v0 = vertices[f.idx[0]];
		VERTEX_3D v1 = vertices[f.idx[1]];
		VERTEX_3D v2 = vertices[f.idx[2]];

		CPlane p;
		p.MakeEquatation(v0.Position, v1.Position, v2.Position);
		m_planes.emplace_back(p);
	}
}

float Field::GetFieldHeight(DirectX::SimpleMath::Vector3 pos)
{	
	float t;	

	// 面数分
	for (unsigned int idx = 0; idx < m_planes.size(); idx++) {
		Vector3 up = { 0,1,0 };
		Vector3 startpoint = { pos.x,0,pos.z };
		Plane p = m_planes[idx].GetPlaneInfo().plane;
		Vector3 ans;

		bool sts = m_Collider->LinetoPlaneCross(p, startpoint, up, t, ans);
		if (sts) {
			sts = m_Collider->CheckInTriangle(
				m_planes[idx].GetPlaneInfo().p0,
				m_planes[idx].GetPlaneInfo().p1,
				m_planes[idx].GetPlaneInfo().p2, ans);
			if (sts)
			{
				float slope = fabsf(m_planes[idx].GetPlaneInfo().pNormal.Dot(up));
				
				//坂道を転がる処理
				Vector3 dir = CalculateDiagonalDirection(m_planes[idx].GetPlaneInfo().pNormal);

				Scene* scene = Manager::GetScene();
				Player* player = scene->GetGameObject<Player>();

				if (!player)
				{
					return ans.y;
				}

				RigidBody* body = player->GetComponent<RigidBody>();					

				Vector3 force = dir * 10.0f;
			
				//body->AddForceToPoint(force, dir, ForceMode::Force);
				//body->AddForce(force, ForceMode::Force);		

				force.y = 0.0f;

				//body->AddTorque((force), ForceMode::Force);

				direction = dir;
				normalDB = m_planes[idx].GetPlaneInfo().pNormal;
							

				return ans.y;
			}
		}
	}

	return 0;
}

Vector3 Field::CalculateDiagonalDirection(Vector3 normal)
{
	// 法線ベクトルが垂直な方向（Y軸方向）を取得
	Vector3 up = Vector3(0, 1, 0);

	// 法線ベクトルと垂直な方向を求める（クロス積）
	Vector3 diagonalDirection = normal.Cross(up);	

	Vector3 dir = normal.Cross(diagonalDirection);

	// 正規化して長さを1にする
	dir.Normalize();

	// ボールが坂道を下る方向は逆向き
	return dir;
}

float Field::GetFieldHeightBySqno(DirectX::SimpleMath::Vector3 pos, GameObject& obj)
{
	float t;

	// 現在位置からのっかている四角形番号を取得
	int sqno = m_planemesh.GetSquareNo(pos);

	static float oldheight = 0;

	// 下面チェック
	{
		int idx = sqno * 2;

		// 面数分
		Vector3 up = { 0,1,0 };
		Vector3 startpoint = { pos.x,0,pos.z };
		Plane p = m_planes[idx].GetPlaneInfo().plane;
		Vector3 ans;

		bool sts = m_Collider->LinetoPlaneCross(p, startpoint, up, t, ans);
		if (sts) {
			sts = m_Collider->CheckInTriangle(
				m_planes[idx].GetPlaneInfo().p0,
				m_planes[idx].GetPlaneInfo().p1,
				m_planes[idx].GetPlaneInfo().p2, ans);
			if (sts) {

				Scene* scene = Manager::GetScene();				
				
				//坂道を転がる処理
				Vector3 dir = CalculateDiagonalDirection(m_planes[idx].GetPlaneInfo().pNormal);				

				RigidBody* body = obj.GetComponent<RigidBody>();

				if (body == nullptr)
				{
					return ans.y;
				}

				Vector3 force = dir * 10.0f;
				force.y = 0.0f;

				body->AddForceToPoint(force, dir, ForceMode::Force);
				body->AddForce(force, ForceMode::Force);						

				//body->AddTorque((force), ForceMode::Force);

				direction = dir;
				normalDB = m_planes[idx].GetPlaneInfo().pNormal;

				oldheight = ans.y;
				return ans.y;
			}
		}
	}

	// 上面チェック
	{
		int idx = sqno * 2 + 1;

		// 面数分
		Vector3 up = { 0,1,0 };
		Vector3 startpoint = { pos.x,0,pos.z };
		Plane p = m_planes[idx].GetPlaneInfo().plane;
		Vector3 ans;

		bool sts = m_Collider->LinetoPlaneCross(p, startpoint, up, t, ans);
		if (sts) {
			sts = m_Collider->CheckInTriangle(
				m_planes[idx].GetPlaneInfo().p0,
				m_planes[idx].GetPlaneInfo().p1,
				m_planes[idx].GetPlaneInfo().p2, ans);
			if (sts) 
			{

				Scene* scene = Manager::GetScene();				

				//坂道を転がる処理
				Vector3 dir = CalculateDiagonalDirection(m_planes[idx].GetPlaneInfo().pNormal);				

				RigidBody* body = obj.GetComponent<RigidBody>();

				if (body == nullptr)
				{
					return ans.y;
				}

				//傾きが小さいなら
				if (dir.x < 0.5f)
				{
					dir.x = 0.0f;
				}
				if (dir.z < 0.5f)
				{
					dir.z = 0.0f;
				}

				Vector3 force = dir * 10.0f;
				force.y = 0.0f;

				body->AddForceToPoint(force, dir, ForceMode::Force);
				body->AddForce(force, ForceMode::Force);		

				force.y = 0.0f;

				//body->AddTorque((force), ForceMode::Force);

				direction = dir;
				normalDB = m_planes[idx].GetPlaneInfo().pNormal;

				oldheight = ans.y;
				return ans.y;
			}
		}

	}

	// 見つからなかった場合は０
	//std::cout << "床なし" << "(" << sqno << ")" << std::endl;
	return oldheight;
}

void Field::PointPlaneCollision(DirectX::SimpleMath::Vector3* _point)
{
	float t;

	// すべての点のめり込み量を考慮してオブジェクト全体を補正する
	Vector3 totalCorrection = Vector3::Zero;

	for (int i = 0; i < MAX_SPHERE_MESH; i++)
	{
		// 現在位置からのっかている四角形番号を取得
		int sqno = m_planemesh.GetSquareNo(_point[i]);

		static float oldheight = 0;

		// 下面チェック
		{
			int idx = sqno * 2;

			// 面数分
			Vector3 up = { 0,1,0 };
			Vector3 startpoint = { _point[i].x,0,_point[i].z};
			Plane p = m_planes[idx].GetPlaneInfo().plane;
			Vector3 ans;

			bool sts = m_Collider->LinetoPlaneCross(p, startpoint, up, t, ans);
			if (sts) {
				sts = m_Collider->CheckInTriangle(
					m_planes[idx].GetPlaneInfo().p0,
					m_planes[idx].GetPlaneInfo().p1,
					m_planes[idx].GetPlaneInfo().p2, ans);
				if (sts) {
					Plane plane = m_planes[idx].GetPlaneInfo().plane;
					float distance = plane.x * _point[i].x + plane.y * _point[i].y + plane.z * _point[i].z + plane.w;

					dis = distance;

					if (distance <= 0)
					{
						Scene* scene = Manager::GetScene();

						Player* player = scene->GetGameObject<Player>();

						float moveDistance = -distance * 0.5f;

						Vector3 pos = player->GetPosition();

						totalCorrection.x += moveDistance * plane.x;
						totalCorrection.y += moveDistance * plane.y;
						totalCorrection.z += moveDistance * plane.z;

						//player->SetPosition(pos);						
					}
				}
			}
		}

		// 上面チェック
		{
			int idx = sqno * 2 + 1;

			// 面数分
			Vector3 up = { 0,1,0 };
			Vector3 startpoint = { _point[i].x,0,_point[i].z};
			Plane p = m_planes[idx].GetPlaneInfo().plane;
			Vector3 ans;

			bool sts = m_Collider->LinetoPlaneCross(p, startpoint, up, t, ans);
			if (sts) {
				sts = m_Collider->CheckInTriangle(
					m_planes[idx].GetPlaneInfo().p0,
					m_planes[idx].GetPlaneInfo().p1,
					m_planes[idx].GetPlaneInfo().p2, ans);
				if (sts)
				{
					Plane plane = m_planes[idx].GetPlaneInfo().plane;
					float distance = plane.x * _point[i].x + plane.y * _point[i].y + plane.z * _point[i].z + plane.w;


					dis = distance;

					if (distance <= 0)
					{
						Scene* scene = Manager::GetScene();

						Player* player = scene->GetGameObject<Player>();

						float moveDistance = -distance * 0.5f;

						Vector3 pos = player->GetPosition();

						totalCorrection.x += moveDistance * plane.x;
						totalCorrection.y += moveDistance * plane.y;
						totalCorrection.z += moveDistance * plane.z;

						//player->SetPosition(pos);
					}
				}
			}

		}
	}

	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	player->SetPosition(player->GetPosition() + totalCorrection);
}
