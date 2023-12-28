#pragma once
#include"scene.h"
#include"../Sysytem/DirectWrite.h"
/**
 * @brief ゲームシーン管理クラス
 */

class GameScene : public Scene
{
public:

	void Init()override;
	void Update()override;	
	void Draw()override;

private:

	//シーン遷移
	class Transition* m_Transition{};

	//ゴール判定
	bool m_Goal = false;

	DirectWrite* write;

	std::string text = "これはテストです";
	std::string pushText = "追加文章挿入テスト";

	float flame = 0;
	int texIdx = 0;
};