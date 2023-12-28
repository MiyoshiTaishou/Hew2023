#pragma once
#include"scene.h"
#include"../Sysytem/DirectWrite.h"
/**
 * @brief チュートリアルシーン
 */

class TutorialScene : public Scene
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

	std::string text;
	std::vector<std::string> textList;
	std::string pushText = "よう!新入り!たこ焼きを転がすのは初めてって顔だな!";

	float flame = 0;
	int texIdx = 0;
	int listIdx = 0;
};