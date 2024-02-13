#include "CPlaneMeshTexture.h"
#include<WICTextureLoader.h>

using namespace DirectX::SimpleMath;

void CPlaneMeshTexture::Init(int divx, int divy, int width, int height, DirectX::SimpleMath::Color color, DirectX::SimpleMath::Vector3 normal, bool xzflag)
{
	CPlaneMesh::Init(divx, divy, width, height, color, normal, xzflag);

	// テクスチャ読み込み
	DirectX::CreateWICTextureFromFile(
		Renderer::GetDevice(),
		L"../asset/texture/field.jpg",
		nullptr,		
		&m_Texture);
}

void CPlaneMeshTexture::Draw()
{
	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
}
