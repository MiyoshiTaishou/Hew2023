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

private:

	//�V�[���J��
	class Transition* m_Transition{};	

	//�S�[������
	bool m_Goal = false;

	float flame = 0;
	int texIdx = 0;	
};