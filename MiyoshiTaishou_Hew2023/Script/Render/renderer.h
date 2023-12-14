#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include "../Sysytem/Application.h"

// �����N���ׂ��O�����C�u����
#pragma comment(lib, "directxtk.lib")
#pragma comment(lib, "d3d11.lib")

/**
 * @brief �R�c���_�f�[�^�̍\����
 */
struct VERTEX_3D
{
    DirectX::SimpleMath::Vector3 Position; ///< ���_�̈ʒu
    DirectX::SimpleMath::Vector3 Normal;   ///< ���_�̖@��
    DirectX::SimpleMath::Color Diffuse;    ///< ���_�̃f�B�t���[�Y�J���[
    DirectX::SimpleMath::Vector2 TexCoord; ///< �e�N�X�`�����W
    int     BoneIndex[4];
    float   BoneWeight[4];
};

/**
 * @brief �}�e���A���̍\����
 */
struct MATERIAL
{
    DirectX::SimpleMath::Color Ambient;   ///< �A���r�G���g�J���[
    DirectX::SimpleMath::Color Diffuse;   ///< �f�B�t���[�Y�J���[
    DirectX::SimpleMath::Color Specular;  ///< �X�y�L�����J���[
    DirectX::SimpleMath::Color Emission;  ///< �G�~�b�V�����J���[
    float Shininess;                     ///< �V���C�j���O�x
    BOOL TextureEnable;                  ///< �e�N�X�`���L���t���O
    float Dummy[2]{};                    ///< �_�~�[�f�[�^
};

/**
 * @brief ���s�����̍\����
 */
struct LIGHT
{
    BOOL Enable;                             ///< �����̗L�����
    BOOL Dummy[3];
    DirectX::SimpleMath::Vector4 Direction;  ///< �����̕���
    DirectX::SimpleMath::Color Diffuse;      ///< �����̃f�B�t���[�Y�J���[
    DirectX::SimpleMath::Color Ambient;      ///< �����̃A���r�G���g�J���[
};

/**
 * @brief Pollar�i�~�Q�[�W�j�̍\����
 */
struct Pollar
{
    float gauge1;                          ///< �Q�[�W�̉����l
    float gauge2;                          ///< �Q�[�W�̏���l
    float inner;                           ///< �����̉~�̔��a
    float outer;                           ///< �O���̉~�̔��a
    DirectX::SimpleMath::Vector4 baseColor; ///< �x�[�X�J���[
    DirectX::SimpleMath::Vector4 diffColor; ///< �Q�[�W��gauge1��gauge2�̊Ԃ̐F
    DirectX::SimpleMath::Vector4 lostColor; ///< �Q�[�W��gauge2�𒴂����Ƃ��̐F
};

/**
 * @brief �t�F�[�h�̍\����
 */
struct Fade
{
    float alpha;                           ///< �A���t�@�l
    DirectX::SimpleMath::Vector3 dummy;
};

/**
 * @brief �s�N�Z���̈ʒu�ƃe�N�X�`�����W�̍\����
 */
struct VertexPositionTexture
{
    DirectX::XMFLOAT3 pos;               ///< �s�N�Z���̈ʒu
    DirectX::XMFLOAT2 texCoord;         ///< �s�N�Z���̃e�N�X�`�����W
};

/**
 * @brief �u���[�����ʂ̍\����
 */
struct Bloom
{
    float bloom;                         ///< �u���[���x����
    float power;                         ///< �u���[���p���[
    DirectX::SimpleMath::Vector2 dummy;
};

/**
 * @brief ��]�p�x�̍\����
 */
struct RotationAngle
{
    DirectX::SimpleMath::Vector2 rotationAngle; ///< ��]�p�x
    DirectX::SimpleMath::Vector2 dummy;
};

/**
 * @brief �X�P�[���V�F�[�_�̍\����
 */
struct ScaleShader
{
    DirectX::SimpleMath::Vector2 screenSize;     ///< ��ʃT�C�Y
    DirectX::SimpleMath::Vector2 circlePosition;  ///< �~�̈ʒu
    float circleRadius;                          ///< �~�̔��a
    DirectX::SimpleMath::Vector3 dummy;
};

// �u�����h�X�e�[�g
enum EBlendState {
    BS_NONE = 0,							// ��������������
    BS_ALPHABLEND,							// ����������
    BS_ADDITIVE,							// ���Z����
    BS_SUBTRACTION,							// ���Z����

    MAX_BLENDSTATE
};

/**
 * @brief �����_���N���X
 */
class Renderer
{
private:
    static D3D_FEATURE_LEVEL       m_FeatureLevel;
    static ID3D11Device* m_Device;
    static ID3D11DeviceContext* m_DeviceContext;
    static IDXGISwapChain* m_SwapChain;
    static ID3D11RenderTargetView* m_RenderTargetView;
    static ID3D11DepthStencilView* m_DepthStencilView;
    static ID3D11Buffer* m_WorldBuffer;
    static ID3D11Buffer* m_ViewBuffer;
    static ID3D11Buffer* m_ProjectionBuffer;
    static ID3D11Buffer* m_MaterialBuffer;
    static ID3D11Buffer* m_LightBuffer;
    static ID3D11Buffer* m_PollarBuffer;
    static ID3D11Buffer* m_FadeBuffer;
    static ID3D11Buffer* m_BloomBuffer;
    static ID3D11Buffer* m_RotationBuffer;
    static ID3D11Buffer* m_ScaleBuffer;
    static ID3D11DepthStencilState* m_DepthStateEnable;
    static ID3D11DepthStencilState* m_DepthStateDisable;
    static ID3D11BlendState* m_BlendState[MAX_BLENDSTATE];
    static ID3D11BlendState* m_BlendStateATC;
    static Application* m_Application;    

public:
    //�J�����O
    static ID3D11RasterizerState* m_RasterizerState[3];

