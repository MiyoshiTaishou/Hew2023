#pragma once
#include"scene.h"

/**
 * @brief ゲームシーン管理クラス
 */

class GameScene : public Scene
{
public:

	void Init()override;
	void Update()override;	

private:

	//シーン遷移
	class Transition* m_Transition{};

	//ゴール判定
	bool m_Goal = false;
};