#pragma once
#include "scene.h"
class TitleScene : public Scene
{
private:
    class Transition* m_Transition{}; 

    //�V�[���J�ڃt���O
    bool m_Goal = false;

    float currentTime = 0.0f;// ���݂̎��Ԃ��擾���鏈���i�Ⴆ�΁ADirectX�̎��Ԋ֐����g�p����j

    // ���Ԃ��V�F�[�_�[�ɑ��M���邽�߂̒萔�o�b�t�@�̍쐬
    ID3D11Buffer* timeBuffer;
    D3D11_BUFFER_DESC timeBufferDesc;

    // �f�[�^�����邽�߂̍\���̂��쐬���A�f�[�^��ݒ肷��ꍇ
    D3D11_SUBRESOURCE_DATA timeBufferData;
public:
    void Init()override;
    void Update()override;   
};

