#pragma once

#include "gameObject.h"
#include "../Render/renderer.h"

//�w�i�I�u�W�F�N�g
class Sky : public GameObject
{

private:

	//�V�F�[�_�[�̒l���������悤�ɂ��邽�߂̕ϐ�
	Bloom bloom;
	RotationAngle rot;

public:
	void Init() override;
	void Init(const char* _name);
	void Update() override;
	void Draw()override;
};