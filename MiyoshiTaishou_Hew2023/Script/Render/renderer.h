#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include "../Sysytem/Application.h"

// リンクすべき外部ライブラリ
#pragma comment(lib, "directxtk.lib")
#pragma comment(lib, "d3d11.lib")

/**
 * @brief ３Ｄ頂点データの構造体
 */
struct VERTEX_3D
{
    DirectX::SimpleMath::Vector3 Position; ///< 頂点の位置
    DirectX::SimpleMath::Vector3 Normal;   ///< 頂点の法線
    DirectX::SimpleMath::Color Diffuse;    ///< 頂点のディフューズカラー
    DirectX::SimpleMath::Vector2 TexCoord; ///< テクスチャ座標
    int     BoneIndex[4];
    float   BoneWeight[4];
};

/**
 * @brief マテリアルの構造体
 */
struct MATERIAL
{
    DirectX::SimpleMath::Color Ambient;   ///< アンビエントカラー
    DirectX::SimpleMath::Color Diffuse;   ///< ディフューズカラー
    DirectX::SimpleMath::Color Specular;  ///< スペキュラカラー
    DirectX::SimpleMath::Color Emission;  ///< エミッションカラー
    float Shininess;                     ///< シャイニング度
    BOOL TextureEnable;                  ///< テクスチャ有効フラグ
    float Dummy[2]{};                    ///< ダミーデータ
};

/**
 * @brief 平行光源の構造体
 */
struct LIGHT
{
    BOOL Enable;                             ///< 光源の有効状態
    BOOL Dummy[3];
    DirectX::SimpleMath::Vector4 Direction;  ///< 光源の方向
    DirectX::SimpleMath::Color Diffuse;      ///< 光源のディフューズカラー
    DirectX::SimpleMath::Color Ambient;      ///< 光源のアンビエントカラー
};

/**
 * @brief Pollar（円環ゲージ）の構造体
 */
struct Pollar
{
    float gauge1;                          ///< ゲージの下限値
    float gauge2;                          ///< ゲージの上限値
    float inner;                           ///< 内側の円の半径
    float outer;                           ///< 外側の円の半径
    DirectX::SimpleMath::Vector4 baseColor; ///< ベースカラー
    DirectX::SimpleMath::Vector4 diffColor; ///< ゲージがgauge1とgauge2の間の色
    DirectX::SimpleMath::Vector4 lostColor; ///< ゲージがgauge2を超えたときの色
};

/**
 * @brief フェードの構造体
 */
struct Fade
{
    float alpha;                           ///< アルファ値
    DirectX::SimpleMath::Vector3 dummy;
};

/**
 * @brief ピクセルの位置とテクスチャ座標の構造体
 */
struct VertexPositionTexture
{
    DirectX::XMFLOAT3 pos;               ///< ピクセルの位置
    DirectX::XMFLOAT2 texCoord;         ///< ピクセルのテクスチャ座標
};

/**
 * @brief ブルーム効果の構造体
 */
struct Bloom
{
    float bloom;                         ///< ブルーム度合い
    float power;                         ///< ブルームパワー
    DirectX::SimpleMath::Vector2 dummy;
};

/**
 * @brief 回転角度の構造体
 */
struct RotationAngle
{
    DirectX::SimpleMath::Vector2 rotationAngle; ///< 回転角度
    DirectX::SimpleMath::Vector2 dummy;
};

/**
 * @brief スケールシェーダの構造体
 */
struct ScaleShader
{
    DirectX::SimpleMath::Vector2 screenSize;     ///< 画面サイズ
    DirectX::SimpleMath::Vector2 circlePosition;  ///< 円の位置
    float circleRadius;                          ///< 円の半径
    DirectX::SimpleMath::Vector3 dummy;
};

// ブレンドステート
enum EBlendState {
    BS_NONE = 0,							// 半透明合成無し
    BS_ALPHABLEND,							// 半透明合成
    BS_ADDITIVE,							// 加算合成
    BS_SUBTRACTION,							// 減算合成

    MAX_BLENDSTATE
};

