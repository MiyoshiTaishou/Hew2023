#pragma once
#include "scene.h"

// �񋓌^�ŃN���X�̎�ނ��Ǘ�
enum CLASS
{
    BOX,   /**< �{�b�N�X�N���X */
    ENEMY, /**< �G�l�~�[�N���X */
    NONE,  /**< �Ȃ� */
};

/**
 * @brief �I�u�W�F�N�g�̏��f�[�^�\����
 */
struct InfoObjData
{
    CLASS ClassKind;                          /**< �N���X�̎�� */
    DirectX::SimpleMath::Vector3 pos;         /**< �ʒu */
    DirectX::SimpleMath::Vector3 scale;       /**< �X�P�[�� */
    DirectX::SimpleMath::Vector3 rot;         /**< ��] */
};

/**
 * @brief �X�e�[�W���쐬����V�[�� StageEditor �N���X
 */
class StageEditor : public Scene
{
public:
   
    void Init() override;
    void Update() override;   
    void Draw() override;

    /**
     * @brief �I�u�W�F�N�g�����t�@�C���ɕۑ�����֐�
     * @param filename �ۑ���̃t�@�C����
     */
    void SavepositionToFile(const std::string& filename);

    /**
     * @brief �I�u�W�F�N�g�����t�@�C������ǂݍ��ފ֐�
     * @param filename �ǂݍ��ރt�@�C����
     */
    void LoadpositionToFile(const std::string& filename);

    /**
     * @brief �I�u�W�F�N�g���쐬����֐�
     */
    void CreateObject();

    /**
     * @brief �����ɃI�u�W�F�N�g����ǉ�����֐�
     */
    void AddToHistory();

    /**
     * @brief �A���h�D�i�������j����֐�
     */
    void Undo();

    /**
     * @brief ���h�D�i��蒼���j����֐�
     */
    void Redo();

private:
    // �����Ǘ��p�̃R���e�i
    std::array<std::list<InfoObjData>, 4> history;
    std::vector<InfoObjData> position;
    std::vector<GameObject*> objList;
    int historyIndex = 0;
};
