#pragma once

#include	<d3d11.h>
#include	<SimpleMath.h>
#include	"Application.h"

// リンクすべき外部ライブラリ
#pragma comment(lib,"directxtk.lib")
#pragma comment(lib,"d3d11.lib")

// ３Ｄ頂点データ
struct VERTEX_3D
{
	DirectX::SimpleMath::Vector3 Position;
	DirectX::SimpleMath::Vector3 Normal;
	DirectX::SimpleMath::Color	Diffuse;
	DirectX::SimpleMath::Vector2 TexCoord;
};


// マテリアル
struct MATERIAL
{
	DirectX::SimpleMath::Color	Ambient;
	DirectX::SimpleMath::Color	Diffuse;
	DirectX::SimpleMath::Color	Specular;
	DirectX::SimpleMath::Color	Emission;
	float		Shininess;
	BOOL		TextureEnable;
	float		Dummy[2]{};
};


// 平行光源
struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];
	DirectX::SimpleMath::Vector4	Direction;
	DirectX::SimpleMath::Color	Diffuse;
	DirectX::SimpleMath::Color	Ambient;
};

struct Pollar
{
	float gauge1;//ゲージの下限値
	float gauge2;//ゲージの上限値
	float inner;//描画する内側の円の半径
	float outer;//描画する外側の円の半径
	DirectX::SimpleMath::Vector4 baseColor;//ベースカラー
	DirectX::SimpleMath::Vector4 diffColor;//ゲージがgauge1とgauge2の間の時の色
	DirectX::SimpleMath::Vector4 lostColor;//ゲージがgauge2を超えたときの色
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

// レンダラ
class Renderer
{
private:

	static D3D_FEATURE_LEVEL       m_FeatureLevel;

	static ID3D11Device*           m_Device;
	static ID3D11DeviceContext*    m_DeviceContext;
	static IDXGISwapChain*         m_SwapChain;
	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;

	static ID3D11Buffer*			m_WorldBuffer;
	static ID3D11Buffer*			m_ViewBuffer;
	static ID3D11Buffer*			m_ProjectionBuffer;
	static ID3D11Buffer*			m_MaterialBuffer;
	static ID3D11Buffer*			m_LightBuffer;
	static ID3D11Buffer*			m_PollarBuffer;
	static ID3D11Buffer*			m_FadeBuffer;
	static ID3D11Buffer*			m_BloomBuffer;


	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;

	static ID3D11BlendState*		m_BlendState;
	static ID3D11BlendState*		m_BlendStateATC;

	static Application* m_Application;

public:
	static void Init(Application* ap);
	static void Uninit();
	static void Begin();
	static void End();

	static void SetDepthEnable(bool Enable);
	static void SetATCEnable(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(DirectX::SimpleMath::Matrix* WorldMatrix);
	static void SetViewMatrix(DirectX::SimpleMath::Matrix* ViewMatrix);
	static void SetProjectionMatrix(DirectX::SimpleMath::Matrix* ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);
	static void SetPollar(Pollar pol);
	static void SetFade(Fade fade);
	static void SetBloom(Bloom bloom);

	static ID3D11Device* GetDevice( void ){ return m_Device; }
	static ID3D11DeviceContext* GetDeviceContext( void ){ return m_DeviceContext; }



	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

	static void PostProcess();
};
