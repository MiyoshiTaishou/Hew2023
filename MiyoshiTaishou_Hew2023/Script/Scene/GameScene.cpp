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

void GameScene::Init()
{
	//オブジェクト生成
	AddGameObject<Sky>(Layer1);
	AddGameObject<BoxObject>(Layer1);
	AddGameObject<Player>(Layer1);
	AddGameObject<Field>(Layer1);

	AddGameObject<Camera>(Layer0);
}

void GameScene::Update()
{
	Player* player = GetGameObject<Player>();

	//高さを取得
	float Height = GetGameObject<Field>()->GetFieldHeight(player->GetPosition());

	Vector3 pos = player->GetPosition();
	pos.y = Height + (player->GetScale().y / 2);

	player->SetPosition(pos);
}
