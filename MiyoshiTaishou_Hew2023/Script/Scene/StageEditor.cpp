#include "StageEditor.h"
#include"../ImGui/ImGuiManager.h"

//�I�u�W�F�N�g
#include"../Object/BoxObject.h"
#include"../Object/sky.h"
#include"../Object/Player.h"
#include"../Object/field.h"
#include"../Object/camera.h"
#include"../Object/DebugCamera.h"

//UI
#include"../UI/score.h"

#define NOTSELECTED -1

void StageEditor::Init()
{
	AddGameObject<DebugCamera>(Layer0);
	AddGameObject<Sky>(Layer0);
    //AddGameObject<Field>(Layer1);

    AddGameObject<Score>(Layer3);
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
            AddGameObject<DebugCamera>(Layer0);
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
        SaveObjectData("Obj.csv");
    }

    // �ǂݍ��݃{�^��
    if (ImGui::Button("Load Positions"))
    {
        LoadObjectData("Obj.csv");
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

    ImGui::End();

    CreateObj();

    ObjListManger();
}

void StageEditor::CreateObj()
{
    if (ImGui::TreeNode(("Create Object ")))
    {
        if (ImGui::Button("BOXCreate"))
        {            
            BoxObject* box = AddGameObject<BoxObject>(Layer1);          
        }

        if (ImGui::Button("ENEMYCreate"))
        {
            BoxObject* box = AddGameObject<BoxObject>(Layer1);
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

    // �����{�^��
    if (ImGui::Button("-##PosX"))
    {
        pos.x -= sliderStep;
    }
    ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

    // �X���C�_�[
    ImGui::SliderFloat("posX##", &pos.x, -100.0f, 100.0f);

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
    ImGui::SliderFloat("posY##", &pos.y, -100.0f, 100.0f);

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
    ImGui::SliderFloat("posZ##", &pos.z, -100.0f, 100.0f);

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
    ImGui::SliderFloat("scaleX##", &scale.x, -100.0f, 100.0f);

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
    ImGui::SliderFloat("scaleY##", &scale.y, -100.0f, 100.0f);

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
    ImGui::SliderFloat("scaleZ##", &scale.z, -100.0f, 100.0f);

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
    ImGui::SliderFloat("rotX##", &rot.x, -100.0f, 100.0f);

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
    ImGui::SliderFloat("rotY##", &rot.y, -100.0f, 100.0f);

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
    ImGui::SliderFloat("rotZ##", &rot.z, -100.0f, 100.0f);

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
