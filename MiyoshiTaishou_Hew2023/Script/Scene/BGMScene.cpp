#include "BGMScene.h"
#include"TitleScene.h"
#include"Transition.h"

#include"../Sysytem/DirectWrite.h"
#include"../Sysytem/input.h"
#include"../Sysytem/manager.h"

#include"../Component/sprite.h"
#include"../Component/audio.h"

using namespace DirectX::SimpleMath;

void BGMScene::Init()
{	
    ReadBGMName("../asset/text/曲リスト.txt");

    //曲数分文字表示処理追加
    for (int i = 0; i < m_BGMName.size(); i++)
    {
        //フォント設定
        FontData* data = new FontData();
        data->fontSize = 25;
        data->fontWeight = DWRITE_FONT_WEIGHT_BOLD;
        data->Color = D2D1::ColorF(1.0f, 1.0f, 0.0f, 1.0f);

        DirectWrite* write = new DirectWrite(data);
        write->Init();

        m_WriteList.push_back(write);
    }

    //プレイリストの文字
    for (int i = 0; i < MAX_PLAYLIST; i++)
    {
        //フォント設定
        FontData* data = new FontData();
        data->fontSize = 25;
        data->fontWeight = DWRITE_FONT_WEIGHT_BOLD;
        data->Color = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f);

        DirectWrite* write = new DirectWrite(data);
        write->Init();

        m_WritePlayList[i] = write;

        m_BGMPlayName.push_back("None");
    }

    //フォント設定
    FontData* data = new FontData();
    data->fontSize = 25;
    data->fontWeight = DWRITE_FONT_WEIGHT_BOLD;
    data->Color = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f);

    m_WriteActionText = new DirectWrite(data);
    m_WriteActionText->Init();


    GameObject* obj = AddGameObject<GameObject>(Layer3);
    obj->AddComponent<Sprite>()->Init(50, 0, 550.0f, 650.0f,
        "../asset\\texture\\曲リスト.png");

    GameObject* obj2 = AddGameObject<GameObject>(Layer3);
    obj2->AddComponent<Sprite>()->Init(170, -90, 300.0f, 300.0f,
        "../asset\\texture\\曲リスト文字.png");

    GameObject* obj3 = AddGameObject<GameObject>(Layer3);
    obj3->AddComponent<Sprite>()->Init(700, 0, 550.0f, 650.0f,
        "../asset\\texture\\曲リスト.png");

    GameObject* obj4 = AddGameObject<GameObject>(Layer3);
    obj4->AddComponent<Sprite>()->Init(850, -85, 300.0f, 300.0f,
        "../asset\\texture\\再生曲.png");

    //BGM
    for (int i = 0; i < m_BGMName.size(); i++)
    {
        GameObject* audioObj = AddGameObject<GameObject>(Layer3);
        audioObj->AddComponent<Audio>()->Init();
        std::string path = "../asset\\audio\\";
        std::string path2 = m_BGMName[i].c_str();
        std::string path3 = ".wav";
        path.append(path2);
        path.append(path3);
        Audio* audio = audioObj->GetComponent<Audio>();
        audio->Load(path.c_str());
        audio->SetVolume(10.0f);

        m_AudioList.push_back(audioObj);
    }    

    m_AudioList[0]->GetComponent<Audio>()->Play();

    m_Transition = AddGameObject<Transition>(3);
    m_Transition->FadeIn();//フェードイン開始	
}

void BGMScene::Uninit()
{
    for (auto* write : m_WriteList)
    {
        write->Uninit();
        delete write;
    }

    for (int i = 0; i < MAX_PLAYLIST; i++)
    {
        m_WritePlayList[i]->Uninit();
        delete m_WritePlayList[i];
    }

    m_WriteActionText->Uninit();
    delete m_WriteActionText;
}

void BGMScene::Update()
{
    //画面遷移が終了しているか
    if (m_Transition->GetState() == Transition::State::Finish)
    {
        Manager::SetScene<TitleScene>();
        return;
    }

    if (m_Transition->GetState() == Transition::State::Out)
    {        
        return;
    }

    if (m_Transition->GetState() == Transition::State::Stop)
    {
        if (Input::GetGamePadTrigger(BUTTON::BBUTTON))
        {
            m_Transition->FadeOut();
        }
    }

    std::vector<std::string> m_AssetList;

    for (int i = 0; i < MAX_PLAYLIST; i++)
    {
        std::string path = "../asset\\audio\\";
        std::string path2 = m_BGMPlayName[i].c_str();
        std::string path3 = ".wav";
        path.append(path2);
        path.append(path3);

        m_AssetList.push_back(path);
    }   
    Manager::SetBGMList(m_AssetList);

    switch (m_Select)
    {
    case BGMLIST:
        BGMListUpdate();
        break;
    case PLAYLIST:
        PlayListUpdate();
        break;
    case NONELIST:
        break;
    default:
        break;
    }       
}

