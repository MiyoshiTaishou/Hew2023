#include "StageEditor.h"
#include "ImGuiManager.h"
#include "gameObject.h"
#include "box.h"
#include "sky.h"
#include "Player.h"
#include "field.h"
#include "camera.h"
#include"DebugCamera.h"
#include"Enemy.h"
#include <fstream>

using namespace DirectX::SimpleMath;

void StageEditor::Init()
{
    AddGameObject<DebugCamera>(0);

    AddGameObject<Sky>(1);
    //AddGameObject<Player>(1);
    //AddGameObject<Field>(1);    
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
            AddGameObject<DebugCamera>(0);
        }
        else if (dbCamera)
        {
            dbCamera->SetDestroy();
            AddGameObject<Player>(1);
            AddGameObject<Camera>(0);
        }

    }

    // �ۑ��{�^��
    if (ImGui::Button("Save Positions"))
    {
        AddToHistory();
        SavepositionToFile("positions.txt");
    }

    // �ǂݍ��݃{�^��
    if (ImGui::Button("Load Positions"))
    {
        AddToHistory();
        LoadpositionToFile("positions.txt");
    }

    //��O�A���ɖ߂�
    if (ImGui::Button("Undo"))
    {
        Undo();
    }

    if (ImGui::Button("Redo"))
    {
        Redo();
    }

    //�I�u�W�F�N�g��������
    CreateObject();

    //�I�u�W�F�N�g�폜
    if (ImGui::Button("Deleteobject"))
        for (GameObject* object : objList)
        {
            AddToHistory();
            SavepositionToFile("undo.txt");
            object->SetDestroy();
            position.clear();
            objList.clear();
        }

    std::vector<GameObject*> objects;    

    // ���W���
    int iterat = 0;
    for (GameObject* object : objList)       
        {
            object->SetPosition(position[iterat].pos);
            object->SetScale(position[iterat].scale);
            object->SetRotation(position[iterat].rot);
            iterat++;
        }

    ImGui::End();  

    //�I�u�W�F�N�g�����Ǘ�
    ObjListManger();
}

//scene.h�ɓ��������ǂ�����
void StageEditor::SavepositionToFile(const std::string& filename)
{
    std::ofstream outputFile(filename);

    if (outputFile.is_open())
    {
        for (const InfoObjData& position : position)
        {
            outputFile << position.pos.x << " " << position.pos.y << " " << position.pos.z << " "
                << position.scale.x << " " << position.scale.y << " " << position.scale.z << " "
                << position.rot.x << " " << position.rot.y << " " << position.rot.z << " " << static_cast<int>(position.ClassKind) << " " << "\n";
        }

        outputFile.close();
    }
    else
    {
        // �G���[���b�Z�[�W��\���܂��̓��O�ɋL�^
    }
}

//scene.h�ɓ��������ǂ�����
void StageEditor::LoadpositionToFile(const std::string& filename)
{
    std::ifstream inputFile(filename);

    if (inputFile.is_open())
    {
        position.clear();

        InfoObjData data;
        int classKind;
        while (inputFile >> data.pos.x >> data.pos.y >> data.pos.z
            >> data.scale.x >> data.scale.y >> data.scale.z
            >> data.rot.x >> data.rot.y >> data.rot.z
            >> classKind)
        {
            switch (classKind)
            {
            case CLASS::BOX:
            {
                Box* box = AddGameObject<Box>(1);
                objList.push_back(box);
                break;
            }
            case CLASS::ENEMY:
            {
                Enemy* enemy = AddGameObject<Enemy>(1);
                objList.push_back(enemy);
                break;
            }
            default:
                break;
            }

            position.push_back(data);
        }

        inputFile.close();
    }
    else
    {
        // �G���[���b�Z�[�W��\���܂��̓��O�ɋL�^
    }
}

