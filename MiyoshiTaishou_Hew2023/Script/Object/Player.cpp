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
#include"../Component/BoxCollider.h"
#include"../Component/sprite.h"

//描画
#include"../Render/modelRenderer.h"

//ImGui
#include"../ImGui/ImGuiManager.h"

//オブジェクト
#include"BoxObject.h"
#include"camera.h"
#include"field.h"
#include"TakoyakiObject.h"
#include"FakeTakotaki.h"
#include"Sphere.h"
#include"BillBoardObject.h"

//パーティクル
#include"../Particle/Particle.h"

//UI
#include"../UI/score.h"
#include"../UI/HitUI.h"

using namespace DirectX::SimpleMath;

#define MAX_FILED 20

void Player::Init()
{
	//座標、サイズ設定
	this->m_Scale = Vector3(10.0f, 10.0f, 10.f);
	
	AddComponent<Shader>()->Load("../shader\\VS_GouraudShading.cso", "../shader\\PS_OrangeScale.cso");

	ModelRenderer* model = AddComponent<ModelRenderer>();
	//model->Load("../asset\\model\\bullet.obj");
	model->Load("../asset\\model\\bullet.obj");
	
	Shadow* shadow = AddComponent<Shadow>();
	shadow->Init();
	shadow->SetSize(10.0f);

	//コンポーネント		
	RigidBody* body = AddComponent<RigidBody>();
	body->Init();
	body->SetInetiaTensorOfSpherAngular(5.0f, m_Position);	

	SphereCollider* sphere = AddComponent<SphereCollider>();	
	sphere->SetRadius(2.0f);	

	m_Collider.push_back(sphere);	

	//左端
	m_Point[0] = Vector3(m_Position.x - (m_Scale.x / 2), m_Position.y, m_Position.z);
	//右端
	m_Point[1] = Vector3(m_Position.x + (m_Scale.x / 2), m_Position.y, m_Position.z);
	//下
	m_Point[2] = Vector3(m_Position.x, m_Position.y - (m_Scale.y / 2), m_Position.z);
	//上
	m_Point[3] = Vector3(m_Position.x, m_Position.y + (m_Scale.y / 2), m_Position.z);
	//手前
	m_Point[4] = Vector3(m_Position.x, m_Position.y, m_Position.z - (m_Scale.z / 2));
	//奥
	m_Point[5] = Vector3(m_Position.x, m_Position.y, m_Position.z + (m_Scale.z / 2));
	//左下
	m_Point[6] = (m_Point[0] + m_Point[2]) / 2;
	m_Point[6].x -= m_Distance[6];
	m_Point[6].y -= m_Distance[6];
	//左上
	m_Point[7] = (m_Point[0] + m_Point[3]) / 2;
	m_Point[7].x -= m_Distance[7];
	m_Point[7].y += m_Distance[7];
	//左手前
	m_Point[8] = (m_Point[0] + m_Point[4]) / 2;
	m_Point[8].x -= m_Distance[8];
	m_Point[8].z -= m_Distance[8];
	//左奥
	m_Point[9] = (m_Point[0] + m_Point[5]) / 2;
	m_Point[9].x -= m_Distance[9];
	m_Point[9].z += m_Distance[9];
	//右下
	m_Point[10] = (m_Point[1] + m_Point[2]) / 2;
	m_Point[10].x += m_Distance[10];
	m_Point[10].y -= m_Distance[10];
	//右上
	m_Point[11] = (m_Point[1] + m_Point[3]) / 2;
	m_Point[11].x += m_Distance[11];
	m_Point[11].y += m_Distance[11];
	//右手前
	m_Point[12] = (m_Point[1] + m_Point[4]) / 2;
	m_Point[12].x += m_Distance[12];
	m_Point[12].z -= m_Distance[12];
	//右奥
	m_Point[13] = (m_Point[1] + m_Point[5]) / 2;
	m_Point[13].x += m_Distance[13];
	m_Point[13].z += m_Distance[13];
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

	for (int i = 0; i < MAX_SPHERE_MESH; i++)
	{
		//球のメッシュ作成
		m_Sphere[i] = new CSphereMesh();
		m_Sphere[i]->Init(1.0f, Color(1, 1, 1, 1), 100, 100);

		m_MeshRenderer[i] = new CMeshRenderer();
		m_MeshRenderer[i]->Init(*m_Sphere[i]);		
	}	

	m_Particle = new Particle();
	m_Particle->SetTextureName("../asset/texture/ゴロゴロ.png");

	Scene* scene = Manager::GetScene();

	m_Rotmatrix = Matrix::Identity;

	m_Qtr = true;

	//加速エフェクト
	m_AccEffect = scene->AddGameObject<GameObject>(Layer2);
	m_AccEffect->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");
	m_AccEffect->AddComponent<Sprite>()->Init(-600.0f * 2.0f, -300.0f * 2.0f, 1280.0f * 3, 720.0f * 3,
		"../asset\\texture\\ダッシュ.png");
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
	//前の座標を残しておく
	m_AfterPos = m_Position;

	//コンポーネントのUpdate呼び出し
	for (auto& cmpt : m_Component) {
		cmpt->Update();
	}
	
	//座標計算
	PointUpdate();

	//パーティクル更新処理
	m_Particle->Update();

	//当たり判定処理
	Collision();

	if (m_Controller)
	{
		//コントローラー入力
		ConInput();
	}
}
//
void Player::Draw()
{		
#ifdef _DEBUG

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

		//当たり判定の大きさをオブジェクトに合わせる
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
		// ワールドマトリクス設定
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

	//パーティクル描画処理
	m_Particle->Draw();
}

