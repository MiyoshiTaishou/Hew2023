#include "StageEditor.h"
#include"../ImGui/ImGuiManager.h"
#include"../Sysytem/manager.h"

//�I�u�W�F�N�g
#include"../Object/BoxObject.h"
#include"../Object/sky.h"
#include"../Object/Player.h"
#include"../Object/field.h"
#include"../Object/camera.h"
#include"../Object/DebugCamera.h"

//�X�e�[�W�p�I�u�W�F�N�g
#include"../Object/YataiObject.h"
#include"../Object/YakisobaObject.h"
#include"../Object/TreeObject.h"
#include"../Object/KasuteraObject.h"
#include"../Object/CarObject.h"
#include"../Object/TakoyakiObject.h"
#include"../Object/FakeTakotaki.h"

//UI
#include"../UI/score.h"
#include"../UI/HitUI.h"

#define NOTSELECTED -1


void StageEditor::Init()
{
   /* obj = new GameObject;
    obj->Init();
    obj->SetPosition(DirectX::SimpleMath::Vector3(0, 100, -300));*/
            
	Sky* sky = AddGameObject<Sky>(Layer0);
    Field* filed = AddGameObject<Field>(Layer1);
    filed->Init("../asset/map/GameMap1-3.csv");
    //filed->Init("Title.csv");

    AddGameObject<DebugCamera>(Layer0)->m_TargetObj = sky;

    AddGameObject<Score>(Layer3);

    //�q�b�g���ɕ\������UI
    AddGameObject<HitUI>(Layer3)->Init(0.0f, 450.0f, 480.0f, 240.0f,
        "../asset\\texture\\�ۂ�.png");

    AddGameObject<HitUI>(Layer3)->Init(800.0f, 0.0f, 480.0f, 240.0f,
        "../asset\\texture\\�ۂ�.png");

    AddGameObject<HitUI>(Layer3)->Init(0.0f, 0.0f, 480.0f, 240.0f,
        "../asset\\texture\\�҂�.png");

    AddGameObject<HitUI>(Layer3)->Init(800.0f, 450.0f, 480.0f, 240.0f,
        "../asset\\texture\\�҂�.png");
}

void StageEditor::Update()
{
   
}

void StageEditor::Draw()
{
    ImGui::Begin("Stage Editor");

    //�J�����؂�ւ�
    if (ImGui::Button("CameraModeChange"))
    {
        Camera* camera = GetGameObject<Camera>();
        DebugCamera* dbCamera = GetGameObject<DebugCamera>();
        Player* player = GetGameObject<Player>();

        if (camera)
        {
            camera->SetDestroy();
            player->SetDestroy();

            Sky* sky = GetGameObject<Sky>();
            AddGameObject<DebugCamera>(Layer0)->m_TargetObj = sky;
        }
        else if (dbCamera)
        {
            dbCamera->SetDestroy();
            AddGameObject<Player>(Layer1);
            AddGameObject<Camera>(Layer0);
        }

        //�I�����Ă��Ȃ�
        selectedObjectIndex = NOTSELECTED;
    }

    // �ۑ��{�^��
    if (ImGui::Button("Save Positions"))
    {
        SaveObjectData(m_bufferMap);
    }

    // �ǂݍ��݃{�^��
    if (ImGui::Button("Load Positions"))
    {
        LoadObjectData(m_bufferMap);
    }

    //�X�e�[�W�����蔻��X�V
    if (ImGui::Button("FieldMeshUpdaye"))
    {
        GetGameObject<Field>()->SetDestroy();
        Field* filed = AddGameObject<Field>(Layer1);
        filed->Init(m_bufferField);
    }

    //�I�u�W�F�N�g�폜
    if (ImGui::Button("Deleteobject"))
    {
        const auto& objList = m_GameObject[Layer1];
    
        for (const auto& obj : objList)
        {
            obj->SetDestroy();

            //�����I�����Ă��Ȃ���Ԃɖ߂�
            selectedObjectIndex = -1;
        }    
    }

    ImGui::InputText("Field Name", m_bufferField, sizeof(m_bufferField));
    Manager::SetFiledName(m_bufferField);

    ImGui::InputText("Map Name", m_bufferMap, sizeof(m_bufferMap));

    ImGui::End();

    CreateObj();

    ObjListManger();
}

void StageEditor::CreateObj()
{
    if (ImGui::TreeNode(("Create Object ")))
    {
        if (ImGui::Button("YataiCreate"))
        {            
            YataiObject* yatai = AddGameObject<YataiObject>(Layer1);          
        }

        if (ImGui::Button("YakisobCareate"))
        {
            YakisobaObject* yakisoba = AddGameObject<YakisobaObject>(Layer1);
        }

        if (ImGui::Button("TreeCareate"))
        {
            TreeObject* tree = AddGameObject<TreeObject>(Layer1);
        }

        if (ImGui::Button("KasuteraCareate"))
        {
            KasuteraObject* kasutera = AddGameObject<KasuteraObject>(Layer1);
        }

        if (ImGui::Button("CarCareate"))
        {
            CarObject* car = AddGameObject<CarObject>(Layer1);
        }

        if (ImGui::Button("FiledCareate"))
        {
            Field* filed = AddGameObject<Field>(Layer1);
        }

        if (ImGui::Button("TakoyakiCareate"))
        {
            TakoyakiObject* takoyaki = AddGameObject<TakoyakiObject>(Layer1);
        }

        if (ImGui::Button("FakeTakoyakiCareate"))
        {
            FakeTakoyakiObject* takoyaki = AddGameObject<FakeTakoyakiObject>(Layer1);
        }

        ImGui::TreePop();
    }
}

