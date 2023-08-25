#include "StageEditor.h"
#include "ImGuiManager.h"
#include "gameObject.h"
#include "box.h"
#include "sky.h"
#include "Player.h"
#include "field.h"
#include "camera.h"
#include"DebugCamera.h"
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
    std::vector<Box*> boxVec = GetGameObjects<Box>();

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
        else if(dbCamera)
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

    // オブジェクト生成
    if (ImGui::Button("Create Object"))
    {               
        AddToHistory();
        Box* box = AddGameObject<Box>(3);
        InfoObjData data;
        data.pos = box->GetPosition();
        data.scale = box->GetScale();
        data.rot = box->GetRotation();
        position.push_back(data);  
    }

    if (ImGui::Button("Deleteobject"))    
        for (auto& objectList : m_GameObject)        
            for (GameObject* object : objectList)            
                if (typeid(*object) == typeid(Box))
                {       
                    AddToHistory();
                    SavepositionToFile("undo.txt");
                    object->SetDestroy();
                    position.clear();
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
                boxVec[i]->SetDestroy();
                
                auto first = position.begin() + i;  // 削除を開始する位置
                auto last = position.begin() + i + 1;   // 削除を終了する位置（この位置の要素は含まれません）

                position.erase(first, last);
            }

            ImGui::TreePop();
        }    

    // 座標代入
    int iterat = 0;
    for (auto& objectList : m_GameObject)    
        for (GameObject* object : objectList)        
            if (iterat < position.size() && typeid(*object) == typeid(Box))
            {
                object->SetPosition(position[iterat].pos);
                object->SetScale(position[iterat].scale);
                object->SetRotation(position[iterat].rot);
                iterat++;
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
                << position.rot.x << " " << position.rot.y << " " << position.rot.z << "\n";
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
        while (inputFile >> data.pos.x >> data.pos.y >> data.pos.z
            >> data.scale.x >> data.scale.y >> data.scale.z
            >> data.rot.x >> data.rot.y >> data.rot.z)
        {
            Box* box = AddGameObject<Box>(3);
            position.push_back(data);
        }

        inputFile.close();
    }
    else
    {
        // エラーメッセージを表示またはログに記録
    }
}

void StageEditor::AddToHistory()
{
    if (historyIndex > 4)return;

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

    for (auto& objectList : m_GameObject)
        for (GameObject* object : objectList)
            if (typeid(*object) == typeid(Box))
            {                
                object->SetDestroy();
                position.clear();
            }

    for (InfoObjData info : history[historyIndex])
    {
        Box* box = AddGameObject<Box>(3);
        position.push_back(info);
    }    
}

void StageEditor::Redo()
{
    if (historyIndex > 4)return;

    historyIndex++;

    for (auto& objectList : m_GameObject)
        for (GameObject* object : objectList)
            if (typeid(*object) == typeid(Box))
            {
                object->SetDestroy();
                position.clear();
            }

    for (InfoObjData info : history[historyIndex])
    {
        Box* box = AddGameObject<Box>(3);
        position.push_back(info);
    }
}
