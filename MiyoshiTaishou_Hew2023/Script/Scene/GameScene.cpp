#include "GameScene.h"
#include"../Sysytem/main.h"
#include"../Sysytem/utility.h"

//�I�u�W�F�N�g�֌W�w�b�_
#include"../Object/BoxObject.h"
#include"../Object/Player.h"
#include"../Object/camera.h"
#include"../Object/sky.h"
#include"../Object/field.h"

using namespace DirectX::SimpleMath;

void GameScene::Init()
{
	//�I�u�W�F�N�g����
	AddGameObject<Sky>(Layer1);
	AddGameObject<BoxObject>(Layer1);
	AddGameObject<Player>(Layer1);
	AddGameObject<Field>(Layer1);

	AddGameObject<Camera>(Layer0);
}

void GameScene::Update()
{
	Player* player = GetGameObject<Player>();

	//�������擾
	float Height = GetGameObject<Field>()->GetFieldHeight(player->GetPosition());

	Vector3 pos = player->GetPosition();
	pos.y = Height + (player->GetScale().y / 2);

	player->SetPosition(pos);
}
