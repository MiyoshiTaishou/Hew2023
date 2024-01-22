#pragma once
#include "scene.h"

enum SELECT_SCENE
{
    TUTORIAL,
    GAME1,
    GAME2,
};

class TitleScene : public Scene
{
private:
    class Transition* m_Transition{}; 

    //�V�[���J�ڃt���O
    bool m_Goal = false;

    float currentTime = 1.0f;// ���݂̎��Ԃ��擾���鏈���i�Ⴆ�΁ADirectX�̎��Ԋ֐����g�p����j

    // ���Ԃ��V�F�[�_�[�ɑ��M���邽�߂̒萔�o�b�t�@�̍쐬
    ID3D11Buffer* timeBuffer;
    D3D11_BUFFER_DESC timeBufferDesc;

    // �f�[�^�����邽�߂̍\���̂��쐬���A�f�[�^��ݒ肷��ꍇ
    D3D11_SUBRESOURCE_DATA timeBufferData;

    //SE�炷
    GameObject* m_SEObj;

    SELECT_SCENE m_Select;

    GameObject* m_TitleSprite[3];

    MATERIAL m_TitleMt;
    MATERIAL m_AnyKeyMT;

    bool m_UpDown = true;
    bool m_FadeStart = false;

public:
    void Init()override;
    void Update()override;   

    //�^�C�g����ʂ̃t�F�[�h����
    bool FadeTitle();
};

