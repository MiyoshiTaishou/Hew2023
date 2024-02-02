#include<SimpleMath.h>

#include "Player.h"

//�Ǘ�
#include"../Sysytem/manager.h"

//�V�[��
#include"../Scene/scene.h"

//����
#include"../Sysytem/input.h"

//�R���|�[�l���g
#include"../Component/shader.h"
#include"../Component/SphereCollider.h"
#include"../Component/RigidBody.h"
#include"../Component/shadow.h"
#include"../Component/BoxCollider.h"
#include"../Component/sprite.h"

//�`��
#include"../Render/modelRenderer.h"

//ImGui
#include"../ImGui/ImGuiManager.h"

//�I�u�W�F�N�g
#include"BoxObject.h"
#include"camera.h"
#include"field.h"
#include"TakoyakiObject.h"
#include"FakeTakotaki.h"
#include"Sphere.h"
#include"BillBoardObject.h"

//�p�[�e�B�N��
#include"../Particle/Particle.h"

//UI
#include"../UI/score.h"
#include"../UI/HitUI.h"

using namespace DirectX::SimpleMath;

#define MAX_FILED 20

void Player::Init()
{
	//���W�A�T�C�Y�ݒ�
	this->m_Scale = Vector3(10.0f, 10.0f, 10.f);
	
	AddComponent<Shader>()->Load("../shader\\VS_GouraudShading.cso", "../shader\\PS_OrangeScale.cso");

	ModelRenderer* model = AddComponent<ModelRenderer>();
	//model->Load("../asset\\model\\bullet.obj");
	model->Load("../asset\\model\\bullet.obj");
	
	Shadow* shadow = AddComponent<Shadow>();
	shadow->Init();
	shadow->SetSize(10.0f);

	//�R���|�[�l���g		
	RigidBody* body = AddComponent<RigidBody>();
	body->Init();
	body->SetInetiaTensorOfSpherAngular(5.0f, m_Position);	

	SphereCollider* sphere = AddComponent<SphereCollider>();	
	sphere->SetRadius(2.0f);	

	m_Collider.push_back(sphere);	

	//���[
	m_Point[0] = Vector3(m_Position.x - (m_Scale.x / 2), m_Position.y, m_Position.z);
	//�E�[
	m_Point[1] = Vector3(m_Position.x + (m_Scale.x / 2), m_Position.y, m_Position.z);
	//��
	m_Point[2] = Vector3(m_Position.x, m_Position.y - (m_Scale.y / 2), m_Position.z);
	//��
	m_Point[3] = Vector3(m_Position.x, m_Position.y + (m_Scale.y / 2), m_Position.z);
	//��O
	m_Point[4] = Vector3(m_Position.x, m_Position.y, m_Position.z - (m_Scale.z / 2));
	//��
	m_Point[5] = Vector3(m_Position.x, m_Position.y, m_Position.z + (m_Scale.z / 2));
	//����
	m_Point[6] = (m_Point[0] + m_Point[2]) / 2;
	m_Point[6].x -= m_Distance[6];
	m_Point[6].y -= m_Distance[6];
	//����
	m_Point[7] = (m_Point[0] + m_Point[3]) / 2;
	m_Point[7].x -= m_Distance[7];
	m_Point[7].y += m_Distance[7];
	//����O
	m_Point[8] = (m_Point[0] + m_Point[4]) / 2;
	m_Point[8].x -= m_Distance[8];
	m_Point[8].z -= m_Distance[8];
	//����
	m_Point[9] = (m_Point[0] + m_Point[5]) / 2;
	m_Point[9].x -= m_Distance[9];
	m_Point[9].z += m_Distance[9];
	//�E��
	m_Point[10] = (m_Point[1] + m_Point[2]) / 2;
	m_Point[10].x += m_Distance[10];
	m_Point[10].y -= m_Distance[10];
	//�E��
	m_Point[11] = (m_Point[1] + m_Point[3]) / 2;
	m_Point[11].x += m_Distance[11];
	m_Point[11].y += m_Distance[11];
	//�E��O
	m_Point[12] = (m_Point[1] + m_Point[4]) / 2;
	m_Point[12].x += m_Distance[12];
	m_Point[12].z -= m_Distance[12];
	//�E��
	m_Point[13] = (m_Point[1] + m_Point[5]) / 2;
	m_Point[13].x += m_Distance[13];
	m_Point[13].z += m_Distance[13];
	//���[
	m_Point[0] = Vector3(m_Position.x - (m_Scale.x / 2) - m_Distance[0], m_Position.y, m_Position.z);
	//�E�[
	m_Point[1] = Vector3(m_Position.x + (m_Scale.x / 2) + m_Distance[1], m_Position.y, m_Position.z);
	//��
	m_Point[2] = Vector3(m_Position.x, m_Position.y - (m_Scale.y / 2) - m_Distance[2], m_Position.z);
	//��
	m_Point[3] = Vector3(m_Position.x, m_Position.y + (m_Scale.y / 2) + m_Distance[3], m_Position.z);
	//��O
	m_Point[4] = Vector3(m_Position.x, m_Position.y, m_Position.z - (m_Scale.z / 2) - m_Distance[4]);
	//��
	m_Point[5] = Vector3(m_Position.x, m_Position.y, m_Position.z + (m_Scale.z / 2) + m_Distance[5]);

	for (int i = 0; i < MAX_SPHERE_MESH; i++)
	{
		//���̃��b�V���쐬
		m_Sphere[i] = new CSphereMesh();
		m_Sphere[i]->Init(1.0f, Color(1, 1, 1, 1), 100, 100);

		m_MeshRenderer[i] = new CMeshRenderer();
		m_MeshRenderer[i]->Init(*m_Sphere[i]);		
	}	

	m_Particle = new Particle();
	m_Particle->SetTextureName("../asset/texture/�S���S��.png");

	Scene* scene = Manager::GetScene();

	m_Rotmatrix = Matrix::Identity;

	m_Qtr = true;

	//�����G�t�F�N�g
	m_AccEffect = scene->AddGameObject<GameObject>(Layer2);
	m_AccEffect->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");
	m_AccEffect->AddComponent<Sprite>()->Init(-600.0f * 2.0f, -300.0f * 2.0f, 1280.0f * 3, 720.0f * 3,
		"../asset\\texture\\�_�b�V��.png");
}

