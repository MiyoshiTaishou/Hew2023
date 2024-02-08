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

    //�����������
    DirectWrite* m_WriteActionText;

    //�Đ�
    std::vector<GameObject*> m_AudioList;


    //���ǂ����̃��X�g��I��ł��邩
    SELECTLIST m_Select;

    //���Đ�����
    bool m_IsPay = true;

    //�Ȗ����X�g�֌W
    
    //�Ȗ����X�g
    std::vector<std::string> m_BGMName;

    //�\�����鏈��
    std::vector< DirectWrite*> m_WriteList;

    //���I��ł����
    int m_Index = 0;
    int m_NowPlayIndex = 0;

    //�Đ��Ȋ֌W

    //�Đ��ȃ��X�g
    //3�Ȃ܂Œ������ꍇ�͑I�����ē���ւ�
    std::vector<std::string> m_BGMPlayName;
    
    //�\�����鏈��
    DirectWrite* m_WritePlayList[MAX_PLAYLIST];

    int m_PlayListIndex = 0;

public:
    void Init()override;
    void Uninit()override;
    void Update()override;
    void Draw()override;

    //BGM�I���̎��ɍs������
    void BGMListUpdate();

    //PLAYLIST�I�����ɍs������
    void PlayListUpdate();

    void ReadBGMName(const std::string& filename);
};