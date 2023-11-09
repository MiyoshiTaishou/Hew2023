#pragma once
#include"CPlaneMesh.h"

class CPlaneMeshTexture : public CPlaneMesh
{
public:
	void Init(int divx, int divy,
		int width, int height,
		DirectX::SimpleMath::Color color,
		DirectX::SimpleMath::Vector3 normal,
		bool xzflag = false);

	void Draw();

private:
	ID3D11ShaderResourceView* m_Texture{};
};
