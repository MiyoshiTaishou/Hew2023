#include "GameScene.h"
#include"../Sysytem/main.h"
#include"../Sysytem/utility.h"

//オブジェクト関係ヘッダ
#include"../Object/BoxObject.h"
#include"../Object/Player.h"
#include"../Object/camera.h"
#include"../Object/sky.h"

void GameScene::Init()
{
	//オブジェクト生成
	AddGameObject<Sky>(Layer1);
	AddGameObject<BoxObject>(Layer1);
	AddGameObject<Player>(Layer1);

	AddGameObject<Camera>(Layer0);
}

void GameScene::Update()
{
}
