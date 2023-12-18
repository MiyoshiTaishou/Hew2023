#pragma once


#include "../Object/gameObject.h"
#include "component.h"

class Shader;

class Shadow : public Component
{

private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11ShaderResourceView* m_Texture;

	DirectX::SimpleMath::Vector3 m_Position{};
	float	m_Size = 1.0f;

	Shader* m_Shader;

	//‰e‚ð•`‰æ‚·‚é
	bool m_ShadowView = true;

public:
	using Component::Component;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetSize(float Size) { m_Size = Size; }

	void SetShadowView(bool _view) { m_ShadowView = _view; }

};