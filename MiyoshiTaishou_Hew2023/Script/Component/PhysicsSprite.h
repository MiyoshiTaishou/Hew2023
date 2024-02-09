#pragma once

#include	"../Render/renderer.h"
#include	"component.h"
#include	"../Sysytem/utftosjisconv.h"

//2Dポリゴンの画像表示
//オブジェクトの移動に合わせて動く
class PhysicsSprite : public Component
{
private:

	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	MATERIAL					m_Material{};

	//描画可能か
	bool						m_View = true;

public:

	using Component::Component;

	PhysicsSprite();

	void Init(const char* TextureName);
	void Uninit() override;
	void Draw() override;
	void Update()override;

	void SetMaterial(MATERIAL Material) { m_Material = Material; }
	void SetView(bool _view) { m_View = _view; }

};