void Player::Uninit()
{
	for (int i = 0; i < MAX_SPHERE_MESH; i++)
	{
		delete m_Sphere[i];
		delete m_MeshRenderer[i];
	}	
	
	m_Particle->Uninit();
	delete m_Particle;		
}

void Player::Update()
{	
	//�O�̍��W���c���Ă���
	m_AfterPos = m_Position;

	//�R���|�[�l���g��Update�Ăяo��
	for (auto& cmpt : m_Component) {
		cmpt->Update();
	}
	
	//���W�v�Z
	PointUpdate();

	//�p�[�e�B�N���X�V����
	m_Particle->Update();

	//�����蔻�菈��
	Collision();

	if (m_Controller)
	{
		//�R���g���[���[����
		ConInput();
	}
}
//
void Player::Draw()
{		
#ifdef _DEBUG

	//�v���C���[�̏���\������
	ImGui::Begin("Player");
	ImGui::Text("PlayerScale\n %f\nY %f\nZ %f", this->m_Scale.x, this->m_Scale.y, this->m_Scale.z);
	ImGui::Text("PlayerPos\nX %f\nY %f\nZ %f", this->m_Position.x, this->m_Position.y, this->m_Position.z);
	ImGui::Text("PlayerRot\nX %f\nY %f\nZ %f", this->m_Rotation.x, this->m_Rotation.y, this->m_Rotation.z);
	ImGui::Text("PlayerFow\nX %f\nY %f\nZ %f", this->GetForward().x, this->GetForward().y, this->GetForward().z);
	ImGui::Text("PlayerState\n %d", this->state);
	//�ړ����x
	ImGui::SliderFloat("Speed##", &m_Speed, 0.0f, 300.0f);
	ImGui::SliderFloat("SpeedRot##", &m_RotSpeed, 0.0f, 300.0f);

	//��]
	ImGui::SliderFloat("TorqueX##", &torque.x, -100.0f, 100.0f);
	ImGui::SliderFloat("TorqueY##", &torque.y, -100.0f, 100.0f);
	ImGui::SliderFloat("TorqueZ##", &torque.z, -100.0f, 100.0f);

	//�T�C�Y
	ImGui::SliderFloat("RotX##", &m_Scale.x, 0.0f, 100.0f);
	ImGui::SliderFloat("RotY##", &m_Scale.y, 0.0f, 100.0f);
	ImGui::SliderFloat("RotZ##", &m_Scale.z, 0.0f, 100.0f);

	//�T�C�Y

	for (int i = 0; i < MAX_SPHERE_MESH; ++i) 
	{
		ImGui::SliderFloat(("Distance " + std::to_string(i) + "##").c_str(), &m_Distance[i], 0.0f, 10.0f);
	}	
	
	if (ImGui::Button("Resset"))
	{
		m_Rotation = Vector3(0.0f, 0.0f, 0.0f);
		torque = Vector3(0.0f, 0.0f, 0.0f);
		m_Scale = Vector3(1.0f, 1.0f, 1.0f);
	}

	if (ImGui::Button("SetTensor"))
	{
		RigidBody* body = GetComponent<RigidBody>();

		//�����蔻��̑傫�����I�u�W�F�N�g�ɍ��킹��
		Vector3 absModelScale;
		absModelScale.x = fabsf(ModelRenderer::Max.x) + fabsf(ModelRenderer::Min.x);
		absModelScale.y = fabsf(ModelRenderer::Max.y) + fabsf(ModelRenderer::Min.y);
		absModelScale.z = fabsf(ModelRenderer::Max.z) + fabsf(ModelRenderer::Min.z);

		Vector3 absScale = absModelScale * m_Scale;

		body->SetInetiaTensorOfRectangular(absScale.x, absScale.y, absScale.z, Vector3(0.0f, 0.0f, 0.0f));
	}

	ImGui::End();	

	for (int i = 0; i < MAX_SPHERE_MESH; i++)
	{
		// ���[���h�}�g���N�X�ݒ�
		Matrix world, scale, rot, trans;
		scale = Matrix::CreateScale(1.0);
		rot = Matrix::CreateFromYawPitchRoll(0, 0, 0);
		//rot = m_Rotmatrix;
		trans = Matrix::CreateTranslation(m_Point[i].x, m_Point[i].y, m_Point[i].z);
		world = scale * rot * trans;
		Renderer::SetWorldMatrix(&world);

		m_MeshRenderer[i]->Draw();
	}

#endif // _DEBUG	

	//�p�[�e�B�N���`�揈��
	m_Particle->Draw();
}

