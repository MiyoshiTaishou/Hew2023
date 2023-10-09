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

    //オブジェクト生成処理
    CreateObject();

    //オブジェクト削除
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

    //オブジェクト情報を管理
    ObjListManger();
}

//scene.hに入れる方が良さそう
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

//scene.hに入れる方が良さそう
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

//Undo,Redoは現在の処理だと間違っているので修正をする
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
                selectedObjectIndex = i; // オブジェクトが選択されたときの処理
            }
        }
        ImGui::ListBoxFooter();
    }
    
    ImGui::End();

    ImGui::Begin("ObjList");
   
       // オブジェクトリストを表示   

       // 各オブジェクトごとの座標設定
    if (selectedObjectIndex != -1) {
        {
            float sliderStep = 1.0f;//値の加入量

            // 減少ボタン
            if (ImGui::Button("-##PosX"))
            {
                position[selectedObjectIndex].pos.x -= sliderStep;
            }
            ImGui::SameLine(); // 同じ行にスライダーを配置

            // スライダー
            ImGui::SliderFloat("posX##", &position[selectedObjectIndex].pos.x, -100.0f, 100.0f);

            // 増加ボタン
            ImGui::SameLine();
            if (ImGui::Button("+##PosX"))
            {
                position[selectedObjectIndex].pos.x += sliderStep;
            }

            if (ImGui::Button("-##PosY")) {
                position[selectedObjectIndex].pos.y -= sliderStep;
            }
            ImGui::SameLine(); // 同じ行にスライダーを配置

            // Y座標のスライダー
            ImGui::SliderFloat("posY##", &position[selectedObjectIndex].pos.y, -100.0f, 100.0f);

            // Y座標の増加ボタン
            ImGui::SameLine();
            if (ImGui::Button("+##PosY")) {
                position[selectedObjectIndex].pos.y += sliderStep;
            }

            // Z座標の減少ボタン
            if (ImGui::Button("-##PosZ")) {
                position[selectedObjectIndex].pos.z -= sliderStep;
            }
            ImGui::SameLine(); // 同じ行にスライダーを配置

            // Z座標のスライダー
            ImGui::SliderFloat("posZ##", &position[selectedObjectIndex].pos.z, -100.0f, 100.0f);

            // Z座標の増加ボタン
            ImGui::SameLine();
            if (ImGui::Button("+##PosZ")) {
                position[selectedObjectIndex].pos.z += sliderStep;
            }

            // Xスケールの減少ボタン
            if (ImGui::Button("-##ScaleX")) {
                position[selectedObjectIndex].scale.x -= sliderStep;
            }
            ImGui::SameLine(); // 同じ行にスライダーを配置

            // Xスケールのスライダー
            ImGui::SliderFloat("scaleX##", &position[selectedObjectIndex].scale.x, -100.0f, 100.0f);

            // Xスケールの増加ボタン
            ImGui::SameLine();
            if (ImGui::Button("+##ScaleX")) {
                position[selectedObjectIndex].scale.x += sliderStep;
            }

            // Yスケールの減少ボタン
            if (ImGui::Button("-##ScaleY")) {
                position[selectedObjectIndex].scale.y -= sliderStep;
            }
            ImGui::SameLine(); // 同じ行にスライダーを配置

            // Yスケールのスライダー
            ImGui::SliderFloat("scaleY##", &position[selectedObjectIndex].scale.y, -100.0f, 100.0f);

            // Yスケールの増加ボタン
            ImGui::SameLine();
            if (ImGui::Button("+##ScaleY")) {
                position[selectedObjectIndex].scale.y += sliderStep;
            }

            // Zスケールの減少ボタン
            if (ImGui::Button("-##ScaleZ")) {
                position[selectedObjectIndex].scale.z -= sliderStep;
            }
            ImGui::SameLine(); // 同じ行にスライダーを配置

            // Zスケールのスライダー
            ImGui::SliderFloat("scaleZ##", &position[selectedObjectIndex].scale.z, -100.0f, 100.0f);

            // Zスケールの増加ボタン
            ImGui::SameLine();
            if (ImGui::Button("+##ScaleZ")) {
                position[selectedObjectIndex].scale.z += sliderStep;
            }

            // X回転の減少ボタン
            if (ImGui::Button("-##RotX")) {
                position[selectedObjectIndex].rot.x -= sliderStep;
            }
            ImGui::SameLine(); // 同じ行にスライダーを配置

            // X回転のスライダー
            ImGui::SliderFloat("rotX##", &position[selectedObjectIndex].rot.x, -100.0f, 100.0f);

            // X回転の増加ボタン
            ImGui::SameLine();
            if (ImGui::Button("+##RotX")) {
                position[selectedObjectIndex].rot.x += sliderStep;
            }

            // Y回転の減少ボタン
            if (ImGui::Button("-##RotY")) {
                position[selectedObjectIndex].rot.y -= sliderStep;
            }
            ImGui::SameLine(); // 同じ行にスライダーを配置

            // Y回転のスライダー
            ImGui::SliderFloat("rotY##", &position[selectedObjectIndex].rot.y, -100.0f, 100.0f);

            // Y回転の増加ボタン
            ImGui::SameLine();
            if (ImGui::Button("+##RotY")) {
                position[selectedObjectIndex].rot.y += sliderStep;
            }

            // Z回転の減少ボタン
            if (ImGui::Button("-##RotZ")) {
                position[selectedObjectIndex].rot.z -= sliderStep;
            }
            ImGui::SameLine(); // 同じ行にスライダーを配置

            // Z回転のスライダー
            ImGui::SliderFloat("rotZ##", &position[selectedObjectIndex].rot.z, -100.0f, 100.0f);

            // Z回転の増加ボタン
            ImGui::SameLine();
            if (ImGui::Button("+##RotZ")) {
                position[selectedObjectIndex].rot.z += sliderStep;
            }

            if (ImGui::Button("DeleteObject"))
            {
                objList[selectedObjectIndex]->SetDestroy();

                auto first = position.begin() + selectedObjectIndex;  // 削除を開始する位置
                auto last = position.begin() + selectedObjectIndex + 1;   // 削除を終了する位置（この位置の要素は含まれません）

                position.erase(first, last);
            }
        }
    }


    ImGui::End();
}
