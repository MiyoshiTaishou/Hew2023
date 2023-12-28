#pragma once
#include"scene.h"
#include"../Sysytem/DirectWrite.h"
/**
 * @brief �`���[�g���A���V�[��
 */

class TutorialScene : public Scene
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

	std::string text;
	std::vector<std::string> textList;
	std::string pushText = "�悤!�V����!�����Ă���]�����̂͏��߂Ă��Ċ炾��!";

	float flame = 0;
	int texIdx = 0;
	int listIdx = 0;
};