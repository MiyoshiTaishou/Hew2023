#pragma once
#include "../Object/gameObject.h"

class Audio;
class BoxCollider;

class YakisobaObject : public GameObject
{
private:

	//SE
	Audio* m_SE;

	//�����蔻��
	BoxCollider* m_Collider;

public:
	void Init();
	void Update();
};