void Player::Collision()
{
	// ���݃V�[�����擾
	Scene* scene = Manager::GetScene();	

	//�������I�u�W�F�N�g�����蔻��
	{
		std::vector<TakoyakiObject*> Takoyakilist = scene->GetGameObjects<TakoyakiObject>();
		std::vector<FakeTakoyakiObject*> FakeTakoyakilist = scene->GetGameObjects<FakeTakoyakiObject>();

		
		for (int i = 0; i < m_Collider.size(); i ++)
		{			
			for (const auto& Takoyaki : Takoyakilist)
			{
				if (m_Collider[i]->Hit(Takoyaki->GetComponent<SphereCollider>()))
				{
					//����������
					StickObject* child = AddChild<TakoyakiObject>();
					child->Stick(Takoyaki->GetPosition());

					//�R���C�_�[�ǉ�
					SphereCollider* sphere = AddComponent<SphereCollider>();					
					sphere->SetRadius(2.0f);					

					Vector3 relative = Takoyaki->GetPosition() - m_Position;
					relative.x = fabs(relative.x);
					relative.y = fabs(relative.y);
					relative.z = fabs(relative.z);
					sphere->SetRelative(relative);
					sphere->m_Hitobj = child;
					sphere->m_hit = true;
					m_Collider.push_back(sphere);	

					//��ԋ߂��_�̋��������΂�
					int no = 0;
					float length = 1000;
					for (int j = 0; j < MAX_SPHERE_MESH; j++)
					{						
						Vector3 len = Takoyaki->GetPosition() - m_Point[j];

						//��ԋ߂��_�����ւ���
						if (length > len.Length())
						{
							length = len.Length();
							no = j;
						}					
					}

					m_Distance[no] += 1.0f;

					//�I�u�W�F�N�g�폜
					Takoyaki->SetDestroy();
					Takoyaki->GetComponent<SphereCollider>()->SetCanHit(false);

					//�X�R�A���Z
					Score* score = scene->GetGameObject<Score>();
					score->AddCount(1);
					Manager::AddCount(1);	

					//�q�b�gUI�\��
					std::vector<HitUI*> HitUIList = scene->GetGameObjects<HitUI>();
					int num = rand() % 4;

					HitUIList[num]->Indication();

					state = HIT;
				}
				else
				{
					state = IDLE;
				}
			}		

			for (int i = 0; i < m_Collider.size(); i++)
			{
				for (const auto& Takoyaki : FakeTakoyakilist)
				{
					if (m_Collider[i]->Hit(Takoyaki->GetComponent<SphereCollider>()))
					{
						//����������
						StickObject* child = AddChild<FakeTakoyakiObject>();
						child->Stick(Takoyaki->GetPosition());

						//�R���C�_�[�ǉ�
						SphereCollider* sphere = AddComponent<SphereCollider>();
						sphere->SetRadius(2.0f);
						sphere->SetRelative((Takoyaki->GetPosition() - m_Position));
						sphere->m_Hitobj = child;
						sphere->m_hit = true;
						m_Collider.push_back(sphere);

						//��ԋ߂��_�̋��������΂�
						int no = 0;
						float length = 1000;
						for (int j = 0; j < MAX_SPHERE_MESH; j++)
						{
							Vector3 len = Takoyaki->GetPosition() - m_Point[j];

							//��ԋ߂��_�����ւ���
							if (length > len.Length())
							{
								length = len.Length();
								no = j;
							}
						}

						m_Distance[no] += 1.5f;

						//�I�u�W�F�N�g�폜
						Takoyaki->SetDestroy();
						Takoyaki->GetComponent<SphereCollider>()->SetCanHit(false);

						//�X�R�A���Z
						Score* score = scene->GetGameObject<Score>();
						score->AddCount(1);
						Manager::AddCount(1);

						state = HIT;
					}
					else
					{
						state = IDLE;
					}
				}
			}
		}
	}

	//�ǂƂ̓����蔻��
	{
		std::vector<BoxObject*> boxList = scene->GetGameObjects<BoxObject>();

		for (const auto& box : boxList)
		{
			for (int i = 0; i < MAX_SPHERE_MESH; i++)
			{
				if (box->GetComponent<BoxCollider>()->PointHit(m_Point[i]))
				{
					RigidBody* body = this->GetComponent<RigidBody>();
					Vector3 vel = body->GetVelocity();
					body->AddForce(-vel, ForceMode::Force);
				}
			}
		}
	}
	
	//�������擾	
	Field* filed = scene->GetGameObject<Field>();
	if (!filed)
	{
		return;
	}

	//�@�͈̓`�F�b�N 
	//�@�͈̓`�F�b�N 
	Vector3 max = filed->GetMax();
	Vector3 min = filed->GetMin();

	if (m_Position.x <= min.x + MAX_FILED) {
		m_Position.x = min.x + MAX_FILED;
	}
	if (m_Position.x >= max.x - MAX_FILED) {
		m_Position.x = max.x - MAX_FILED;
	}

	if (m_Position.z <= min.z + MAX_FILED) {
		m_Position.z = min.z + MAX_FILED;
	}
	if (m_Position.z >= max.z - MAX_FILED) {
		m_Position.z = max.z - MAX_FILED;
	}

	filed->PointPlaneCollision(m_Point);
}

