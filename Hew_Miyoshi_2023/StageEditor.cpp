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

    //カメラ切り替え
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

    // 保存ボタン
    if (ImGui::Button("Save Positions"))
    {
        AddToHistory();
        SavepositionToFile("positions.txt");
    }

    // 読み込みボタン
    if (ImGui::Button("Load Positions"))
    {
        AddToHistory();
        LoadpositionToFile("positions.txt");
    }

    //一個前、元に戻す
    if (ImGui::Button("Undo"))
    {
        Undo();
    }

    if (ImGui::Button("Redo"))
    {
        Redo();
    }

    CreateObject();

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

    // 各オブジェクトごとの座標設定
    for (int i = 0; i < position.size(); i++)
        if (ImGui::TreeNode(("Object " + std::to_string(i)).c_str()))
        {
            ImGui::SliderFloat("posX", &position[i].pos.x, -100.0f, 100.0f);
            ImGui::SliderFloat("posY", &position[i].pos.y, -100.0f, 100.0f);
            ImGui::SliderFloat("posZ", &position[i].pos.z, -100.0f, 100.0f);

            ImGui::SliderFloat("scaleX", &position[i].scale.x, -100.0f, 100.0f);
            ImGui::SliderFloat("scaleY", &position[i].scale.y, -100.0f, 100.0f);
            ImGui::SliderFloat("scaleZ", &position[i].scale.z, -100.0f, 100.0f);

            ImGui::SliderFloat("rotX", &position[i].rot.x, -100.0f, 100.0f);
            ImGui::SliderFloat("rotY", &position[i].rot.y, -100.0f, 100.0f);
            ImGui::SliderFloat("rotZ", &position[i].rot.z, -100.0f, 100.0f);

            if (ImGui::Button("DeleteObject"))
            {
                objList[i]->SetDestroy();

                auto first = position.begin() + i;  // 削除を開始する位置
                auto last = position.begin() + i + 1;   // 削除を終了する位置（この位置の要素は含まれません）

                position.erase(first, last);
            }

            ImGui::TreePop();
        }

    // 座標代入
    int iterat = 0;
    for (GameObject* object : objList)       
        {
            object->SetPosition(position[iterat].pos);
            object->SetScale(position[iterat].scale);
            object->SetRotation(position[iterat].rot);
            iterat++;
        }

    ImGui::End();

    ImGui::Begin("History");
    ImGui::Text("Index %d", historyIndex);
    ImGui::Text("Size %d", history.size());
    for (int i = 0; i < 4; i++)
    {
        ImGui::Text("Size %d", history[i].size());
    }
    ImGui::End();
}

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
        // エラーメッセージを表示またはログに記録
    }
}

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
        // エラーメッセージを表示またはログに記録
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