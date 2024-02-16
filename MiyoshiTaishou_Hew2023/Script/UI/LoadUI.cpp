#include "LoadUI.h"

#include"../Component/audio.h"
#include"../Component/PhysicsSprite.h"

using namespace DirectX::SimpleMath;

void LoadUI::Init()
{
	AddComponent<PhysicsSprite>()->Init("../asset\\texture\\�����Ă����[�h.png");

	m_Position = Vector3(100, 100, 0);
	m_Scale = Vector3(100, 100, 0);
}

void LoadUI::Update()
{	
	GetComponent<PhysicsSprite>()->Update();

	if (m_Goal)
	{
		//�ړI�n����
		m_StratPos = m_Position;
		m_IntermediatePos = Vector3(rand() % 1500, rand() % 800, 0);
		m_GoalPos = Vector3(rand() % 1500, rand() % 800, 0);

		m_Goal = false;
		m_Rate = 0;
	}
	else
	{
		//�x�W�G�Ȑ�
		Vector3 t1 = Vector3::Lerp(m_StratPos, m_IntermediatePos, m_Rate);
		Vector3 t2 = Vector3::Lerp(m_IntermediatePos, m_GoalPos, m_Rate);
		m_Position = Vector3::Lerp(t1, t2, m_Rate);

		m_Rate += 0.01f;

		if (m_Rate > 1.0f)
		{
			m_Goal = true;
		}
	}
}

void LoadUI::LoadAction(Audio* _audio)
{
	while (!_audio->GetFade())
	{
		this->Update();
		GetComponent<PhysicsSprite>()->Draw();
	}	
}
