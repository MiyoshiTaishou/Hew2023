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
#include"../Mesh/CUndulationPlaneMesh.h"
#include"../Mesh/CPlane.h"
#include"../Mesh/CPlaneMeshTexture.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;


//  �����b�V���i�W�I���g���f�[�^�j
//static CPlaneMeshWithoutCommon g_planemesh;					
// �n�`�v���[�����擾����ꍇ�́@�K���@�b�o���������l���������g����
//    ���R�́A
//static CPlaneMesh g_planemesh;
static CUndulationPlaneMesh g_planemesh;


// �����b�V���i�����_�����O�f�[�^�j
static CMeshRenderer g_meshrenderer;

std::vector<CPlane> g_planes;

void Field::Init()
{
	// �e�N�X�`���ǂݍ���
	DirectX::CreateWICTextureFromFile(
		Renderer::GetDevice(),
		L"../asset/texture/field.jpg",
		nullptr,
		&m_Texture);

	assert(m_Texture);

	AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\PS_OrangeScale.cso");

	m_Collider = AddComponent<Collider>();
	m_Collider->Init();

	// �����b�V������
	g_planemesh.Init(
		10, 10,					// ������
		640,					// �T�C�Y
		640,					// �T�C�Y
		Color(1, 1, 1, 1),		// ���_�J���[
		Vector3(0, 0, -1),		// �@���x�N�g��
		true);					// XZ����

	// �ʉ���t����i��l���z�Łj
	g_planemesh.MakeUndulation(
		0.0f,					// �ŏ�
		30.0f);					// �ő�

	// ���b�V�������_�������i���p�j
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
	
	// GPU�ɍs����Z�b�g����
	Matrix mtx;
	DX11MakeWorldMatrix(
		mtx,
		m_Scale,							// �X�P�[��
		m_Rotation,							// �p��
		m_Position);						// �ʒu

	Renderer::SetWorldMatrix(&mtx);

	// ���`��
	g_planemesh.Draw();
	g_meshrenderer.Draw();

	ImGui::Begin("Debug");
	ImGui::Text("Dir %f,%f,%f", direction.x, direction.y, direction.z);
	ImGui::Text("Normal %f,%f,%f", normalDB.x, normalDB.y, normalDB.z);
	ImGui::End();

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

	float threshold = 0.9f;

	// �ʐ���
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
			if (sts)
			{
				float slope = fabsf(g_planes[idx].GetPlaneInfo().pNormal.Dot(up));

				//�]�����
				if (slope > threshold)
				{
					//�⓹��]���鏈��
					Vector3 dir = CalculateDiagonalDirection(g_planes[idx].GetPlaneInfo().pNormal);

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
					normalDB = g_planes[idx].GetPlaneInfo().pNormal;
				}				

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