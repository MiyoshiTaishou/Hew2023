#pragma once

#include	"../Render/renderer.h"
#include	"component.h"
#include	"../Sysytem/utftosjisconv.h"

//2D�|���S���̉摜�\��
//�I�u�W�F�N�g�̈ړ��ɍ��킹�ē���
class PhysicsSprite : public Component
{
private:

	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	MATERIAL					m_Material{};

	//�`��\��
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