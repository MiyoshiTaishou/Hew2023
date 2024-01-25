#include "RootChaise.h"
#include"../ImGui/ImGuiManager.h"
#include"../Object/gameObject.h"

#include"../Sysytem/manager.h"
#include"../Scene/scene.h"
#include"../Object/field.h"

#include <fstream> // �t�@�C������p�̃w�b�_�[

using namespace DirectX::SimpleMath;

void RootChaise::Init()
{
    for (int i = 0; i < MAX_BEJIE; i++)
    {
        //���̃��b�V���ǉ�  
        m_Sphere[i] = new CSphereMesh();
        m_Sphere[i]->Init(2.0f, Color(1, 1, 1, 1), 100, 100);

        m_MeshRenderer[i] = new CMeshRenderer();
        m_MeshRenderer[i]->Init(*m_Sphere[i]);

        m_SpherePos[i].x = i * 10;
    }  

    //particle = new Particle();
    Scene* scne = Manager::GetScene();
    //scne->m_Particle.push_back(particle);
    //particle->Init();


    //�t�@�C�����烋�[�g���ǂݍ���
    std::ifstream inputFile(m_buffer);
    if (inputFile.is_open())
    {
        std::string line;
        while (getline(inputFile, line))
        {
            size_t pos = line.find(",");
            if (pos != std::string::npos)
            {
                std::string label = line.substr(0, pos);
                std::string valueStr = line.substr(pos + 1);

                // �C���f�b�N�X�̌��o�ƒl�̉��
                int posIndex = std::stoi(label.substr(4, 1));
                float value = std::stof(valueStr);

                // ���x���̎�ނɊ�Â��� m_SpherePos ���X�V
                if (label.find("PosX") != std::string::npos)
                {
                    m_SpherePos[posIndex].x = value;
                }
                else if (label.find("PosY") != std::string::npos)
                {
                    m_SpherePos[posIndex].y = value;
                }
                else if (label.find("PosZ") != std::string::npos)
                {
                    m_SpherePos[posIndex].z = value;
                }
            }
        }
        inputFile.close();
    }
}

void RootChaise::Uninit()
{
    for (int i = 0; i < MAX_BEJIE; i++)
    {
        delete m_Sphere[i];
        m_Sphere[i] = nullptr;

        delete m_MeshRenderer[i];
        m_MeshRenderer[i] = nullptr;
    }  

    //particle->Uninit();
}

void RootChaise::Draw()
{   
#if DEBUG

    for (int i = 0; i < MAX_BEJIE; i++)
    {
        // ���[���h�ϊ��s�񐶐�
        // �}�g���N�X�ݒ�
        Matrix world, scale, trans;
        scale = DirectX::SimpleMath::Matrix::CreateScale(Vector3(1.0f, 1.0f, 1.0f));
        trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_SpherePos[i].x, m_SpherePos[i].y, m_SpherePos[i].z);
        world = scale * trans;

        // GPU�ɍs����Z�b�g����
        Renderer::SetWorldMatrix(&world);//�ʒu

        m_MeshRenderer[i]->Draw();
    }

    ImGui::Begin("Collider");

    if (ImGui::Button("Save Values"))
    {
        std::ofstream outputFile(m_buffer); // �t�@�C�����쐬�܂��͏㏑��
        if (outputFile.is_open())
        {
            for (int i = 0; i < 4; i++)
            {
                outputFile << "PosX" << i << "," << m_SpherePos[i].x << "\n";
                outputFile << "PosY" << i << "," << m_SpherePos[i].y << "\n";
                outputFile << "PosZ" << i << "," << m_SpherePos[i].z << "\n";
            }
            outputFile.close();
        }
    }    

    if (ImGui::Button("Load Value"))
    {
        std::ifstream inputFile(m_buffer);
        if (inputFile.is_open())
        {
            std::string line;
            while (getline(inputFile, line))
            {
                size_t pos = line.find(",");
                if (pos != std::string::npos)
                {
                    std::string label = line.substr(0, pos);
                    std::string valueStr = line.substr(pos + 1);

                    // �C���f�b�N�X�̌��o�ƒl�̉��
                    int posIndex = std::stoi(label.substr(4, 1));
                    float value = std::stof(valueStr);

                    // ���x���̎�ނɊ�Â��� m_SpherePos ���X�V
                    if (label.find("PosX") != std::string::npos)
                    {
                        m_SpherePos[posIndex].x = value;
                    }
                    else if (label.find("PosY") != std::string::npos)
                    {
                        m_SpherePos[posIndex].y = value;
                    }
                    else if (label.find("PosZ") != std::string::npos)
                    {
                        m_SpherePos[posIndex].z = value;
                    }
                }
            }
            inputFile.close();
        }
    }

    for (int i = 0; i < 4; i++)
    {
        ImGui::SliderFloat(("PosX" + std::to_string(i)).c_str(), &m_SpherePos[i].x, -1000, 1000);
        ImGui::SliderFloat(("PosY" + std::to_string(i)).c_str(), &m_SpherePos[i].y, -1000, 1000);
        ImGui::SliderFloat(("PosZ" + std::to_string(i)).c_str(), &m_SpherePos[i].z, -1000, 1000);
    }    

    // std::string��char�^�̃o�b�t�@�ɃR�s�[
    //strcpy_s(m_buffer, m_GameObject->GetFileName().c_str());    
    ImGui::InputText("File Name", m_buffer, sizeof(m_buffer));    
   
    ImGui::End();

