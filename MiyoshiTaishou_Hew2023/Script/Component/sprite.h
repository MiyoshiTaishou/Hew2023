#pragma once

#include	"../Render/renderer.h"
#include	"component.h"
#include	"../Sysytem/utftosjisconv.h"

//2Dƒ|ƒŠƒSƒ“‚Ì‰æ‘œ•\Ž¦
class Sprite : public Component
{

private:
	ID3D11Buffer*				m_VertexBuffer{};
	ID3D11ShaderResourceView*	m_Texture{};

	MATERIAL					m_Material{};

public:

	using Component::Component;

	void Init(int x, int y, int Width, int Height, const char* TextureName);
	void Uninit() override;
	void Draw() override;

	void SetMaterial(MATERIAL Material) { m_Material = Material; }

};