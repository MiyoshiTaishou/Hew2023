#pragma once


#include "gameObject.h"
#include "component.h"
//#include"shader.h"

class Shadow : public Component
{

private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11ShaderResourceView* m_Texture;
	ID3D11PixelShader* m_PixelShader{};

	DirectX::SimpleMath::Vector3 m_Position{};
	float	m_Size = 1.0f;
	float m_Alpha = 1.0f;
	float m_MaxDistance = 100.0f;

	Fade pollar;

public:
	using Component::Component;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetSize(float Size) { m_Size = Size; }

};