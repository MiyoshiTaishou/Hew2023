#include "field.h"
#include <WICTextureLoader.h>

//�}�l�[�W���[
#include"../Sysytem/dx11mathuntil.h"
#include"../Sysytem/manager.h"

//�V�[��
#include"../Scene/scene.h"

//�I�u�W�F�N�g
#include"../Object/Player.h"

//�R���|�[�l���g
#include "../Component/shader.h"
#include"../Component/Collider.h"
#include"../Component/RigidBody.h"

//�`��
#include "../Render/modelRenderer.h"

//���b�V��
#include"../Mesh/CPlaneMesh.h"
#include"../Mesh/CMeshRenderer.h"
#include"../Mesh/CPlaneMeshTexture.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void Field::Init()
{
	AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\vertexLightingPS.cso");
	m_Collider = AddComponent<Collider>();

	// �����b�V������
	m_planemesh.Init(
		25, 25,					// ������
		320,						// �T�C�Y
		320,						// �T�C�Y
		Color(1, 1, 1, 1),			// ���_�J���[
		Vector3(0, 0, -1),			// �@���x�N�g��
		true);						// XZ����

	// �ʉ���t����i��l���z�Łj
//	m_planemesh.MakeUndulation(
//		0.0f,						// �ŏ�
//		3.0f);						// �ő�

	//m_planemesh.MakeUndulationPerlinnoise(
	//	10.0f,			// �ő�̍���
	//	10,				// �I�N�^�[�u��
	//	0.28f);			// �p�[�V�X�e���X

	m_planemesh.LoadUndulation("saveMap.csv");

	// ���ʂ̕������𐶐��i�S�ʁj
	MakeEquatation();

	// �����_���[������
	m_renderer.Init(m_planemesh);

	// �e�N�X�`���ǂݍ���
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

	// ���[���h�}�g���N�X�ݒ�
	Matrix world, scale, rot, trans;
	scale = Matrix::CreateScale(m_Scale.x);
	rot = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	trans = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//�����_���ŕ`��
	m_renderer.Draw();

	//ImGui::Begin("Debug");
	//ImGui::Text("Dir %f,%f,%f", direction.x, direction.y, direction.z);
	//ImGui::Text("Normal %f,%f,%f", normalDB.x, normalDB.y, normalDB.z);
	//ImGui::Text("Dis %f", dis);
	//ImGui::End();

	// ���̓��C�A�E�g�ݒ�
//	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
//	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
//	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//// ���[���h�}�g���N�X�ݒ�
	//Matrix world, scale, rot, trans;
	//scale = Matrix::CreateScale(m_Scale.x);
	//rot = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	//trans = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	//world = scale * rot * trans;
	//Renderer::SetWorldMatrix(&world);

	//// ���_�o�b�t�@�ݒ�
	//UINT stride = sizeof(VERTEX_3D);
	//UINT offset = 0;
	//Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//// �}�e���A���ݒ�
	//MATERIAL material;
	//ZeroMemory(&material, sizeof(material));
	//material.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	//material.TextureEnable = true;
	//Renderer::SetMaterial(material);

	//// �e�N�X�`���ݒ�
	//Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//// �v���~�e�B�u�g�|���W�ݒ�
	//Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//// �|���S���`��
	//Renderer::GetDeviceContext()->Draw(4, 0);


	m_planemesh.MakeUndulationSelf();

	// ���ʂ̕������𐶐��i�S�ʁj
	MakeEquatation();

	// �����_���[������
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
	// �ʐ����擾
	int numface;
	numface = m_planemesh.GetIndices().size() / 3;

	std::vector<VERTEX_3D> vertices;
	vertices = m_planemesh.GetVertices();

	// �ʐ������[�v
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

	// �ʐ���
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
				
				//�⓹��]���鏈��
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
	// �@���x�N�g���������ȕ����iY�������j���擾
	Vector3 up = Vector3(0, 1, 0);

	// �@���x�N�g���Ɛ����ȕ��������߂�i�N���X�ρj
	Vector3 diagonalDirection = normal.Cross(up);	

	Vector3 dir = normal.Cross(diagonalDirection);

	// ���K�����Ē�����1�ɂ���
	dir.Normalize();

	// �{�[�����⓹����������͋t����
	return dir;
}

float Field::GetFieldHeightBySqno(DirectX::SimpleMath::Vector3 pos, GameObject& obj)
{
	float t;

	// ���݈ʒu����̂����Ă���l�p�`�ԍ����擾
	int sqno = m_planemesh.GetSquareNo(pos);

	static float oldheight = 0;

	// ���ʃ`�F�b�N
	{
		int idx = sqno * 2;

		// �ʐ���
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
				
				//�⓹��]���鏈��
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

	// ��ʃ`�F�b�N
	{
		int idx = sqno * 2 + 1;

		// �ʐ���
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

				//�⓹��]���鏈��
				Vector3 dir = CalculateDiagonalDirection(m_planes[idx].GetPlaneInfo().pNormal);				

				RigidBody* body = obj.GetComponent<RigidBody>();

				if (body == nullptr)
				{
					return ans.y;
				}

				//�X�����������Ȃ�
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

	// ������Ȃ������ꍇ�͂O
	//std::cout << "���Ȃ�" << "(" << sqno << ")" << std::endl;
	return oldheight;
}

void Field::PointPlaneCollision(DirectX::SimpleMath::Vector3* _point)
{
	float t;

	// ���ׂĂ̓_�̂߂荞�ݗʂ��l�����ăI�u�W�F�N�g�S�̂�␳����
	Vector3 totalCorrection = Vector3::Zero;

	for (int i = 0; i < MAX_SPHERE_MESH; i++)
	{
		// ���݈ʒu����̂����Ă���l�p�`�ԍ����擾
		int sqno = m_planemesh.GetSquareNo(_point[i]);

		static float oldheight = 0;

		// ���ʃ`�F�b�N
		{
			int idx = sqno * 2;

			// �ʐ���
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

		// ��ʃ`�F�b�N
		{
			int idx = sqno * 2 + 1;

			// �ʐ���
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
