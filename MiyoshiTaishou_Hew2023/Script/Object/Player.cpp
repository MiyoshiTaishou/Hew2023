#include<SimpleMath.h>

#include "Player.h"

//管理
#include"../Sysytem/manager.h"

//シーン
#include"../Scene/scene.h"

//入力
#include"../Sysytem/input.h"

//コンポーネント
#include"../Component/shader.h"
#include"../Component/SphereCollider.h"
#include"../Component/RigidBody.h"
#include"../Component/shadow.h"

//描画
#include"../Render/modelRenderer.h"

//ImGui
#include"../ImGui/ImGuiManager.h"

//オブジェクト
#include"BoxObject.h"
#include"camera.h"
#include"field.h"
#include"TakoyakiObject.h"
#include"Sphere.h"

//UI
#include"../UI/score.h"

using namespace DirectX::SimpleMath;

void Player::Init()
{
	//座標、サイズ設定
	this->m_Scale = Vector3(10.0f, 10.0f, 10.f);
	//this->m_Scale = Vector3(2.0f, 1.0f, 4.0f);
	this->m_Position.x = 10.0f;
	this->m_Position.z = -10.0f;
	this->m_Position.y = 0.0f;

	//コンポーネント
	AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\vertexLightingPS.cso");
	//AddComponent<Shader>()->Load("../shader\\VS_Object.cso", "../shader\\PS_Toon.cso");
	//AddComponent<Shader>()->Load("../shader\\VS_GouraudShading.cso", "../shader\\PS_OrangeScale.cso");
	//AddComponent<Shader>()->Load("../shader\\VS_Object.cso", "../shader\\PS_Toon.cso");
	

	ModelRenderer* model = AddComponent<ModelRenderer>();
	//model->Load("../asset\\model\\bullet.obj");
	model->Load("../asset\\model\\bullet.obj");

	Shadow* shadow = AddComponent<Shadow>();
	shadow->Init();
	shadow->SetSize(10.0f);
	
	RigidBody* body = AddComponent<RigidBody>();
	body->Init();
	body->SetInetiaTensorOfSpherAngular(5.0f, m_Position);	

	SphereCollider* sphere = AddComponent<SphereCollider>();	
	sphere->SetRadius(2.0f);	

	m_Collider.push_back(sphere);

	

	//左端
	m_Point[0] = Vector3(m_Position.x - (m_Scale.x / 2) - m_Distance[0], m_Position.y, m_Position.z);
	//右端
	m_Point[1] = Vector3(m_Position.x + (m_Scale.x / 2) + m_Distance[1], m_Position.y, m_Position.z);
	//下
	m_Point[2] = Vector3(m_Position.x, m_Position.y - (m_Scale.y / 2) - m_Distance[2], m_Position.z);
	//上
	m_Point[3] = Vector3(m_Position.x, m_Position.y + (m_Scale.y / 2) + m_Distance[3], m_Position.z);
	//手前
	m_Point[4] = Vector3(m_Position.x, m_Position.y, m_Position.z - (m_Scale.z / 2) - m_Distance[4]);
	//奥
	m_Point[5] = Vector3(m_Position.x, m_Position.y, m_Position.z + (m_Scale.z / 2) + m_Distance[5]);

	for (int i = 0; i < 6; i++)
	{
		//球のメッシュ作成
		m_Sphere[i] = new CSphereMesh();
		m_Sphere[i]->Init(1.0f, Color(1, 1, 1, 1), 100, 100);

		m_MeshRenderer[i] = new CMeshRenderer();
		m_MeshRenderer[i]->Init(*m_Sphere[i]);
	}	

	//body->SetInetiaTensorOfRectangular(absScale.x, absScale.y, absScale.z, Vector3(0.0f, 0.0f, 0.0f));
}

void Player::Uninit()
{
	for (int i = 0; i < 6; i++)
	{
		delete m_Sphere[i];
		delete m_MeshRenderer[i];
	}
}

void Player::Update()
{	
	//当たり判定処理
	Collision();

	//コントローラー入力
	ConInput();

	//コンポーネントのUpdate呼び出し
	for (auto& cmpt : m_Component) {
		cmpt->Update();
	}

	GetComponent<RigidBody>()->AddTorque(torque, ForceMode::Force);

	//左端
	m_Point[0] = Vector3(m_Position.x - (m_Scale.x / 2) - m_Distance[0], m_Position.y, m_Position.z);
	//右端
	m_Point[1] = Vector3(m_Position.x + (m_Scale.x / 2) + m_Distance[1], m_Position.y, m_Position.z);
	//下
	m_Point[2] = Vector3(m_Position.x, m_Position.y - (m_Scale.y / 2) - m_Distance[2], m_Position.z);
	//上
	m_Point[3] = Vector3(m_Position.x, m_Position.y + (m_Scale.y / 2) + m_Distance[3], m_Position.z);
	//手前
	m_Point[4] = Vector3(m_Position.x, m_Position.y, m_Position.z - (m_Scale.z / 2) - m_Distance[4]);
	//奥
	m_Point[5] = Vector3(m_Position.x, m_Position.y, m_Position.z + (m_Scale.z / 2) + m_Distance[5]);	

	// ポイントをプレイヤーの回転に合わせて変換する
	for (int i = 0; i < 6; ++i) {
		// ポイントをベクトルに変換
		Vector3 point = m_Point[i];

		point -= m_Position;

		// ポイントを行列で回転させる
		Matrix rotationMatrix = this->GetRotMatrix();
		Vector3 rotatedVector;
		rotatedVector.x = rotationMatrix._11 * point.x + rotationMatrix._12 * point.y + rotationMatrix._13 * point.z;
		rotatedVector.y = rotationMatrix._21 * point.x + rotationMatrix._22 * point.y + rotationMatrix._23 * point.z;
		rotatedVector.z = rotationMatrix._31 * point.x + rotationMatrix._32 * point.y + rotationMatrix._33 * point.z;
		
		rotatedVector += m_Position;
		// 回転後のポイントを更新
		m_Point[i] = rotatedVector;
	}
}