//���͏���
void Player::ConInput()
{
	// ���݃V�[�����擾
	Scene* scene = Manager::GetScene();

	Camera* cameraObj = scene->GetGameObject<Camera>();

	RigidBody* body = GetComponent<RigidBody>();

	//�J�����̑O�����x�N�g��
	Vector3 forward = Vector3(0, 0, 0);	
	Vector3 side = Vector3(0, 0, 0);	
	if (cameraObj)
	{
		forward = cameraObj->GetForward();
		//forward *= -1;
		forward.y = 0.0f;
		side = cameraObj->GetSide();
	}

	float yaw = 0.0f;
	float pitch = 0.0f;
	float roll = 0.0f;

	//�p�[�e�B�N���̃|�W�V����
	Vector3 particlePos = m_Position;
	particlePos.y += 5.0f;

	//�O��ړ�
	if (Input::GetGamePad(BUTTON::LUP))
	{						
		//�ړ�����	
		
		Vector3 force = cameraObj->camForward * m_Speed * m_Acc;
		force.y = 0.0f;
		body->AddForce(force, ForceMode::Force);	

		if (m_MoveCount > m_MaxMoveCount)
		{
			m_Particle->Create(particlePos, Vector3(0, -10, 0), Vector3(0, 10, 0), 30.0f, false, 1.0f);
			m_MoveCount = 0;
		}

		m_MoveCount++;
	}
	if (Input::GetGamePad(BUTTON::LDOWN))
	{	
		//��]����	
		
		//�ړ�����	
		Vector3 force = cameraObj->camForward * -m_Speed * m_Acc;
		force.y = 0.0f;
		body->AddForce(force, ForceMode::Force);

		if (m_MoveCount > m_MaxMoveCount)
		{
			m_Particle->Create(particlePos, Vector3(0, -10, 0), Vector3(0, 10, 0), 30.0f, false, 1.0f);
			m_MoveCount = 0;
		}

		m_MoveCount++;
	}

	//���E�ړ�
	if (Input::GetGamePad(BUTTON::LRIGHT))
	{		
		Vector3 force = cameraObj->camRight * -m_Speed * m_Acc;
		body->AddForce(force, ForceMode::Force);	

		if (m_MoveCount > m_MaxMoveCount)
		{
			m_Particle->Create(particlePos, Vector3(0, -10, 0), Vector3(0, 10, 0), 30.0f, false, 1.0f);
			m_MoveCount = 0;
		}

		m_MoveCount++;
	}
	if (Input::GetGamePad(BUTTON::LLEFT))
	{		
		Vector3 force = cameraObj->camRight * m_Speed * m_Acc;
		body->AddForce(force, ForceMode::Force);

		if (m_MoveCount > m_MaxMoveCount)
		{			
			m_Particle->Create(particlePos, Vector3(0,0,0), Vector3(0, 0, 0), 30.0f, false, 1.0f);
			m_MoveCount = 0;
		}

		m_MoveCount++;
	}

	//�J��������
	if (Input::GetGamePad(BUTTON::RRIGHT))
	{		
		cameraObj->theta -= 0.1f;
	}
	if (Input::GetGamePad(BUTTON::RLEFT))
	{	
		cameraObj->theta += 0.1f;
	}
	if (Input::GetGamePad(BUTTON::RUP))
	{		
		cameraObj->phi -= 0.1f;
	}
	if (Input::GetGamePad(BUTTON::RDOWN))
	{		
		cameraObj->phi += 0.1f;
	}

	//�_�b�V������
	if (Input::GetGamePad(BUTTON::ABUTTON))
	{
		m_Acc = 2.0f;

		//�_�b�V�����ɉ������Ă�����G�t�F�N�g����
		if (body->GetVelocity().x > 1.0f || body->GetVelocity().z > 1.0f)
		{
			m_AccEffect->GetComponent<Sprite>()->SetView(true);
		}
	}
	else
	{
		m_Acc = 1.0f;
		m_AccEffect->GetComponent<Sprite>()->SetView(false);
	}

#ifdef _DEBUG

	if (Input::GetKeyTrigger('J'))
	{
		Vector3 force = { 0,50,0 };
		body->AddForce(force, ForceMode::Impulse);
	}

#endif // _DEBUG

	//���x�������������l����]�̒l�ɂ���
	Vector3 vel = body->GetVelocity();
	//yaw = vel.y * 0.1f;
	pitch = vel.z * 0.005f;
	roll = vel.x * -0.005f;

	this->accumulatedRotation *= Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll);
	m_Rotmatrix = Matrix::CreateFromQuaternion(accumulatedRotation);
}