/**
 * @brief レンダラクラス
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
    //カリング
    static ID3D11RasterizerState* m_RasterizerState[3];

    /**
     * @brief レンダラの初期化
     * @param ap Applicationクラスへのポインタ
     */
    static void Init(Application* ap);

    /**
     * @brief レンダラの終了処理
     */
    static void Uninit();

    /**
     * @brief レンダリングの開始
     */
    static void Begin();

    /**
     * @brief レンダリングの終了
     */
    static void End();

    /**
    * @brief 定数バッファの作成
    */
    static void CreateConstntBuffer();

    /**
     * @brief デプステストの有効/無効を設定
     * @param Enable 有効にする場合はtrue、無効にする場合はfalse
     */
    static void SetDepthEnable(bool Enable);

    /**
     * @brief ATC (Alpha to Coverage) の有効/無効を設定
     * @param Enable 有効にする場合はtrue、無効にする場合はfalse
     */
    static void SetATCEnable(bool Enable);

    /**
     * @brief 2D描画用のワールド、ビュー、プロジェクション行列を設定
     */
    static void SetWorldViewProjection2D();

    /**
     * @brief ワールド行列を設定
     * @param WorldMatrix ワールド行列
     */
    static void SetWorldMatrix(DirectX::SimpleMath::Matrix* WorldMatrix);

    /**
     * @brief ビュー行列を設定
     * @param ViewMatrix ビュー行列
     */
    static void SetViewMatrix(DirectX::SimpleMath::Matrix* ViewMatrix);

    /**
     * @brief プロジェクション行列を設定
     * @param ProjectionMatrix プロジェクション行列
     */
    static void SetProjectionMatrix(DirectX::SimpleMath::Matrix* ProjectionMatrix);

    /**
     * @brief マテリアルを設定
     * @param Material マテリアル情報
     */
    static void SetMaterial(MATERIAL Material);

    /**
     * @brief 光源情報を設定
     * @param Light 光源情報
     */
    static void SetLight(LIGHT Light);

    /**
     * @brief Pollar（円環ゲージ）情報を設定
     * @param pol Pollar情報
     */
    static void SetPollar(Pollar pol);

    /**
     * @brief フェード情報を設定
     * @param fade フェード情報
     */
    static void SetFade(Fade fade);

    /**
     * @brief ブルーム情報を設定
     * @param bloom ブルーム情報
     */
    static void SetBloom(Bloom bloom);

    /**
     * @brief 回転角度情報を設定
     * @param rot 回転角度情報
     */
    static void SetRotationAngle(RotationAngle rot);

    /**
     * @brief スケールシェーダ情報を設定
     * @param scale スケールシェーダ情報
     */
    static void SetScaleShader(ScaleShader scale);

    /**
     * @brief デバイスオブジェクトを取得
     * @return ID3D11Deviceオブジェクトへのポインタ
     */
    static ID3D11Device* GetDevice(void) { return m_Device; }

    /**
     * @brief デバイスコンテキストオブジェクトを取得
     * @return ID3D11DeviceContextオブジェクトへのポインタ
     */
    static ID3D11DeviceContext* GetDeviceContext(void) { return m_DeviceContext; }

    /**
     * @brief 頂点シェーダを生成
     * @param VertexShader 生成された頂点シェーダへのポインタを格納する変数へのポインタ
     * @param VertexLayout 頂点レイアウトへのポインタを格納する変数へのポインタ
     * @param FileName シェーダファイルの名前
     */
    static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);

    /**
     * @brief ピクセルシェーダを生成
     * @param PixelShader 生成されたピクセルシェーダへのポインタを格納する変数へのポインタ
     * @param FileName シェーダファイルの名前
     */
    static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

    /**
     * @brief ポストプロセスを実行
     */
    static void PostProcess();

    //=============================================================================
    // ブレンド ステート設定
    //=============================================================================
    static void SetBlendState(int nBlendState)
    {
        if (nBlendState >= 0 && nBlendState < MAX_BLENDSTATE) {
            float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
            m_DeviceContext->OMSetBlendState(m_BlendState[nBlendState], blendFactor, 0xffffffff);
        }
    }
};