void Player::Collision()
{
	// 現在シーンを取得
	Scene* scene = Manager::GetScene();	

	//くっつくオブジェクト当たり判定
	{
		std::vector<TakoyakiObject*> Takoyakilist = scene->GetGameObjects<TakoyakiObject>();
		std::vector<FakeTakoyakiObject*> FakeTakoyakilist = scene->GetGameObjects<FakeTakoyakiObject>();

		
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

					Vector3 relative = Takoyaki->GetPosition() - m_Position;
					relative.x = fabs(relative.x);
					relative.y = fabs(relative.y);
					relative.z = fabs(relative.z);
					sphere->SetRelative(relative);
					sphere->m_Hitobj = child;
					sphere->m_hit = true;
					m_Collider.push_back(sphere);	

					//一番近い点の距離を延ばす
					int no = 0;
					float length = 1000;
					for (int j = 0; j < MAX_SPHERE_MESH; j++)
					{						
						Vector3 len = Takoyaki->GetPosition() - m_Point[j];

						//一番近い点を入れ替える
						if (length > len.Length())
						{
							length = len.Length();
							no = j;
						}					
					}

					m_Distance[no] += 1.0f;

					//オブジェクト削除
					Takoyaki->SetDestroy();
					Takoyaki->GetComponent<SphereCollider>()->SetCanHit(false);

					//スコア加算
					Score* score = scene->GetGameObject<Score>();
					score->AddCount(1);
					Manager::AddCount(1);	

					//ヒットUI表示
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
						//くっつく処理
						StickObject* child = AddChild<FakeTakoyakiObject>();
						child->Stick(Takoyaki->GetPosition());

						//コライダー追加
						SphereCollider* sphere = AddComponent<SphereCollider>();
						sphere->SetRadius(2.0f);
						sphere->SetRelative((Takoyaki->GetPosition() - m_Position));
						sphere->m_Hitobj = child;
						sphere->m_hit = true;
						m_Collider.push_back(sphere);

						//一番近い点の距離を延ばす
						int no = 0;
						float length = 1000;
						for (int j = 0; j < MAX_SPHERE_MESH; j++)
						{
							Vector3 len = Takoyaki->GetPosition() - m_Point[j];

							//一番近い点を入れ替える
							if (length > len.Length())
							{
								length = len.Length();
								no = j;
							}
						}

						m_Distance[no] += 1.5f;

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
	}

	//壁との当たり判定
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
	
	//高さを取得	
	Field* filed = scene->GetGameObject<Field>();
	if (!filed)
	{
		return;
	}

	//　範囲チェック 
	//　範囲チェック 
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

//入力処理
void Player::ConInput()
{
	// 現在シーンを取得
	Scene* scene = Manager::GetScene();

	Camera* cameraObj = scene->GetGameObject<Camera>();

	RigidBody* body = GetComponent<RigidBody>();

	//カメラの前向きベクトル
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

	//パーティクルのポジション
	Vector3 particlePos = m_Position;
	particlePos.y += 5.0f;

	//前後移動
	if (Input::GetGamePad(BUTTON::LUP))
	{						
		//移動処理	
		
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
		//回転処理	
		
		//移動処理	
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

	//左右移動
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

	//カメラ操作
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

	//ダッシュ処理
	if (Input::GetGamePad(BUTTON::ABUTTON))
	{
		m_Acc = 2.0f;

		//ダッシュ中に加速していたらエフェクト発生
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

	//速度を小さくした値を回転の値にする
	Vector3 vel = body->GetVelocity();
	//yaw = vel.y * 0.1f;
	pitch = vel.z * 0.005f;
	roll = vel.x * -0.005f;

	this->accumulatedRotation *= Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll);
	m_Rotmatrix = Matrix::CreateFromQuaternion(accumulatedRotation);
}

void Player::PointUpdate()
{
	//左端
	m_Point[0] = Vector3(m_Position.x - (m_Scale.x / 2), m_Position.y, m_Position.z);
	//右端
	m_Point[1] = Vector3(m_Position.x + (m_Scale.x / 2), m_Position.y, m_Position.z);
	//下
	m_Point[2] = Vector3(m_Position.x, m_Position.y - (m_Scale.y / 2), m_Position.z);
	//上
	m_Point[3] = Vector3(m_Position.x, m_Position.y + (m_Scale.y / 2), m_Position.z);
	//手前
	m_Point[4] = Vector3(m_Position.x, m_Position.y, m_Position.z - (m_Scale.z / 2));
	//奥
	m_Point[5] = Vector3(m_Position.x, m_Position.y, m_Position.z + (m_Scale.z / 2));
	//左下
	m_Point[6] = (m_Point[0] + m_Point[2]) / 2;
	m_Point[6].x -= m_Distance[6];
	m_Point[6].y -= m_Distance[6];
	//左上
	m_Point[7] = (m_Point[0] + m_Point[3]) / 2;
	m_Point[7].x -= m_Distance[7];
	m_Point[7].y += m_Distance[7];
	//左手前
	m_Point[8] = (m_Point[0] + m_Point[4]) / 2;
	m_Point[8].x -= m_Distance[8];
	m_Point[8].z -= m_Distance[8];
	//左奥
	m_Point[9] = (m_Point[0] + m_Point[5]) / 2;
	m_Point[9].x -= m_Distance[9];
	m_Point[9].z += m_Distance[9];
	//右下
	m_Point[10] = (m_Point[1] + m_Point[2]) / 2;
	m_Point[10].x += m_Distance[10];
	m_Point[10].y -= m_Distance[10];
	//右上
	m_Point[11] = (m_Point[1] + m_Point[3]) / 2;
	m_Point[11].x += m_Distance[11];
	m_Point[11].y += m_Distance[11];
	//右手前
	m_Point[12] = (m_Point[1] + m_Point[4]) / 2;
	m_Point[12].x += m_Distance[12];
	m_Point[12].z -= m_Distance[12];
	//右奥
	m_Point[13] = (m_Point[1] + m_Point[5]) / 2;
	m_Point[13].x += m_Distance[13];
	m_Point[13].z += m_Distance[13];
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
	for (int i = 0; i < MAX_SPHERE_MESH; ++i)
	{		
		// ポイントをベクトルに変換
		Vector3 point = m_Point[i] - m_Position;

		// 行列で回転させる
		Matrix rotationMatrix = m_Rotmatrix;
		Vector3 rotatedVector = Vector3::Transform(point, rotationMatrix);

		// 回転後のポイントを更新
		m_Point[i] = rotatedVector + m_Position;
	}
}