void Player::Draw()
{
	//プレイヤーの情報を表示する
	ImGui::Begin("Player");
	ImGui::Text("PlayerScale\n %f\nY %f\nZ %f", this->m_Scale.x, this->m_Scale.y, this->m_Scale.z);
	ImGui::Text("PlayerPos\nX %f\nY %f\nZ %f", this->m_Position.x, this->m_Position.y, this->m_Position.z);
	ImGui::Text("PlayerRot\nX %f\nY %f\nZ %f", this->m_Rotation.x, this->m_Rotation.y, this->m_Rotation.z);
	ImGui::Text("PlayerFow\nX %f\nY %f\nZ %f", this->GetForward().x, this->GetForward().y, this->GetForward().z);
	ImGui::Text("PlayerState\n %d", this->state);
	//移動速度
	ImGui::SliderFloat("Speed##", &m_Speed, 0.0f, 300.0f);
	ImGui::SliderFloat("SpeedRot##", &m_RotSpeed, 0.0f, 300.0f);

	//回転
	ImGui::SliderFloat("TorqueX##", &torque.x, -100.0f, 100.0f);
	ImGui::SliderFloat("TorqueY##", &torque.y, -100.0f, 100.0f);
	ImGui::SliderFloat("TorqueZ##", &torque.z, -100.0f, 100.0f);

	//サイズ
	ImGui::SliderFloat("RotX##", &m_Scale.x, 0.0f, 100.0f);
	ImGui::SliderFloat("RotY##", &m_Scale.y, 0.0f, 100.0f);
	ImGui::SliderFloat("RotZ##", &m_Scale.z, 0.0f, 100.0f);

	//サイズ
	ImGui::SliderFloat("Left##", &m_Distance[0], 0.0f, 10.0f);
	ImGui::SliderFloat("Right##", &m_Distance[1], 0.0f, 10.0f);
	ImGui::SliderFloat("Down##", &m_Distance[2], 0.0f, 10.0f);
	ImGui::SliderFloat("Up##", &m_Distance[3], 0.0f, 10.0f);
	ImGui::SliderFloat("Front##", &m_Distance[4], 0.0f, 10.0f);
	ImGui::SliderFloat("Back##", &m_Distance[5], 0.0f, 10.0f);
	
	if (ImGui::Button("Resset"))
	{
		m_Rotation = Vector3(0.0f, 0.0f, 0.0f);
		torque = Vector3(0.0f, 0.0f, 0.0f);
		m_Scale = Vector3(1.0f, 1.0f, 1.0f);
	}

	if (ImGui::Button("SetTensor"))
	{
		RigidBody* body = GetComponent<RigidBody>();

		//当たり判定の大きさをオブジェクトに合わせる
		Vector3 absModelScale;
		absModelScale.x = fabsf(ModelRenderer::Max.x) + fabsf(ModelRenderer::Min.x);
		absModelScale.y = fabsf(ModelRenderer::Max.y) + fabsf(ModelRenderer::Min.y);
		absModelScale.z = fabsf(ModelRenderer::Max.z) + fabsf(ModelRenderer::Min.z);

		Vector3 absScale = absModelScale * m_Scale;

		body->SetInetiaTensorOfRectangular(absScale.x, absScale.y, absScale.z, Vector3(0.0f, 0.0f, 0.0f));
	}

	ImGui::End();	

	for (int i = 0; i < 6; i++)
	{
		// ワールドマトリクス設定
		Matrix world, scale, rot, trans;
		scale = Matrix::CreateScale(1.0f);
		rot = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
		trans = Matrix::CreateTranslation(m_Point[i].x, m_Point[i].y, m_Point[i].z);
		world = scale * rot * trans;
		Renderer::SetWorldMatrix(&world);

		m_MeshRenderer[i]->Draw();
	}	

	//m_MeshRenderer->Draw();	
}