void StageEditor::CreateObject()
{
    if (ImGui::TreeNode(("Create Object ")))
    {
        if (ImGui::Button("BOXCreate"))
        {
            AddToHistory();
            Box* box = AddGameObject<Box>(3);
            InfoObjData data;
            data.pos = box->GetPosition();
            data.scale = box->GetScale();
            data.rot = box->GetRotation();
            data.ClassKind = CLASS::BOX;
            position.push_back(data);
            objList.push_back(box);
        }

        if (ImGui::Button("ENEMYCreate"))
        {
            AddToHistory();
            Enemy* enemy = AddGameObject<Enemy>(3);
            InfoObjData data;
            data.pos = enemy->GetPosition();
            data.scale = enemy->GetScale();
            data.rot = enemy->GetRotation();
            data.ClassKind = CLASS::ENEMY;
            position.push_back(data);
            objList.push_back(enemy);

        }

        ImGui::TreePop();
    }
}

void StageEditor::AddToHistory()
{
    if (historyIndex > 2)return;

    for (InfoObjData info : position)
    {
        history[historyIndex].push_back(info);
    }

    historyIndex++;
}

//Undo,Redo�͌��݂̏������ƊԈ���Ă���̂ŏC��������
void StageEditor::Undo()
{
    if (historyIndex <= 0)return;

    historyIndex--;

    for (GameObject* object : objList)
    {
        object->SetDestroy();
        position.clear();
        objList.clear();
    }

    for (InfoObjData info : history[historyIndex])
    {
        switch (info.ClassKind)
        {
        case CLASS::BOX:
        {
            Box* box = AddGameObject<Box>(3);
            objList.push_back(box);
            break;
        }
        case CLASS::ENEMY:
        {
            Enemy* enemy = AddGameObject<Enemy>(3);
            objList.push_back(enemy);
            break;
        }
        default:
            break;
        }

        position.push_back(info);
    }
}

void StageEditor::Redo()
{
    if (historyIndex > 2)return;

    if (history[historyIndex + 1].size() == 0)return;

    historyIndex++;

    for (GameObject* object : objList)
    {
        object->SetDestroy();
        position.clear();
    }

    for (InfoObjData info : history[historyIndex])
    {
        switch (info.ClassKind)
        {
        case CLASS::BOX:
        {
            Box* box = AddGameObject<Box>(3);
            objList.push_back(box);
            break;
        }
        case CLASS::ENEMY:
        {
            Enemy* enemy = AddGameObject<Enemy>(3);
            objList.push_back(enemy);
            break;
        }
        default:
            break;
        }

        position.push_back(info);
    }
}