void BGMScene::Draw()
{
    //画面遷移が終了しているか
    if (m_Transition->GetState() == Transition::State::Finish)
    {        
        return;
    }

    if (m_Transition->GetState() == Transition::State::Out)
    {
        return;
    }

    for (int i = 0; i < m_BGMName.size(); i++)
    {        
        m_WriteList[i]->DrawString(m_BGMName[i].c_str(), Vector2(100, 70 * i + 100), D2D1_DRAW_TEXT_OPTIONS_NONE);
    }

    for (int i = 0; i < m_BGMPlayName.size(); i++)
    {
        m_WritePlayList[i]->DrawString(m_BGMPlayName[i].c_str(), Vector2(650, 70 * i + 100), D2D1_DRAW_TEXT_OPTIONS_NONE);
    }

    m_WriteActionText->DrawString("Bボタン：タイトル画面  Aボタン：リストの切り替え\nYボタン：再生/停止      Xボタン：プレイリストに挿入", Vector2(200, 510), D2D1_DRAW_TEXT_OPTIONS_NONE);
}

void BGMScene::ReadBGMName(const std::string& filename)
{
    std::ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        return;
    }

    std::string line;

    //BGMの名前を取ってくる
    while (std::getline(inputFile, line))
    {       
        m_BGMName.push_back(line);
    }

    inputFile.close();

    return;
}

void BGMScene::BGMListUpdate()
{
    //曲セレクト
    if (Input::GetGamePadTrigger(BUTTON::LUP))
    {
        m_Index--;
    }
    if (Input::GetGamePadTrigger(BUTTON::LDOWN))
    {
        m_Index++;
    }

    //再生
    if (Input::GetGamePadTrigger(BUTTON::YBUTTON))
    {
        if (m_IsPay)
        {
            m_IsPay = false;
            m_AudioList[m_NowPlayIndex]->GetComponent<Audio>()->Stop();
        }
        else
        {
            m_IsPay = true;
            m_AudioList[m_Index]->GetComponent<Audio>()->Play();
            m_NowPlayIndex = m_Index;
        }
    }

    if (Input::GetGamePadTrigger(BUTTON::XBUTTON))
    {
        for (int i = 0; i < m_BGMPlayName.size(); i++)
        {
            //まだ入っていない文字があるならばそこに入れる
            if (m_BGMPlayName[i] == "None")
            {
                m_BGMPlayName[i] = m_BGMName[m_Index];

                return;
            }
        }    

        //全部に入っていたら
        m_BGMPlayName.erase(m_BGMPlayName.begin());
        m_BGMPlayName.push_back(m_BGMName[m_Index]);
    }

    //曲決定
    if (Input::GetGamePadTrigger(BUTTON::ABUTTON))
    {
        //再生曲リストに行く
        m_Select = SELECTLIST::PLAYLIST;

        for (int i = 0; i < m_WriteList.size(); i++)
        {
            m_WriteList[i]->SetFontColor(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
        }

        return;
    }

    if (m_Index <= 0)
    {
        m_Index = 0;
    }
    if (m_Index > m_BGMName.size() - 1)
    {
        m_Index = m_BGMName.size() - 1;
    }

    //選択されてる文字を強調
    //フォント設定  
    m_WriteList[m_Index]->SetFontColor(D2D1::ColorF(1.0f, 0.0f, 0.0f, 1.0f));

    for (int i = 0; i < m_WriteList.size(); i++)
    {
        if (m_Index != i)
        {
            m_WriteList[i]->SetFontColor(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }
}

void BGMScene::PlayListUpdate()
{
    //曲セレクト
    if (Input::GetGamePadTrigger(BUTTON::LUP))
    {
        m_PlayListIndex--;
    }
    if (Input::GetGamePadTrigger(BUTTON::LDOWN))
    {
        m_PlayListIndex++;
    }

    //切り替え
    if (Input::GetGamePadTrigger(BUTTON::ABUTTON))
    {
        //曲リストに行く
        m_Select = SELECTLIST::BGMLIST;

        for (int i = 0; i < MAX_PLAYLIST; i++)
        {           
            m_WritePlayList[i]->SetFontColor(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));            
        }

        return;
    }

    if (m_PlayListIndex <= 0)
    {
        m_PlayListIndex = 0;
    }
    if (m_PlayListIndex > MAX_PLAYLIST -1)
    {
        m_PlayListIndex = MAX_PLAYLIST - 1;
    }

    //選択されてる文字を強調
   //フォント設定  
    m_WritePlayList[m_PlayListIndex]->SetFontColor(D2D1::ColorF(1.0f, 0.0f, 0.0f, 1.0f));

    for (int i = 0; i < MAX_PLAYLIST; i++)
    {
        if (m_PlayListIndex != i)
        {
            m_WritePlayList[i]->SetFontColor(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }
}