#endif // DEBUG
    //particle->Draw();
}

void RootChaise::Update()
{    
    //�������Č�������悤�Ȓl�̌v�Z
    float move;
    move = (-2 * (m_Rate * m_Rate * m_Rate)) + (3 * (m_Rate * m_Rate));
    //move = (-1 * (m_Rate * m_Rate)) + (2 * m_Rate);

    //����
    if (m_Rate > 1.0f)
    {
        m_Goal = true;
    }
    else if(m_Rate < 0) 
    {
        m_Goal = false;
    }

    if (m_Goal)
    {
        //���Z
        m_Rate -= m_MoveSpeed;
    }
    else
    {
        //���Z
        m_Rate += m_MoveSpeed;
    }


    //�J�n�ʒu����[2]�̈ʒu�܂ł�lerp
    m_SpherePos[4] = Vector3::Lerp(m_SpherePos[0], m_SpherePos[1], move);    
    m_SpherePos[5] = Vector3::Lerp(m_SpherePos[1], m_SpherePos[2], move);    
    m_SpherePos[6] = Vector3::Lerp(m_SpherePos[4], m_SpherePos[5], move);    
    m_SpherePos[7] = Vector3::Lerp(m_SpherePos[3], m_SpherePos[2], move); 
    m_SpherePos[8] = Vector3::Lerp(m_SpherePos[0], m_SpherePos[3], move); 
    m_SpherePos[9] = Vector3::Lerp(m_SpherePos[8], m_SpherePos[7], move);    

    Vector3 afterPos = m_GameObject->GetPosition();
    float yaw = 0;
    Quaternion qtr = m_GameObject->GetQtr();

    if (m_Goal)
    {
        m_GameObject->SetPosition(m_SpherePos[9]);

        //��Ƀv���C���[�̕�����������
        //�v���C���[�ւ̃x�N�g�����v�Z
        Vector3 dir = m_GameObject->GetPosition() - m_SpherePos[7];                
        float yaw = atan2(dir.x, dir.z);        
        qtr = Quaternion::CreateFromYawPitchRoll(yaw, 0, 0);               
    }
    else
    {
        m_GameObject->SetPosition(m_SpherePos[6]);
        //��Ƀv���C���[�̕�����������
       //�v���C���[�ւ̃x�N�g�����v�Z
        Vector3 dir = m_GameObject->GetPosition() - m_SpherePos[4];
        float yaw = atan2(dir.x, dir.z);
        qtr = Quaternion::CreateFromYawPitchRoll(yaw, 0, 0);
    }   

    //��]����
    m_GameObject->SetQtr(qtr);

    //��������
    Vector3 pos = m_GameObject->GetPosition();
    pos.y = Manager::GetScene()->GetGameObject<Field>()->GetFieldHeightBySqno(pos, *m_GameObject);
    m_GameObject->SetPosition(pos);

    //particle->Create(m_GameObject->GetPosition(), Vector3::Up, Vector3::Up*100);
    //particle->Update();
}
