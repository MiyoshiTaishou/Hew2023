#pragma once

#include "gameObject.h"
#include "renderer.h"

//�w�i�I�u�W�F�N�g
class Sky : public GameObject
{

private:

	//�V�F�[�_�[�̒l���������悤�ɂ��邽�߂̕ϐ�
	Bloom bloom;
	RotationAngle rot;

public:
	void Init() override;
	void Update() override;
	void Draw()override;
};