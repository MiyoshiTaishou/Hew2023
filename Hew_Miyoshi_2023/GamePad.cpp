#include "GamePad.h"
#include"Application.h"
#include"Player.h"
#include"scene.h"
#include"manager.h"

using namespace DirectX;

void GamePadComponent::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	//GamePad pad;

	//ゲームパッド取得
	/*player->buttonState = pad.GetState(0);	

	if (!player->buttonState.IsConnected())return;

	this->m_StateTracker.Update(player->buttonState);*/
}