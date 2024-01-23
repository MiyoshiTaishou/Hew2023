#include "HitUI.h"

//�V�[��
#include"../Scene/scene.h"

//�}�l�[�W���[
#include"../Sysytem/manager.h"

//�R���|�[�l���g
#include"../Component/shader.h"
#include"../Component/sprite.h"

using namespace DirectX::SimpleMath;

void HitUI::Init()
{
	Scene* scene = Manager::GetScene();

	//�ۂ��摜
	m_Hit[0] = scene->AddGameObject<GameObject>(Layer3);// 3�̓��C���ԍ�
	m_Hit[0]->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");
	m_Hit[0]->AddComponent<Sprite>()->Init(0.0f, 450.0f, 480.0f, 240.0f,
		"../asset\\texture\\�ۂ�.png");

	m_Hit[1] = scene->AddGameObject<GameObject>(Layer3);// 3�̓��C���ԍ�
	m_Hit[1]->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");
	m_Hit[1]->AddComponent<Sprite>()->Init(800.0f, 0.0f, 480.0f, 240.0f,
		"../asset\\texture\\�ۂ�.png");

	//�҂��摜
	m_Hit[2] = scene->AddGameObject<GameObject>(Layer3);// 3�̓��C���ԍ�
	m_Hit[2]->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");
	m_Hit[2]->AddComponent<Sprite>()->Init(0.0f, 0.0f, 480.0f, 240.0f,
		"../asset\\texture\\�҂�.png");

	m_Hit[3] = scene->AddGameObject<GameObject>(Layer3);// 3�̓��C���ԍ�
	m_Hit[3]->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");
	m_Hit[3]->AddComponent<Sprite>()->Init(800.0f, 450.0f, 480.0f, 240.0f,
		"../asset\\texture\\�҂�.png");

	m_MT[0].TextureEnable = true;
	m_MT[0].Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);

}

void HitUI::Update()
{

}
