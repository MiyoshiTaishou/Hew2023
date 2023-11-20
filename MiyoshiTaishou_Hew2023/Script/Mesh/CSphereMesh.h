#pragma once
#include<simplemath.h>
#include"CMesh.h"

class CSphereMesh : public CMesh
{
	// 頂点座標をノーマライズ
	void Normalize(DirectX::SimpleMath::Vector3 vec, DirectX::SimpleMath::Vector3& Normal);

public:
	void Init(float radius,
		DirectX::SimpleMath::Color color,
		int division_horizontal,
		int division_vertical);
	void CreateVertex();
	void CreateIndex();

private:
	unsigned int m_divX = 1;
	unsigned int m_divY = 1;
	float m_radius = 100.0f;
	DirectX::SimpleMath::Color m_color;
};
