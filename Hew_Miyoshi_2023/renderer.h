#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include "Application.h"

// リンクすべき外部ライブラリ
#pragma comment(lib,"directxtk.lib")
#pragma comment(lib,"d3d11.lib")

// ３Ｄ頂点データ
struct VERTEX_3D
{
    DirectX::SimpleMath::Vector3 Position;
    DirectX::SimpleMath::Vector3 Normal;
    DirectX::SimpleMath::Color   Diffuse;
    DirectX::SimpleMath::Vector2 TexCoord;
};

// マテリアル
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

// 平行光源
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
    float gauge1; // ゲージの下限値
    float gauge2; // ゲージの上限値
    float inner;  // 描画する内側の円の半径
    float outer;  // 描画する外側の円の半径
    DirectX::SimpleMath::Vector4 baseColor; // ベースカラー
    DirectX::SimpleMath::Vector4 diffColor; // ゲージがgauge1とgauge2の間の時の色
    DirectX::SimpleMath::Vector4 lostColor; // ゲージがgauge2を超えたときの色
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

// レンダラ
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
     * @brief レンダラの初期化
     * @param[in] ap Applicationクラスへのポインタ
     */
    static void Init(Application* ap);

    /**
     * @brief レンダラの終了処理
     */
    static void Uninit();

    /**
     * @brief 描画開始処理
     */
    static void Begin();

    /**
     * @brief 描画終了処理
     */
    static void End();

    /**
     * @brief 深度バッファを有効または無効に設定
     * @param[in] Enable trueの場合、深度バッファを有効にする
     */
    static void SetDepthEnable(bool Enable);

    /**
     * @brief ATC（アルファトゥカバレッジ）を有効または無効に設定
     * @param[in] Enable trueの場合、ATCを有効にする
     */
    static void SetATCEnable(bool Enable);

    /**
     * @brief 2D用のワールドビュープロジェクション行列を設定
     */
    static void SetWorldViewProjection2D();

    /**
     * @brief ワールド行列を設定
     * @param[in] WorldMatrix ワールド行列
     */
    static void SetWorldMatrix(DirectX::SimpleMath::Matrix* WorldMatrix);

    /**
     * @brief ビュー行列を設定
     * @param[in] ViewMatrix ビュー行列
     */
    static void SetViewMatrix(DirectX::SimpleMath::Matrix* ViewMatrix);

    /**
     * @brief プロジェクション行列を設定
     * @param[in] ProjectionMatrix プロジェクション行列
     */
    static void SetProjectionMatrix(DirectX::SimpleMath::Matrix* ProjectionMatrix);

    /**
     * @brief マテリアルを設定
     * @param[in] Material マテリアル
     */
    static void SetMaterial(MATERIAL Material);

    /**
     * @brief ライトを設定
     * @param[in] Light ライト情報
     */
    static void SetLight(LIGHT Light);

    /**
     * @brief ポーラー効果を設定
     * @param[in] pol ポーラー効果情報
     */
    static void SetPollar(Pollar pol);

    /**
     * @brief フェード効果を設定
     * @param[in] fade フェード効果情報
     */
    static void SetFade(Fade fade);

    /**
     * @brief ブルーム効果を設定
     * @param[in] bloom ブルーム効果情報
     */
    static void SetBloom(Bloom bloom);

    /**
     * @brief 回転角度を設定
     * @param[in] rot 回転角度情報
     */
    static void SetRotationAngle(RotationAngle rot);

    /**
     * @brief スケールシェーダを設定
     * @param[in] scale スケールシェーダ情報
     */
    static void SetScaleShader(ScaleShader scale);

    /**
     * @brief レンダラが使用するDirect3Dデバイスを取得
     * @return ID3D11Deviceへのポインタ
     */
    static ID3D11Device* GetDevice(void) { return m_Device; }

    /**
     * @brief レンダラが使用するDirect3Dデバイスコンテキストを取得
     * @return ID3D11DeviceContextへのポインタ
     */
    static ID3D11DeviceContext* GetDeviceContext(void) { return m_DeviceContext; }

    /**
     * @brief 頂点シェーダと入力レイアウトを作成
     * @param[out] VertexShader 作成される頂点シェーダへのポインタ
     * @param[out] VertexLayout 作成される入力レイアウトへのポインタ
     * @param[in] FileName シェーダファイル名
     */
    static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);

    /**
     * @brief ピクセルシェーダを作成
     * @param[out] PixelShader 作成されるピクセルシェーダへのポインタ
     * @param[in] FileName シェーダファイル名
     */
    static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

    /**
     * @brief ポストプロセス効果を適用
     */
    static void PostProcess();
};
