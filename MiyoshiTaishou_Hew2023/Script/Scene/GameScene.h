#pragma once
#include"scene.h"

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
};