    /**
     * @brief �����_���̏�����
     * @param ap Application�N���X�ւ̃|�C���^
     */
    static void Init(Application* ap);

    /**
     * @brief �����_���̏I������
     */
    static void Uninit();

    /**
     * @brief �����_�����O�̊J�n
     */
    static void Begin();

    /**
     * @brief �����_�����O�̏I��
     */
    static void End();

    /**
    * @brief �萔�o�b�t�@�̍쐬
    */
    static void CreateConstntBuffer();

    /**
     * @brief �f�v�X�e�X�g�̗L��/������ݒ�
     * @param Enable �L���ɂ���ꍇ��true�A�����ɂ���ꍇ��false
     */
    static void SetDepthEnable(bool Enable);

    /**
     * @brief ATC (Alpha to Coverage) �̗L��/������ݒ�
     * @param Enable �L���ɂ���ꍇ��true�A�����ɂ���ꍇ��false
     */
    static void SetATCEnable(bool Enable);

    /**
     * @brief 2D�`��p�̃��[���h�A�r���[�A�v���W�F�N�V�����s���ݒ�
     */
    static void SetWorldViewProjection2D();

    /**
     * @brief ���[���h�s���ݒ�
     * @param WorldMatrix ���[���h�s��
     */
    static void SetWorldMatrix(DirectX::SimpleMath::Matrix* WorldMatrix);

    /**
     * @brief �r���[�s���ݒ�
     * @param ViewMatrix �r���[�s��
     */
    static void SetViewMatrix(DirectX::SimpleMath::Matrix* ViewMatrix);

    /**
     * @brief �v���W�F�N�V�����s���ݒ�
     * @param ProjectionMatrix �v���W�F�N�V�����s��
     */
    static void SetProjectionMatrix(DirectX::SimpleMath::Matrix* ProjectionMatrix);

    /**
     * @brief �}�e���A����ݒ�
     * @param Material �}�e���A�����
     */
    static void SetMaterial(MATERIAL Material);

    /**
     * @brief ��������ݒ�
     * @param Light �������
     */
    static void SetLight(LIGHT Light);

    /**
     * @brief Pollar�i�~�Q�[�W�j����ݒ�
     * @param pol Pollar���
     */
    static void SetPollar(Pollar pol);

    /**
     * @brief �t�F�[�h����ݒ�
     * @param fade �t�F�[�h���
     */
    static void SetFade(Fade fade);

    /**
     * @brief �u���[������ݒ�
     * @param bloom �u���[�����
     */
    static void SetBloom(Bloom bloom);

    /**
     * @brief ��]�p�x����ݒ�
     * @param rot ��]�p�x���
     */
    static void SetRotationAngle(RotationAngle rot);

    /**
     * @brief �X�P�[���V�F�[�_����ݒ�
     * @param scale �X�P�[���V�F�[�_���
     */
    static void SetScaleShader(ScaleShader scale);

    /**
     * @brief �f�o�C�X�I�u�W�F�N�g���擾
     * @return ID3D11Device�I�u�W�F�N�g�ւ̃|�C���^
     */
    static ID3D11Device* GetDevice(void) { return m_Device; }

    /**
     * @brief �f�o�C�X�R���e�L�X�g�I�u�W�F�N�g���擾
     * @return ID3D11DeviceContext�I�u�W�F�N�g�ւ̃|�C���^
     */
    static ID3D11DeviceContext* GetDeviceContext(void) { return m_DeviceContext; }

    /**
     * @brief ���_�V�F�[�_�𐶐�
     * @param VertexShader �������ꂽ���_�V�F�[�_�ւ̃|�C���^���i�[����ϐ��ւ̃|�C���^
     * @param VertexLayout ���_���C�A�E�g�ւ̃|�C���^���i�[����ϐ��ւ̃|�C���^
     * @param FileName �V�F�[�_�t�@�C���̖��O
     */
    static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);

    /**
     * @brief �s�N�Z���V�F�[�_�𐶐�
     * @param PixelShader �������ꂽ�s�N�Z���V�F�[�_�ւ̃|�C���^���i�[����ϐ��ւ̃|�C���^
     * @param FileName �V�F�[�_�t�@�C���̖��O
     */
    static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

    /**
     * @brief �|�X�g�v���Z�X�����s
     */
    static void PostProcess();

    //=============================================================================
    // �u�����h �X�e�[�g�ݒ�
    //=============================================================================
    static void SetBlendState(int nBlendState)
    {
        if (nBlendState >= 0 && nBlendState < MAX_BLENDSTATE) {
            float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
            m_DeviceContext->OMSetBlendState(m_BlendState[nBlendState], blendFactor, 0xffffffff);
        }
    }
};
