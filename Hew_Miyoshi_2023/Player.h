#pragma once

#include "gameObject.h"
#include <SimpleMath.h>
#include <vector>
#include "GamePad.h"

/**
 * @brief ���삷��L�����N�^�[�̃N���X�ł��B
 */
class Player : public GameObject
{
public:
    /**
     * @brief �v���C���[�I�u�W�F�N�g�̏��������s���܂��B
     */
    void Init() override;

    /**
     * @brief �v���C���[�I�u�W�F�N�g�̍X�V�������s���܂��B
     */
    void Update() override;

    /**
     * @brief �v���C���[�I�u�W�F�N�g�̕`�揈�����s���܂��B
     */
    void Draw() override;

    /**
    * @brief �v���C���[�I�u�W�F�N�g�̃R���g���[���[�������s���܂��B
    */
    void ConInput();

    /**
    * @brief �v���C���[�I�u�W�F�N�g�̓����蔻�菈�����s���܂��B
    */
    void Collison();

private:
    /**
     * @brief �v���C���[�̑��x�x�N�g���ł��B
     */
    DirectX::SimpleMath::Vector3 m_Velocity{};

    /**
     * @brief SE�i���ʉ��j���Đ����邽�߂̃I�u�W�F�N�g�ł��B
     */
    class Audio* m_SE{};

    /**
     * @brief ����SE�i���ʉ��j���Đ����邽�߂̃I�u�W�F�N�g�ł��B
     */
    class Audio* m_MeatSE{};

    /**
     * @brief ������̓���SE�i���ʉ��j���Đ����邽�߂̃I�u�W�F�N�g�ł��B
     */
    class Audio* m_MeatSE2{};

    /**
     * @brief �q�I�u�W�F�N�g�̃��X�g�ł��B
     */
    std::list<GameObject*> m_Children;

    /**
     * @brief �q�I�u�W�F�N�g�̈�ł��B
     */
    GameObject* mchild;

    /**
     * @brief ��̑傫���ł��B
     */
    float m_Size;

    /**
     * @brief �_�b�V���p�̃J�E���g�ϐ��ł��B
     */
    int loopCount = 0;

    /**
     * @brief �_�b�V���̎�t���Ԃ�\���ϐ��ł��B
     */
    int reception = 60;

    /**
     * @brief �A�N�V�����̃J�E���g�ϐ��ł��B
     */
    int actionCount = 0;

    /**
     * @brief �_�b�V���A�N�V�����p�̃J�E���g�ϐ��ł��B
     */
    int actionDashu = 5;

    /**
     * @brief �A�N�V�����̗L�����������t���O�ł��B
     */
    bool actionCheck = false;

    /**
     * @brief �ǂ�o�邽�߂̃t���O�ł��B
     */
    bool wallUp = false;

    /**
     * @brief�O��̍��W��ۑ�����ϐ�
     */
    DirectX::SimpleMath::Vector3 m_OldPos;

    /**
     * @brief ���_���W�̃��X�g�ł��B
     */
    std::vector<DirectX::SimpleMath::Vector3> m_VertexPos;
};
