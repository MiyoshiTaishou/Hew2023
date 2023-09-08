/**
 * @file Sahder.h
 * @brief �V�F�[�_���I�u�W�F�N�g�ɓK�p������R���|�[�l���g
 * @author �O�D����
 */
#pragma once

#include "component.h"

class Shader : public Component
{

private:
	ID3D11VertexShader*		m_VertexShader{};
	ID3D11PixelShader*		m_PixelShader{};
	ID3D11InputLayout*		m_VertexLayout{};

public:

	using Component::Component;

	void Load(const char* VertexShader, const char* PixelShader);
	void Uninit() override;
	void Draw() override;

};