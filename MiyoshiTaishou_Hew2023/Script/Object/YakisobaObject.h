#pragma once
#include "../Object/gameObject.h"

class Audio;
class BoxCollider;

class YakisobaObject : public GameObject
{
private:

	//SE
	Audio* m_SE;

	//“–‚½‚è”»’è
	BoxCollider* m_Collider;

public:
	void Init();
	void Update();
};