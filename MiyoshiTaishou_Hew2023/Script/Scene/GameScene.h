#pragma once
#include"scene.h"
#include"../Sysytem/DirectWrite.h"
/**
 * @brief �Q�[���V�[���Ǘ��N���X
 */

class GameScene : public Scene
{
public:

	void Init()override;
	void Update()override;	
	void Draw()override;

private:

	//�V�[���J��
	class Transition* m_Transition{};

	//�S�[������
	bool m_Goal = false;

	DirectWrite* write;

	std::string text = "����̓e�X�g�ł�";
	std::string pushText = "�ǉ����͑}���e�X�g";

	float flame = 0;
	int texIdx = 0;
};