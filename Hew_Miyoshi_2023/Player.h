#pragma once
#include "gameObject.h"
#include <SimpleMath.h>
#include <vector>
#include "GamePad.h"

/**
 * @brief �v���C���[�L�����N�^�[
 *
 * ���̃N���X�̓v���C���[�L�����N�^�[��\���܂��B
 */
class Player : public GameObject
{
public:
    /**
     * @brief �v���C���[�̏�����
     *
     * �v���C���[�L�����N�^�[�̏������������s���܂��B
     */
    void Init() override;

    /**
     * @brief �v���C���[�̏I������
     *
     * �v���C���[�L�����N�^�[�̏I���������s���܂��B
     */
    void Uninit() override;

    /**
     * @brief �v���C���[�̍X�V
     *
     * �v���C���[�L�����N�^�[�̏�Ԃ��X�V���鏈�����s���܂��B
     */
    void Update() override;

    /**
     * @brief �v���C���[�̕`��
     *
     * �v���C���[�L�����N�^�[�̕`�揈�����s���܂��B
     */
    void Draw() override;

    DirectX::GamePad::State buttonState; ///< �v���C���[�L�����N�^�[�̃{�^�����

private:
    DirectX::SimpleMath::Vector3 m_Velocity{}; ///< �v���C���[�L�����N�^�[�̑��x
    class Audio* m_SE{}; ///< ���ʉ��I�u�W�F�N�g
    class Audio* m_MeatSE{}; ///< ���������Ƃ��̌��ʉ��I�u�W�F�N�g
    class Audio* m_MeatSE2{}; ///< ���������Ƃ��̌��ʉ��I�u�W�F�N�g�i2�ځj

    std::list<GameObject*> m_Children; ///< �v���C���[�L�����N�^�[�̎q�I�u�W�F�N�g���X�g
    GameObject* mchild; ///< �q�I�u�W�F�N�g

    // ��̑傫��
    float m_Size;

    // �_�b�V���p�ϐ�
    int loopCount = 0;
    int reception = 60;
    int actionCount = 0;
    int actionDashu = 5;
    bool actionCheck = false;

    // �Ǔo��p�ϐ�
    bool wallUp = false;

    // ���_���W
    std::vector<DirectX::SimpleMath::Vector3> m_VertexPos;
};