void Player::PointUpdate()
{
	//���[
	m_Point[0] = Vector3(m_Position.x - (m_Scale.x / 2), m_Position.y, m_Position.z);
	//�E�[
	m_Point[1] = Vector3(m_Position.x + (m_Scale.x / 2), m_Position.y, m_Position.z);
	//��
	m_Point[2] = Vector3(m_Position.x, m_Position.y - (m_Scale.y / 2), m_Position.z);
	//��
	m_Point[3] = Vector3(m_Position.x, m_Position.y + (m_Scale.y / 2), m_Position.z);
	//��O
	m_Point[4] = Vector3(m_Position.x, m_Position.y, m_Position.z - (m_Scale.z / 2));
	//��
	m_Point[5] = Vector3(m_Position.x, m_Position.y, m_Position.z + (m_Scale.z / 2));
	//����
	m_Point[6] = (m_Point[0] + m_Point[2]) / 2;
	m_Point[6].x -= m_Distance[6];
	m_Point[6].y -= m_Distance[6];
	//����
	m_Point[7] = (m_Point[0] + m_Point[3]) / 2;
	m_Point[7].x -= m_Distance[7];
	m_Point[7].y += m_Distance[7];
	//����O
	m_Point[8] = (m_Point[0] + m_Point[4]) / 2;
	m_Point[8].x -= m_Distance[8];
	m_Point[8].z -= m_Distance[8];
	//����
	m_Point[9] = (m_Point[0] + m_Point[5]) / 2;
	m_Point[9].x -= m_Distance[9];
	m_Point[9].z += m_Distance[9];
	//�E��
	m_Point[10] = (m_Point[1] + m_Point[2]) / 2;
	m_Point[10].x += m_Distance[10];
	m_Point[10].y -= m_Distance[10];
	//�E��
	m_Point[11] = (m_Point[1] + m_Point[3]) / 2;
	m_Point[11].x += m_Distance[11];
	m_Point[11].y += m_Distance[11];
	//�E��O
	m_Point[12] = (m_Point[1] + m_Point[4]) / 2;
	m_Point[12].x += m_Distance[12];
	m_Point[12].z -= m_Distance[12];
	//�E��
	m_Point[13] = (m_Point[1] + m_Point[5]) / 2;
	m_Point[13].x += m_Distance[13];
	m_Point[13].z += m_Distance[13];
	//���[
	m_Point[0] = Vector3(m_Position.x - (m_Scale.x / 2) - m_Distance[0], m_Position.y, m_Position.z);
	//�E�[
	m_Point[1] = Vector3(m_Position.x + (m_Scale.x / 2) + m_Distance[1], m_Position.y, m_Position.z);
	//��
	m_Point[2] = Vector3(m_Position.x, m_Position.y - (m_Scale.y / 2) - m_Distance[2], m_Position.z);
	//��
	m_Point[3] = Vector3(m_Position.x, m_Position.y + (m_Scale.y / 2) + m_Distance[3], m_Position.z);
	//��O
	m_Point[4] = Vector3(m_Position.x, m_Position.y, m_Position.z - (m_Scale.z / 2) - m_Distance[4]);
	//��
	m_Point[5] = Vector3(m_Position.x, m_Position.y, m_Position.z + (m_Scale.z / 2) + m_Distance[5]);


	// �|�C���g���v���C���[�̉�]�ɍ��킹�ĕϊ�����
	for (int i = 0; i < MAX_SPHERE_MESH; ++i)
	{		
		// �|�C���g���x�N�g���ɕϊ�
		Vector3 point = m_Point[i] - m_Position;

		// �s��ŉ�]������
		Matrix rotationMatrix = m_Rotmatrix;
		Vector3 rotatedVector = Vector3::Transform(point, rotationMatrix);

		// ��]��̃|�C���g���X�V
		m_Point[i] = rotatedVector + m_Position;
	}
}
