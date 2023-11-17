#include "Enemy.h"

//�I�u�W�F�N�g
#include"Player.h"
#include"field.h"
#include"TakoyakiObject.h"

//�V�[��
#include"../Scene/scene.h"

//�R���|�[�l���g
#include"../Component/SphereCollider.h"
#include"../Component/RigidBody.h"
#include"../Component/shader.h"
#include"../Component/animationModel.h"

//�V�X�e��
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

    //���������Ƃ��̏���
    Player* player = scene->GetGameObject<Player>();

    if (GetComponent<SphereCollider>()->Hit(player->GetComponent<SphereCollider>()))
    {        
        //�t����΂�
        Vector3 force = GetForward() * 30.0f;
        player->GetComponent<RigidBody>()->AddForce(force, ForceMode::Impulse);    
    }

    //�n�`�ɉ������ړ�
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
        const float searchAngle = 60.0f; // ���G����p�x�͈́i��F30�x�j

        // �G�̌����i���W�A���P�ʂ̊p�x�j
        float enemyAngleRad = m_Rotation.y * (3.14f / 180.0f);

        // �v���C���[�̈ʒu���擾
        Vector3 playerPos = player->GetPosition();
       
        // �G�̌����ɑ΂��Ẵv���C���[�Ƃ̊p�x���v�Z
        Vector3 dirToPlayer = playerPos - m_Position;
        dirToPlayer.Normalize();
        float angleToPlayerRad = std::atan2(dirToPlayer.x, dirToPlayer.z);

        // ���E��30�x���͈̔͂��v�Z
        float leftAngleRad = enemyAngleRad - (30.0f * (3.14f / 180.0f));
        float rightAngleRad = enemyAngleRad + (30.0f * (3.14f / 180.0f));
       
        // �v���C���[�̊p�x�����E�͈͓̔��ɂ��邩�ǂ������`�F�b�N
        if (angleToPlayerRad >= leftAngleRad && angleToPlayerRad <= rightAngleRad) {
            float distance = Vector3::Distance(playerPos, m_Position);
            if (distance <= m_VisibiltyRange) {
                // ���G�������̏���
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
        //�ǐ�
        Vector3 pos = player->GetPosition();

        //�r���{�[�h����
        Vector3 dir = pos - m_Position;
        m_Rotation.y = atan2(dir.x, dir.z);

        //�����Ă�������Ɉړ�
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
        // Defend���̏���
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
