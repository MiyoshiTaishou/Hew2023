#include "GameScene.h"
#include"../Sysytem/main.h"
#include"../Sysytem/utility.h"

//オブジェクト関係ヘッダ
#include"../Object/BoxObject.h"
#include"../Object/Player.h"
#include"../Object/camera.h"
#include"../Object/sky.h"
#include"../Object/field.h"

using namespace DirectX::SimpleMath;

#define MAX_BOX 10

void GameScene::Init()
{
	//オブジェクト生成
	AddGameObject<Sky>(Layer1);
	AddGameObject<BoxObject>(Layer1);
	AddGameObject<Player>(Layer1);
	AddGameObject<Field>(Layer1);

	AddGameObject<Camera>(Layer0);

	for (int i = 0; i < MAX_BOX; i++)
	{
		BoxObject* box = AddGameObject<BoxObject>(Layer1);
		Vector3 pos = Vector3(5.0f * i, 1.0f, 1.0f);
		box->SetPosition(pos);
	}
}

void GameScene::Update()
{
	
}
