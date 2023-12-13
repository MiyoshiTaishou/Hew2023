#include "ParticleObject.h"
#include<WICTextureLoader.h>

#include"../Component/shader.h"

//�I�u�W�F�N�g
#include"../Object/camera.h"

//�V�X�e��
#include"../Sysytem/manager.h"

#include"../Scene/scene.h"

//�R���|�[�l���g
#include"../Component/RigidBody.h"

using namespace DirectX::SimpleMath;

void ParticleObject::Init()
{
	AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso", "../shader\\unlitTexturePS.cso");
	AddComponent<RigidBody>();

	VERTEX_3D vertex[4];

	vertex[0].Position = Vector3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = Vector2(0.0f, 0.0f);

	vertex[1].Position = Vector3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = Vector2(1.0f, 0.0f);

	vertex[2].Position = Vector3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = Vector2(0.0f, 1.0f);

	vertex[3].Position = Vector3(1.0f, -1.0f, 0.0f);
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
		L"../asset/texture/Smoke.jpg",
		nullptr,
		&m_Texture);

	assert(m_Texture);
}

void ParticleObject::Uninit()
{
	for (auto& com : m_Component) {
		com->Uninit();
		delete com;
	}

	m_Component.clear();

	m_VertexBuffer->Release();
	m_Texture->Release();
}

void ParticleObject::Draw()
{		
	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = Color(1.0f, 1.0f, 1.0f, 0.1);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

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

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);		
}

void ParticleObject::Update()
{
	Scene* nowscene = Manager::GetScene();
	Camera* camera = nowscene->GetGameObject<Camera>();

	//��Ƀv���C���[�̕�����������
	//�v���C���[�ւ̃x�N�g�����v�Z
	Vector3 dir = camera->GetPosition() - m_Position;
	m_Rotation.y = atan2(dir.x, dir.z);
	//�p�x������Ă���̂Œ���
	m_Rotation.y -= 60.0f;

	//�p�[�e�B�N���̎���
	if (m_LifeTime > 0)
	{
		m_LifeTime--;		
	}	
}
