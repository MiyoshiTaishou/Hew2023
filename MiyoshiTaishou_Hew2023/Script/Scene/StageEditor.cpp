#include "StageEditor.h"
#include"../ImGui/ImGuiManager.h"

//オブジェクト
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
            AddGameObject<DebugCamera>(Layer0);
        }
        else if (dbCamera)
        {
            dbCamera->SetDestroy();
            AddGameObject<Player>(Layer1);
            AddGameObject<Camera>(Layer0);
        }

        //選択していない
        selectedObjectIndex = NOTSELECTED;
    }

    // 保存ボタン
    if (ImGui::Button("Save Positions"))
    {
        SaveObjectData("Obj.csv");
    }

    // 読み込みボタン
    if (ImGui::Button("Load Positions"))
    {
        LoadObjectData("Obj.csv");
    }

    //オブジェクト削除
    if (ImGui::Button("Deleteobject"))
    {
        const auto& objList = m_GameObject[Layer1];
    
        for (const auto& obj : objList)
        {
            obj->SetDestroy();

            //何も選択していない状態に戻す
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
                selectedObjectIndex = i; // オブジェクトが選択されたときの処理
            }
        }
        ImGui::ListBoxFooter();
    }

    ImGui::End();

    ImGui::Begin("ObjList");

    int count = 0;

    GameObject* IndexObj=nullptr;

    //選択したオブジェクトの情報を取得
    for (const auto& obj : objList)
    {
        if (selectedObjectIndex == count)
        {
            IndexObj = obj;           
        }      

        count++;
    }

    //選択していないなら通さない
    if (selectedObjectIndex == NOTSELECTED)
    {
        ImGui::End();
        return;
    }

    float sliderStep = 1.0f;//値の加入量

    DirectX::SimpleMath::Vector3 pos = IndexObj->GetPosition();
    DirectX::SimpleMath::Vector3 scale = IndexObj->GetScale();
    DirectX::SimpleMath::Vector3 rot = IndexObj->GetRotation();

    // 減少ボタン
    if (ImGui::Button("-##PosX"))
    {
        pos.x -= sliderStep;
    }
    ImGui::SameLine(); // 同じ行にスライダーを配置

    // スライダー
    ImGui::SliderFloat("posX##", &pos.x, -100.0f, 100.0f);

    // 増加ボタン
    ImGui::SameLine();
    if (ImGui::Button("+##PosX"))
    {
        pos.x += sliderStep;
    }

    if (ImGui::Button("-##PosY")) {
        pos.y -= sliderStep;
    }
    ImGui::SameLine(); // 同じ行にスライダーを配置

    // Y座標のスライダー
    ImGui::SliderFloat("posY##", &pos.y, -100.0f, 100.0f);

    // Y座標の増加ボタン
    ImGui::SameLine();
    if (ImGui::Button("+##PosY")) {
        pos.y += sliderStep;
    }

    // Z座標の減少ボタン
    if (ImGui::Button("-##PosZ")) {
        pos.z -= sliderStep;
    }
    ImGui::SameLine(); // 同じ行にスライダーを配置

    // Z座標のスライダー
    ImGui::SliderFloat("posZ##", &pos.z, -100.0f, 100.0f);

    // Z座標の増加ボタン
    ImGui::SameLine();
    if (ImGui::Button("+##PosZ")) {
        pos.z += sliderStep;
    }

    // Xスケールの減少ボタン
    if (ImGui::Button("-##ScaleX")) {
        scale.x -= sliderStep;
    }
    ImGui::SameLine(); // 同じ行にスライダーを配置

    // Xスケールのスライダー
    ImGui::SliderFloat("scaleX##", &scale.x, -100.0f, 100.0f);

    // Xスケールの増加ボタン
    ImGui::SameLine();
    if (ImGui::Button("+##ScaleX")) {
        scale.x += sliderStep;
    }

    // Yスケールの減少ボタン
    if (ImGui::Button("-##ScaleY")) {
        scale.y -= sliderStep;
    }
    ImGui::SameLine(); // 同じ行にスライダーを配置

    // Yスケールのスライダー
    ImGui::SliderFloat("scaleY##", &scale.y, -100.0f, 100.0f);

    // Yスケールの増加ボタン
    ImGui::SameLine();
    if (ImGui::Button("+##ScaleY")) {
        scale.y += sliderStep;
    }

    // Zスケールの減少ボタン
    if (ImGui::Button("-##ScaleZ")) {
        scale.z -= sliderStep;
    }
    ImGui::SameLine(); // 同じ行にスライダーを配置

    // Zスケールのスライダー
    ImGui::SliderFloat("scaleZ##", &scale.z, -100.0f, 100.0f);

    // Zスケールの増加ボタン
    ImGui::SameLine();
    if (ImGui::Button("+##ScaleZ")) {
        scale.z += sliderStep;
    }

    // X回転の減少ボタン
    if (ImGui::Button("-##RotX")) {
        rot.x -= sliderStep;
    }
    ImGui::SameLine(); // 同じ行にスライダーを配置

    // X回転のスライダー
    ImGui::SliderFloat("rotX##", &rot.x, -100.0f, 100.0f);

    // X回転の増加ボタン
    ImGui::SameLine();
    if (ImGui::Button("+##RotX")) {
        rot.x += sliderStep;
    }

    // Y回転の減少ボタン
    if (ImGui::Button("-##RotY")) {
        rot.y -= sliderStep;
    }
    ImGui::SameLine(); // 同じ行にスライダーを配置

    // Y回転のスライダー
    ImGui::SliderFloat("rotY##", &rot.y, -100.0f, 100.0f);

    // Y回転の増加ボタン
    ImGui::SameLine();
    if (ImGui::Button("+##RotY")) {
        rot.y += sliderStep;
    }

    // Z回転の減少ボタン
    if (ImGui::Button("-##RotZ")) {
        rot.z -= sliderStep;
    }
    ImGui::SameLine(); // 同じ行にスライダーを配置

    // Z回転のスライダー
    ImGui::SliderFloat("rotZ##", &rot.z, -100.0f, 100.0f);

    // Z回転の増加ボタン
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

        //選択していない
        selectedObjectIndex = NOTSELECTED;
    }

    ImGui::End();
}
