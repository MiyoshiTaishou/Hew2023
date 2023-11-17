#pragma once
#include"../Object/gameObject.h"

#include <iostream>
#include <unordered_map>
#include <functional>

// �G�̏�Ԃ�\���񋓌^
enum class EnemyState {
	Idle,
	Attack,
	Defend,
	// ���ɂ��K�v�ȏ�Ԃ�����Βǉ����Ă�������
};

class Enemy : public GameObject
{
public:

	void Init();
	void Update();
	void Draw();	
	void PreDraw() override;

	// �e��Ԃɑ΂���֐���o�^����֐�
	void InitializeStateFunctions();

	// ���݂̏�Ԃɉ����Ċ֐������s����֐�
	void ExecuteStateFunction(EnemyState currentState);

private:

	class AnimationModel* m_Model;

	//�ړ����x
	float m_Speed = 30.0f;

	//��]���x
	float m_RotSpeed = 10.0f;

	//���E�̋���
	float m_VisibiltyRange = 30.0f;

	int m_Frame = 0;
	float m_BlendRate = 0;

	//���
	EnemyState m_State = EnemyState::Idle;

	// �G��AI�Ɋ֘A�t����ꂽ�֐���ێ�����}�b�v
	std::unordered_map<EnemyState, std::function<void()>> m_StateFunctions;
};