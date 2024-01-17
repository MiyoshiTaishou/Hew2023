#pragma once
#include"scene.h"
#include"../Sysytem/DirectWrite.h"
/**
 * @brief チュートリアルシーン
 */

//チュートリアルの進行具合
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

	//シーン遷移
	class Transition* m_Transition{};

	//ゴール判定
	bool m_Goal = false;

	bool m_TextEnd = false;

	DirectWrite* m_Write;

	std::string m_Text;
	std::vector<std::string> m_TextList;	

	//テキスト送り処理変数
	float m_Flame = 0;
	int m_TexIdx = 0;
	int m_ListIdx = 0;

	//進行度
	PROGRESS m_Progress = START;
};