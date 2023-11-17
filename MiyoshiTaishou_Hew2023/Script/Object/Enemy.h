#pragma once
#include"../Object/gameObject.h"

#include <iostream>
#include <unordered_map>
#include <functional>

// 敵の状態を表す列挙型
enum class EnemyState {
	Idle,
	Attack,
	Defend,
	// 他にも必要な状態があれば追加してください
};

class Enemy : public GameObject
{
public:

	void Init();
	void Update();
	void Draw();	
	void PreDraw() override;

	// 各状態に対する関数を登録する関数
	void InitializeStateFunctions();

	// 現在の状態に応じて関数を実行する関数
	void ExecuteStateFunction(EnemyState currentState);

private:

	class AnimationModel* m_Model;

	//移動速度
	float m_Speed = 30.0f;

	//回転速度
	float m_RotSpeed = 10.0f;

	//視界の距離
	float m_VisibiltyRange = 30.0f;

	int m_Frame = 0;
	float m_BlendRate = 0;

	//状態
	EnemyState m_State = EnemyState::Idle;

	// 敵のAIに関連付けられた関数を保持するマップ
	std::unordered_map<EnemyState, std::function<void()>> m_StateFunctions;
};