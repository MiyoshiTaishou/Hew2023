#pragma once
#include"scene.h"
#include"../Sysytem/DirectWrite.h"
/**
 * @brief �`���[�g���A���V�[��
 */

//�`���[�g���A���̐i�s�
enum PROGRESS
{
	START,
	MOVE,
	ACTION,
	END,
};

class TutorialScene : public Scene
{
public:

	void Init()override;	
	void Uninit()override;
	void Update()override;
	void Draw()override;	

private:

	//�V�[���J��
	class Transition* m_Transition{};

	//�S�[������
	bool m_Goal = false;

	bool m_TextEnd = false;

	DirectWrite* m_Write;

	std::string m_Text;
	std::vector<std::string> m_TextList;	

	//�e�L�X�g���菈���ϐ�
	float m_Flame = 0;
	int m_TexIdx = 0;
	int m_ListIdx = 0;

	//�i�s�x
	PROGRESS m_Progress = START;
};