void StageEditor::ObjListManger()
{
    ImGui::Begin("ObjInfo");

    const auto& objList = m_GameObject[Layer1];

    if (ImGui::ListBoxHeader("Objects", ImVec2(200, 200))) {
        for (int i = 0; i < objList.size(); i++) {
            const bool isSelected = (i == selectedObjectIndex);
            if (ImGui::Selectable(("Object " + std::to_string(i)).c_str(), isSelected)) {
                selectedObjectIndex = i; // �I�u�W�F�N�g���I�����ꂽ�Ƃ��̏���
            }
        }
        ImGui::ListBoxFooter();
    }

    ImGui::End();

    ImGui::Begin("ObjList");

    int count = 0;

    GameObject* IndexObj=nullptr;

    //�I�������I�u�W�F�N�g�̏����擾
    for (const auto& obj : objList)
    {
        if (selectedObjectIndex == count)
        {
            IndexObj = obj;           
        }      

        count++;
    }

    //�I�����Ă��Ȃ��Ȃ�ʂ��Ȃ�
    if (selectedObjectIndex == NOTSELECTED)
    {
        ImGui::End();
        return;
    }

    float sliderStep = 1.0f;//�l�̉�����

    DirectX::SimpleMath::Vector3 pos = IndexObj->GetPosition();
    DirectX::SimpleMath::Vector3 scale = IndexObj->GetScale();
    DirectX::SimpleMath::Vector3 rot = IndexObj->GetRotation();
    //DirectX::SimpleMath::Quaternion rot;

    // �����{�^��
    if (ImGui::Button("-##PosX"))
    {
        pos.x -= sliderStep;
    }
    ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

    // �X���C�_�[
    ImGui::SliderFloat("posX##", &pos.x, -150.0f, 150.0f);

    // �����{�^��
    ImGui::SameLine();
    if (ImGui::Button("+##PosX"))
    {
        pos.x += sliderStep;
    }

    if (ImGui::Button("-##PosY")) {
        pos.y -= sliderStep;
    }
    ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

    // Y���W�̃X���C�_�[
    ImGui::SliderFloat("posY##", &pos.y, -150.0f, 150.0f);

    // Y���W�̑����{�^��
    ImGui::SameLine();
    if (ImGui::Button("+##PosY")) {
        pos.y += sliderStep;
    }

    // Z���W�̌����{�^��
    if (ImGui::Button("-##PosZ")) {
        pos.z -= sliderStep;
    }
    ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

    // Z���W�̃X���C�_�[
    ImGui::SliderFloat("posZ##", &pos.z, -150.0f, 150.0f);

    // Z���W�̑����{�^��
    ImGui::SameLine();
    if (ImGui::Button("+##PosZ")) {
        pos.z += sliderStep;
    }

    // X�X�P�[���̌����{�^��
    if (ImGui::Button("-##ScaleX")) {
        scale.x -= sliderStep;
    }
    ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

    // X�X�P�[���̃X���C�_�[
    ImGui::SliderFloat("scaleX##", &scale.x, -150.0f, 150.0f);

    // X�X�P�[���̑����{�^��
    ImGui::SameLine();
    if (ImGui::Button("+##ScaleX")) {
        scale.x += sliderStep;
    }

    // Y�X�P�[���̌����{�^��
    if (ImGui::Button("-##ScaleY")) {
        scale.y -= sliderStep;
    }
    ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

    // Y�X�P�[���̃X���C�_�[
    ImGui::SliderFloat("scaleY##", &scale.y, -150.0f, 150.0f);

    // Y�X�P�[���̑����{�^��
    ImGui::SameLine();
    if (ImGui::Button("+##ScaleY")) {
        scale.y += sliderStep;
    }

    // Z�X�P�[���̌����{�^��
    if (ImGui::Button("-##ScaleZ")) {
        scale.z -= sliderStep;
    }
    ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

    // Z�X�P�[���̃X���C�_�[
    ImGui::SliderFloat("scaleZ##", &scale.z, -150.0f, 150.0f);

    // Z�X�P�[���̑����{�^��
    ImGui::SameLine();
    if (ImGui::Button("+##ScaleZ")) {
        scale.z += sliderStep;
    }

    // X��]�̌����{�^��
    if (ImGui::Button("-##RotX")) {
        rot.x -= sliderStep;
    }
    ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

    // X��]�̃X���C�_�[
    ImGui::SliderFloat("rotX##", &rot.x, -150.0f, 150.0f);

    // X��]�̑����{�^��
    ImGui::SameLine();
    if (ImGui::Button("+##RotX")) {
        rot.x += sliderStep;
    }

    // Y��]�̌����{�^��
    if (ImGui::Button("-##RotY")) {
        rot.y -= sliderStep;
    }
    ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

    // Y��]�̃X���C�_�[
    ImGui::SliderFloat("rotY##", &rot.y, -150.0f, 150.0f);

    // Y��]�̑����{�^��
    ImGui::SameLine();
    if (ImGui::Button("+##RotY")) {
        rot.y += sliderStep;
    }

    // Z��]�̌����{�^��
    if (ImGui::Button("-##RotZ")) {
        rot.z -= sliderStep;
    }
    ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

    // Z��]�̃X���C�_�[
    ImGui::SliderFloat("rotZ##", &rot.z, -150.0f, 150.0f);

    // Z��]�̑����{�^��
    ImGui::SameLine();
    if (ImGui::Button("+##RotZ")) {
        rot.z += sliderStep;
    }

    IndexObj->SetPosition(pos);
    IndexObj->SetScale(scale);
    IndexObj->SetRotation(rot);
   
    if (ImGui::Button("DeleteObject"))
    {
        IndexObj->SetDestroy();

        //�I�����Ă��Ȃ�
        selectedObjectIndex = NOTSELECTED;
    }

    ImGui::End();
}
