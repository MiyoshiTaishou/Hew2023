#pragma once
#include<SimpleMath.h>
#include "component.h"

//���������R���|�[�l���g

// �ǂ̌v�Z�����g����
enum class ForceMode
{
	Force,           ///< ���ʂɈˑ����A�p���I�ȗ͂�^����
	Acceleration,    ///< ���ʂɈˑ������A�p���I�ȗ͂�^����
	Impulse,         ///< ���ʂɈˑ����A�u�ԓI�ȗ͂�^����
	VelocityChange   ///< ���ʂɈˑ������A�u�ԓI�ȗ͂�^����
};

// �Œ�ɂ���ӏ�
enum class Freeze
{
	Xpos,  ///< X���W�̈ʒu���Œ�
	YPos,  ///< Y���W�̈ʒu���Œ�
	ZPos,  ///< Z���W�̈ʒu���Œ�
	XRot,  ///< X���̉�]���Œ�
	YRot,  ///< Y���̉�]���Œ�
	ZRot   ///< Z���̉�]���Œ�
};

/**
 * @brief ���������R���|�[�l���g
 */
class Rigidbody : public Component
{
public:
    using Component::Component;

    /**
     * @brief �R���|�[�l���g�̏�����
     * @param _mass ����
     * @param _drag ���C
     * @param _gravityScale �d�͂̋���
     */
    void Init(float _mass, float _drag, float _gravityScale);

    /**
     * @brief �R���|�[�l���g�̍X�V
     */
    void Update() override;

    /**
     * @brief �R���|�[�l���g�̕`��
     */
    void Draw() override;

    /**
     * @brief �͂�������
     * @param _force �͂̃x�N�g��
     * @param forceMode �͂̌v�Z���[�h
     */
    void AddForce(DirectX::SimpleMath::Vector3 _force, ForceMode forceMode);

    /**
     * @brief ���݂̑��x���擾
     * @return ���x�̃x�N�g��
     */
    DirectX::SimpleMath::Vector3 GetVelocity();

    /**
     * @brief ���x��ݒ�
     * @param _vel ���x�̃x�N�g��
     */
    void SetVelocity(DirectX::SimpleMath::Vector3 _vel);

    /**
     * @brief �͂�ݒ�
     * @param _force �͂̃x�N�g��
     */
    void SetForce(DirectX::SimpleMath::Vector3 _force);

    /**
     * @brief ����̎��̌Œ��ݒ�
     * @param freez �Œ肷�鎲
     * @param _b true�Ȃ�Œ�Afalse�Ȃ�Œ����
     */
    void SetFreeze(Freeze freez, bool _b);

    /**
     * @brief ����̎����Œ肳��Ă��邩�擾
     * @param freez ��
     * @return true�Ȃ�Œ�Afalse�Ȃ�Œ肳��Ă��Ȃ�
     */
    bool GetFreeze(Freeze freez);

    /**
     * @brief ���C�W����ݒ�
     * @param _drag ���C�W��
     */
    void SetDrag(float _drag);

    /**
     * @brief ���C�W����������
     */
    void InitDrag();

private:
    float mass;                       ///< �I�u�W�F�N�g�̎���
    float drag;                       ///< ���C�W��
    float saveDrag;                   ///< ���C�W���̕ۑ��p
    float gravityScale;               ///< �d�͂̋���
    DirectX::SimpleMath::Vector3 velocity; ///< �I�u�W�F�N�g�̌��݂̑��x
    DirectX::SimpleMath::Vector3 force;    ///< �I�u�W�F�N�g�Ɍ��݉������Ă����

    bool mXPos = false;   ///< X���̈ʒu���Œ肷�邩
    bool mYPos = false;   ///< Y���̈ʒu���Œ肷�邩
    bool mZPos = false;   ///< Z���̈ʒu���Œ肷�邩
    bool mXRot = false;   ///< X���̉�]���Œ肷�邩
    bool mYRot = false;   ///< Y���̉�]���Œ肷�邩
    bool mZRot = false;   ///< Z���̉�]���Œ肷�邩
};