void Player::Collision()
{
	// 現在シーンを取得
	Scene* scene = Manager::GetScene();	

	//くっつくオブジェクト当たり判定
	{
		std::vector<TakoyakiObject*> Takoyakilist = scene->GetGameObjects<TakoyakiObject>();

		
		for (int i = 0; i < m_Collider.size(); i ++)
		{			
			for (const auto& Takoyaki : Takoyakilist)
			{
				if (m_Collider[i]->Hit(Takoyaki->GetComponent<SphereCollider>()))
				{
					//くっつく処理
					StickObject* child = AddChild<TakoyakiObject>();
					child->Stick(Takoyaki->GetPosition());

					//コライダー追加
					SphereCollider* sphere = AddComponent<SphereCollider>();					
					sphere->SetRadius(2.0f);					
					sphere->SetRelative((Takoyaki->GetPosition() - m_Position));
					sphere->m_Hitobj = child;
					sphere->m_hit = true;
					m_Collider.push_back(sphere);					

					//オブジェクト削除
					Takoyaki->SetDestroy();
					Takoyaki->GetComponent<SphereCollider>()->SetCanHit(false);

					//スコア加算
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
	
	//高さを取得	
	Field* filed = scene->GetGameObject<Field>();
	if (!filed)
	{
		return;
	}

	//　範囲チェック 
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

	////今一番低い位置にいるコライダーの高さに合わせる
	//Vector3 underPos = m_Position;
	//float underRelative = 0.0f;
	//for (int i = 0; i < m_Collider.size(); i++)
	//{
	//	Vector3 collPos = m_Collider[i]->GetPos();		

	//	//小さい
	//	if (underPos.y > collPos.y)
	//	{
	//		underPos = collPos;
	//		underRelative = m_Collider[i]->GetRelative().y;
	//	}
	//}

	////float Height = filed->GetFieldHeightBySqno(underPos,*this);
	//float Height = filed->GetFieldHeightBySqno(m_Position,*this);
	//
	////float Height = 0.0f;

	//// 位置が０以下なら地面位置にセットする
	//if ((m_Position.y - 2)  < Height)
	//{
	//	////速度を0にする
	//	//RigidBody* body = GetComponent<RigidBody>();
	//	//Vector3 vel = body->GetVelocity();	
	//	//Vector3 force = { 0,-(vel.y / 2),0 };
	//	//vel.y = 0.0f;		
	//	//body->SetVelocity(vel);		

	//	
	//	//m_Position.y = Height +  fabsf(underRelative) + 2.0f;
	//	m_Position.y = Height + 2.0f;

	//	////バウンドする
	//	//if (force.y > 10.0f)
	//	//{
	//	//	body->AddForce(force, ForceMode::Impulse);
	//	//}
	//}

	for (int i = 0; i < 5; i++)
	{
		filed->PointPlaneCollision(m_Point[i]);
	}	
}

//入力処理
void Player::ConInput()
{
	// 現在シーンを取得
	Scene* scene = Manager::GetScene();

	Camera* cameraObj = scene->GetGameObject<Camera>();

	RigidBody* body = GetComponent<RigidBody>();

	//カメラの前向きベクトル
	Vector3 forward = Vector3(0, 0, 0);	
	if (cameraObj)
	{
		forward = cameraObj->GetForward();
	}

	if (Input::GetGamePad(BUTTON::LUP)  && Input::GetGamePad(BUTTON::RUP))
	{
		Vector3 force = forward * m_Speed;
		Vector3 forceRot = forward * m_RotSpeed;
		forceRot.y = 0.0f;
		forceRot.z = 0.0f;
		forceRot.x = m_RotSpeed;

		//body->AddForceToPoint(force, Vector3(1.0f, 0.0f, 0.0f), ForceMode::Force);

		body->AddForce(force, ForceMode::Force);
		body->AddTorque(forceRot, ForceMode::Force);
	}
	if (Input::GetGamePad(BUTTON::LDOWN) && Input::GetGamePad(BUTTON::RDOWN))
	{
		Vector3 force = forward * -m_Speed;
		Vector3 forceRot = forward * -m_RotSpeed;
		forceRot.y = 0.0f;
		forceRot.z = 0.0f;
		forceRot.x = -m_RotSpeed;

		body->AddForce(force, ForceMode::Force);
		body->AddTorque(forceRot, ForceMode::Force);
	}
	/*if (Input::GetGamePad(BUTTON::LLEFT))
	{
		m_Position.x -= 0.1f;
	}
	if (Input::GetGamePad(BUTTON::LRIGHT))
	{
		m_Position.x += 0.1f;
	}*/

	if (Input::GetGamePad(BUTTON::RDOWN) && Input::GetGamePad(BUTTON::LUP))
	{
		m_Rotation.y += 0.05f;
	}
	if (Input::GetGamePad(BUTTON::RUP) && Input::GetGamePad(BUTTON::LDOWN))
	{
		m_Rotation.y -= 0.05f;
	}

	if (Input::GetKeyTrigger('J'))
	{
		Vector3 force = { 0,50,0 };
		body->AddForce(force, ForceMode::Impulse);
	}
}
