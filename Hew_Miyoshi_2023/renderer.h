#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include "Application.h"

// �����N���ׂ��O�����C�u����
#pragma comment(lib,"directxtk.lib")
#pragma comment(lib,"d3d11.lib")

// �R�c���_�f�[�^
struct VERTEX_3D
{
    DirectX::SimpleMath::Vector3 Position;
    DirectX::SimpleMath::Vector3 Normal;
    DirectX::SimpleMath::Color   Diffuse;
    DirectX::SimpleMath::Vector2 TexCoord;
};

// �}�e���A��
struct MATERIAL
{
    DirectX::SimpleMath::Color Ambient;
    DirectX::SimpleMath::Color Diffuse;
    DirectX::SimpleMath::Color Specular;
    DirectX::SimpleMath::Color Emission;
    float Shininess;
    BOOL TextureEnable;
    float Dummy[2]{};
};

// ���s����
struct LIGHT
{
    BOOL Enable;
    BOOL Dummy[3];
    DirectX::SimpleMath::Vector4 Direction;
    DirectX::SimpleMath::Color Diffuse;
    DirectX::SimpleMath::Color Ambient;
};

struct Pollar
{
    float gauge1; // �Q�[�W�̉����l
    float gauge2; // �Q�[�W�̏���l
    float inner;  // �`�悷������̉~�̔��a
    float outer;  // �`�悷��O���̉~�̔��a
    DirectX::SimpleMath::Vector4 baseColor; // �x�[�X�J���[
    DirectX::SimpleMath::Vector4 diffColor; // �Q�[�W��gauge1��gauge2�̊Ԃ̎��̐F
    DirectX::SimpleMath::Vector4 lostColor; // �Q�[�W��gauge2�𒴂����Ƃ��̐F
};

struct Fade
{
    float alpha;
    DirectX::SimpleMath::Vector3 dummy;
};

struct VertexPositionTexture
{
    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT2 texCoord;
};

struct Bloom
{
    float bloom;
    float power;
    DirectX::SimpleMath::Vector2 dummy;
};

struct RotationAngle
{
    DirectX::SimpleMath::Vector2 rotationAngle;
    DirectX::SimpleMath::Vector2 dummy;
};

struct ScaleShader
{
    DirectX::SimpleMath::Vector2 screenSize;
    DirectX::SimpleMath::Vector2 circlePosition;
    float circleRadius;
    DirectX::SimpleMath::Vector3 dummy;
};

// �����_��
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

    static ID3D11BlendState* m_BlendState;
    static ID3D11BlendState* m_BlendStateATC;

    static Application* m_Application;

public:
    /**
     * @brief �����_���̏�����
     * @param[in] ap Application�N���X�ւ̃|�C���^
     */
    static void Init(Application* ap);

    /**
     * @brief �����_���̏I������
     */
    static void Uninit();

    /**
     * @brief �`��J�n����
     */
    static void Begin();

    /**
     * @brief �`��I������
     */
    static void End();

    /**
     * @brief �[�x�o�b�t�@��L���܂��͖����ɐݒ�
     * @param[in] Enable true�̏ꍇ�A�[�x�o�b�t�@��L���ɂ���
     */
    static void SetDepthEnable(bool Enable);

    /**
     * @brief ATC�i�A���t�@�g�D�J�o���b�W�j��L���܂��͖����ɐݒ�
     * @param[in] Enable true�̏ꍇ�AATC��L���ɂ���
     */
    static void SetATCEnable(bool Enable);

    /**
     * @brief 2D�p�̃��[���h�r���[�v���W�F�N�V�����s���ݒ�
     */
    static void SetWorldViewProjection2D();

    /**
     * @brief ���[���h�s���ݒ�
     * @param[in] WorldMatrix ���[���h�s��
     */
    static void SetWorldMatrix(DirectX::SimpleMath::Matrix* WorldMatrix);

    /**
     * @brief �r���[�s���ݒ�
     * @param[in] ViewMatrix �r���[�s��
     */
    static void SetViewMatrix(DirectX::SimpleMath::Matrix* ViewMatrix);

    /**
     * @brief �v���W�F�N�V�����s���ݒ�
     * @param[in] ProjectionMatrix �v���W�F�N�V�����s��
     */
    static void SetProjectionMatrix(DirectX::SimpleMath::Matrix* ProjectionMatrix);

    /**
     * @brief �}�e���A����ݒ�
     * @param[in] Material �}�e���A��
     */
    static void SetMaterial(MATERIAL Material);

    /**
     * @brief ���C�g��ݒ�
     * @param[in] Light ���C�g���
     */
    static void SetLight(LIGHT Light);

    /**
     * @brief �|�[���[���ʂ�ݒ�
     * @param[in] pol �|�[���[���ʏ��
     */
    static void SetPollar(Pollar pol);

    /**
     * @brief �t�F�[�h���ʂ�ݒ�
     * @param[in] fade �t�F�[�h���ʏ��
     */
    static void SetFade(Fade fade);

    /**
     * @brief �u���[�����ʂ�ݒ�
     * @param[in] bloom �u���[�����ʏ��
     */
    static void SetBloom(Bloom bloom);

    /**
     * @brief ��]�p�x��ݒ�
     * @param[in] rot ��]�p�x���
     */
    static void SetRotationAngle(RotationAngle rot);

    /**
     * @brief �X�P�[���V�F�[�_��ݒ�
     * @param[in] scale �X�P�[���V�F�[�_���
     */
    static void SetScaleShader(ScaleShader scale);

    /**
     * @brief �����_�����g�p����Direct3D�f�o�C�X���擾
     * @return ID3D11Device�ւ̃|�C���^
     */
    static ID3D11Device* GetDevice(void) { return m_Device; }

    /**
     * @brief �����_�����g�p����Direct3D�f�o�C�X�R���e�L�X�g���擾
     * @return ID3D11DeviceContext�ւ̃|�C���^
     */
    static ID3D11DeviceContext* GetDeviceContext(void) { return m_DeviceContext; }

    /**
     * @brief ���_�V�F�[�_�Ɠ��̓��C�A�E�g���쐬
     * @param[out] VertexShader �쐬����钸�_�V�F�[�_�ւ̃|�C���^
     * @param[out] VertexLayout �쐬�������̓��C�A�E�g�ւ̃|�C���^
     * @param[in] FileName �V�F�[�_�t�@�C����
     */
    static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);

    /**
     * @brief �s�N�Z���V�F�[�_���쐬
     * @param[out] PixelShader �쐬�����s�N�Z���V�F�[�_�ւ̃|�C���^
     * @param[in] FileName �V�F�[�_�t�@�C����
     */
    static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

    /**
     * @brief �|�X�g�v���Z�X���ʂ�K�p
     */
    static void PostProcess();
};
