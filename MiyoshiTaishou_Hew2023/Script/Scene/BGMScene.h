#pragma once
#include "scene.h"

#define MAX_PLAYLIST 3

class DirectWrite;
class Audio;

enum SELECTLIST
{
    BGMLIST,
    PLAYLIST,
    NONELIST
};

class BGMScene : public Scene
{
private:
    class Transition* m_Transition{};  

    //操作説明文字
    DirectWrite* m_WriteActionText;

    //再生
    std::vector<GameObject*> m_AudioList;


    //今どっちのリストを選んでいるか
    SELECTLIST m_Select;

    //今再生中か
    bool m_IsPay = true;

    //曲名リスト関係
    
    //曲名リスト
    std::vector<std::string> m_BGMName;

    //表示する処理
    std::vector< DirectWrite*> m_WriteList;

    //今選んでいる曲
    int m_Index = 0;
    int m_NowPlayIndex = 0;

    //再生曲関係

    //再生曲リスト
    //3曲まで超えた場合は選択して入れ替え
    std::vector<std::string> m_BGMPlayName;
    
    //表示する処理
    DirectWrite* m_WritePlayList[MAX_PLAYLIST];

    int m_PlayListIndex = 0;

public:
    void Init()override;
    void Uninit()override;
    void Update()override;
    void Draw()override;

    //BGM選択の時に行う処理
    void BGMListUpdate();

    //PLAYLIST選択時に行う処理
    void PlayListUpdate();

    void ReadBGMName(const std::string& filename);
};