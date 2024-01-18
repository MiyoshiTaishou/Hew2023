#include "BillBoardObject.h"
#include<WICTextureLoader.h>

#include"../Component/shader.h"

//�I�u�W�F�N�g
#include"../Object/Player.h"
#include"../Object/camera.h"
#include"../Object/field.h"

//�V�X�e��
#include"../Sysytem/manager.h"

#include"../Scene/scene.h"

using namespace DirectX::SimpleMath;

void BillBoardObject::Init()
{
	AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\PS_OrangeScale.cso");

	VERTEX_3D vertex[4];

	vertex[0].Position = Vector3(-5.0f, 5.0f, 0.0f);
	vertex[0].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = Vector2(0.0f, 0.0f);

	vertex[1].Position = Vector3(5.0f, 5.0f, 0.0f);
	vertex[1].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = Vector2(1.0f, 0.0f);

	vertex[2].Position = Vector3(-5.0f, -5.0f, 0.0f);
	vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = Vector2(0.0f, 1.0f);

	vertex[3].Position = Vector3(5.0f, -5.0f, 0.0f);
	vertex[3].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = Vector2(1.0f, 1.0f);

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// �e�N�X�`���ǂݍ���
	DirectX::CreateWICTextureFromFile(
		Renderer::GetDevice(),
		L"../asset/texture/GameStart.png",
		nullptr,
		&m_Texture);

	assert(m_Texture);

	//���̃��b�V���쐬
	m_Sphere = new CSphereMesh();
	m_Sphere->Init(2.0f, Color(1, 1, 1, 1), 100, 100);

	m_MeshRenderer = new CMeshRenderer();
	m_MeshRenderer->Init(*m_Sphere);

	m_SphereMt.Ambient = Color(0, 0, 0, 0);
	m_SphereMt.Diffuse = Color(1, 1, 1, 0.3f);
	m_SphereMt.Specular = Color(0, 0, 0, 0);
	m_SphereMt.Shininess = 0;
	m_SphereMt.Emission = Color(0, 0, 0, 0);
	m_SphereMt.TextureEnable = FALSE;

	m_Scale.x = 5.0f;
}

void BillBoardObject::Init(const char* TextureName)
{
	AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\PS_OrangeScale.cso");

	VERTEX_3D vertex[4];

	vertex[0].Position = Vector3(-5.0f, 5.0f, 0.0f);
	vertex[0].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = Vector2(0.0f, 0.0f);

	vertex[1].Position = Vector3(5.0f, 5.0f, 0.0f);
	vertex[1].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = Vector2(1.0f, 0.0f);

	vertex[2].Position = Vector3(-5.0f, -5.0f, 0.0f);
	vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = Vector2(0.0f, 1.0f);

	vertex[3].Position = Vector3(5.0f, -5.0f, 0.0f);
	vertex[3].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = Vector2(1.0f, 1.0f);

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	std::wstring ws = sjis_to_wide_winapi(TextureName);

	// �e�N�X�`���ǂݍ���
	DirectX::CreateWICTextureFromFile(
		Renderer::GetDevice(),
		ws.c_str(),
		nullptr,
		&m_Texture);

	assert(m_Texture);
}

void BillBoardObject::Uninit()
{
	for (auto& com : m_Component) {
		com->Uninit();
		delete com;
	}

	m_Component.clear();

	m_VertexBuffer->Release();
	m_Texture->Release();

	delete m_MeshRenderer;
	delete m_Sphere;
}

void BillBoardObject::Draw()
{
	GetComponent<Shader>()->Draw();

	// ���[���h�}�g���N�X�ݒ�
	Matrix world, scale, rot, trans;
	scale = Matrix::CreateScale(m_Scale.x);
	rot = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	trans = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	
	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);

	// �}�e���A���ݒ�
	Renderer::SetMaterial(m_SphereMt);
	//m_MeshRenderer->Draw();
}

void BillBoardObject::Update()
{
	Scene* nowscene = Manager::GetScene();
	Camera* camera = nowscene->GetGameObject<Camera>();

	//��Ƀv���C���[�̕�����������
	//�v���C���[�ւ̃x�N�g�����v�Z
	Vector3 dir = camera->GetPosition() - m_Position;
	m_Rotation.y = atan2(dir.x, dir.z);
	//�p�x������Ă���̂Œ���
	m_Rotation.y -= 60.0f;

	//�������擾	
	Field* filed = nowscene->GetGameObject<Field>();
	if (!filed)
	{
		return;
	}

	//�@�͈̓`�F�b�N 
	Vector3 max = filed->GetMax();
	Vector3 min = filed->GetMin();

	if (m_Position.x <= min.x) {
		m_Position.x = min.x;
	}
	if (m_Position.x >= max.x) {
		m_Position.x = max.x;
	}

	if (m_Position.z <= min.z) {
		m_Position.z = min.z;
	}
	if (m_Position.z >= max.z) {
		m_Position.z = max.z;
	}

	float Height = filed->GetFieldHeightBySqno(m_Position,*this);

	//float Height = 0.0f;

	if (Height != 0.0f + 5.0f)
	{
		//pos.y = Height;
		m_Position.y = Height + 5;
	}
}