void StageEditor::ObjListManger()
{
    ImGui::Begin("ObjInfo");

    if (ImGui::ListBoxHeader("Objects", ImVec2(200, 200))) {
        for (int i = 0; i < position.size(); i++) {
            const bool isSelected = (i == selectedObjectIndex);
            if (ImGui::Selectable(("Object " + std::to_string(i)).c_str(), isSelected)) {
                selectedObjectIndex = i; // �I�u�W�F�N�g���I�����ꂽ�Ƃ��̏���
            }
        }
        ImGui::ListBoxFooter();
    }
    
    ImGui::End();

    ImGui::Begin("ObjList");
   
       // �I�u�W�F�N�g���X�g��\��   

       // �e�I�u�W�F�N�g���Ƃ̍��W�ݒ�
    if (selectedObjectIndex != -1) {
        {
            float sliderStep = 1.0f;//�l�̉�����

            // �����{�^��
            if (ImGui::Button("-##PosX"))
            {
                position[selectedObjectIndex].pos.x -= sliderStep;
            }
            ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

            // �X���C�_�[
            ImGui::SliderFloat("posX##", &position[selectedObjectIndex].pos.x, -100.0f, 100.0f);

            // �����{�^��
            ImGui::SameLine();
            if (ImGui::Button("+##PosX"))
            {
                position[selectedObjectIndex].pos.x += sliderStep;
            }

            if (ImGui::Button("-##PosY")) {
                position[selectedObjectIndex].pos.y -= sliderStep;
            }
            ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

            // Y���W�̃X���C�_�[
            ImGui::SliderFloat("posY##", &position[selectedObjectIndex].pos.y, -100.0f, 100.0f);

            // Y���W�̑����{�^��
            ImGui::SameLine();
            if (ImGui::Button("+##PosY")) {
                position[selectedObjectIndex].pos.y += sliderStep;
            }

            // Z���W�̌����{�^��
            if (ImGui::Button("-##PosZ")) {
                position[selectedObjectIndex].pos.z -= sliderStep;
            }
            ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

            // Z���W�̃X���C�_�[
            ImGui::SliderFloat("posZ##", &position[selectedObjectIndex].pos.z, -100.0f, 100.0f);

            // Z���W�̑����{�^��
            ImGui::SameLine();
            if (ImGui::Button("+##PosZ")) {
                position[selectedObjectIndex].pos.z += sliderStep;
            }

            // X�X�P�[���̌����{�^��
            if (ImGui::Button("-##ScaleX")) {
                position[selectedObjectIndex].scale.x -= sliderStep;
            }
            ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

            // X�X�P�[���̃X���C�_�[
            ImGui::SliderFloat("scaleX##", &position[selectedObjectIndex].scale.x, -100.0f, 100.0f);

            // X�X�P�[���̑����{�^��
            ImGui::SameLine();
            if (ImGui::Button("+##ScaleX")) {
                position[selectedObjectIndex].scale.x += sliderStep;
            }

            // Y�X�P�[���̌����{�^��
            if (ImGui::Button("-##ScaleY")) {
                position[selectedObjectIndex].scale.y -= sliderStep;
            }
            ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

            // Y�X�P�[���̃X���C�_�[
            ImGui::SliderFloat("scaleY##", &position[selectedObjectIndex].scale.y, -100.0f, 100.0f);

            // Y�X�P�[���̑����{�^��
            ImGui::SameLine();
            if (ImGui::Button("+##ScaleY")) {
                position[selectedObjectIndex].scale.y += sliderStep;
            }

            // Z�X�P�[���̌����{�^��
            if (ImGui::Button("-##ScaleZ")) {
                position[selectedObjectIndex].scale.z -= sliderStep;
            }
            ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

            // Z�X�P�[���̃X���C�_�[
            ImGui::SliderFloat("scaleZ##", &position[selectedObjectIndex].scale.z, -100.0f, 100.0f);

            // Z�X�P�[���̑����{�^��
            ImGui::SameLine();
            if (ImGui::Button("+##ScaleZ")) {
                position[selectedObjectIndex].scale.z += sliderStep;
            }

            // X��]�̌����{�^��
            if (ImGui::Button("-##RotX")) {
                position[selectedObjectIndex].rot.x -= sliderStep;
            }
            ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

            // X��]�̃X���C�_�[
            ImGui::SliderFloat("rotX##", &position[selectedObjectIndex].rot.x, -100.0f, 100.0f);

            // X��]�̑����{�^��
            ImGui::SameLine();
            if (ImGui::Button("+##RotX")) {
                position[selectedObjectIndex].rot.x += sliderStep;
            }

            // Y��]�̌����{�^��
            if (ImGui::Button("-##RotY")) {
                position[selectedObjectIndex].rot.y -= sliderStep;
            }
            ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

            // Y��]�̃X���C�_�[
            ImGui::SliderFloat("rotY##", &position[selectedObjectIndex].rot.y, -100.0f, 100.0f);

            // Y��]�̑����{�^��
            ImGui::SameLine();
            if (ImGui::Button("+##RotY")) {
                position[selectedObjectIndex].rot.y += sliderStep;
            }

            // Z��]�̌����{�^��
            if (ImGui::Button("-##RotZ")) {
                position[selectedObjectIndex].rot.z -= sliderStep;
            }
            ImGui::SameLine(); // �����s�ɃX���C�_�[��z�u

            // Z��]�̃X���C�_�[
            ImGui::SliderFloat("rotZ##", &position[selectedObjectIndex].rot.z, -100.0f, 100.0f);

            // Z��]�̑����{�^��
            ImGui::SameLine();
            if (ImGui::Button("+##RotZ")) {
                position[selectedObjectIndex].rot.z += sliderStep;
            }

            if (ImGui::Button("DeleteObject"))
            {
                objList[selectedObjectIndex]->SetDestroy();

                auto first = position.begin() + selectedObjectIndex;  // �폜���J�n����ʒu
                auto last = position.begin() + selectedObjectIndex + 1;   // �폜���I������ʒu�i���̈ʒu�̗v�f�͊܂܂�܂���j

                position.erase(first, last);
            }
        }
    }


    ImGui::End();
}
