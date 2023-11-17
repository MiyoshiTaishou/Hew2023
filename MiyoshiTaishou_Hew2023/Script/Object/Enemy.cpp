#include "Enemy.h"

//オブジェクト
#include"Player.h"
#include"field.h"
#include"TakoyakiObject.h"

//シーン
#include"../Scene/scene.h"

//コンポーネント
#include"../Component/SphereCollider.h"
#include"../Component/RigidBody.h"
#include"../Component/shader.h"
#include"../Component/animationModel.h"

//システム
#include"../Sysytem/manager.h"

using namespace DirectX::SimpleMath;

void Enemy::Init()
{
    AddComponent<Shader>()->Load("../shader\\vertexLightingOneSkinVS.cso", "../shader\\vertexLightingPS.cso"); //20230909-02

    m_Model = AddComponent<AnimationModel>();

    m_Model->Load("../asset\\model\\Akai.fbx");									// animation ok
    m_Model->LoadAnimation("../asset\\model\\Akai_Idle.fbx", "Idle");
    m_Model->LoadAnimation("../asset\\model\\Akai_Run.fbx", "Run");

    InitializeStateFunctions();
    AddComponent<SphereCollider>()->SetRadius(2.0f);
    AddComponent<RigidBody>();

    m_Scale = Vector3(0.1f, 0.1f, 0.1f);
    m_Position.x = 30.0f;   
}

void Enemy::Update()
{
    ExecuteStateFunction(m_State);

    Scene* scene = Manager::GetScene();

    //当たったときの処理
    Player* player = scene->GetGameObject<Player>();

    if (GetComponent<SphereCollider>()->Hit(player->GetComponent<SphereCollider>()))
    {        
        //付き飛ばす
        Vector3 force = GetForward() * 30.0f;
        player->GetComponent<RigidBody>()->AddForce(force, ForceMode::Impulse);    
    }

    //地形に沿った移動
    Field* field = scene->GetGameObject<Field>();
    if (!field)
    {
        return;
    }

    float hight = field->GetFieldHeightBySqno(m_Position, true);
    m_Position.y = hight;
}

void Enemy::Draw()
{
}

void Enemy::PreDraw()
{
    m_Model->Update("Idle", m_Frame, "Run", m_Frame, m_BlendRate);
}

void Enemy::InitializeStateFunctions()
{
    Scene* scene = Manager::GetScene();
    Player* player = scene->GetGameObject<Player>();   

    m_StateFunctions[EnemyState::Idle] = [player,this]()
    {        
        const float searchAngle = 60.0f; // 索敵する角度範囲（例：30度）

        // 敵の向き（ラジアン単位の角度）
        float enemyAngleRad = m_Rotation.y * (3.14f / 180.0f);

        // プレイヤーの位置を取得
        Vector3 playerPos = player->GetPosition();
       
        // 敵の向きに対してのプレイヤーとの角度を計算
        Vector3 dirToPlayer = playerPos - m_Position;
        dirToPlayer.Normalize();
        float angleToPlayerRad = std::atan2(dirToPlayer.x, dirToPlayer.z);

        // 左右に30度ずつの範囲を計算
        float leftAngleRad = enemyAngleRad - (30.0f * (3.14f / 180.0f));
        float rightAngleRad = enemyAngleRad + (30.0f * (3.14f / 180.0f));
       
        // プレイヤーの角度が左右の範囲内にあるかどうかをチェック
        if (angleToPlayerRad >= leftAngleRad && angleToPlayerRad <= rightAngleRad) {
            float distance = Vector3::Distance(playerPos, m_Position);
            if (distance <= m_VisibiltyRange) {
                // 索敵成功時の処理
                m_State = EnemyState::Attack;
            }
        }
        else
        {
            m_Rotation.y += 0.01f;
        }

        m_Frame--;

        m_BlendRate -= 0.1f;

        if (m_BlendRate < 0.0f)
        {
            m_BlendRate = 0.0f;
        }      
    };

    m_StateFunctions[EnemyState::Attack] = [player, this]()
    {     
        //追跡
        Vector3 pos = player->GetPosition();

        //ビルボード処理
        Vector3 dir = pos - m_Position;
        m_Rotation.y = atan2(dir.x, dir.z);

        //向いている方向に移動
        dir.Normalize();
        dir *= m_Speed;
        GetComponent<RigidBody>()->AddForce(dir, ForceMode::Force);

        m_Frame++;

        m_BlendRate += 0.1f;

        if (m_BlendRate > 1.0f)
        {
            m_BlendRate = 1.0f;
        }
       
        float distance = Vector3::Distance(pos, m_Position);
        if (distance >= m_VisibiltyRange)
        {
            m_State = EnemyState::Idle;
        }       
    };

    m_StateFunctions[EnemyState::Defend] = []()
    {
        // Defend時の処理
        std::cout << "Defend state function\n";
    };
}

void Enemy::ExecuteStateFunction(EnemyState currentState)
{
    if (m_StateFunctions.find(currentState) != m_StateFunctions.end()) {
        m_StateFunctions[currentState]();
    }
    else {
        std::cout << "Function for the current state not found\n";
    }
}
