#pragma once
#include "../Object/gameObject.h"

class Audio;
class SphereCollider;

class YakisobaObject : public GameObject
{
private:

	//SE
	Audio* m_SE;

	//“–‚½‚è”»’è
	SphereCollider* m_Collider;

public:
	void Init();
	void Update();
};