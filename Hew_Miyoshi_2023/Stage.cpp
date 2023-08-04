#include "Stage.h"

#include"shader.h"
#include"modelRenderer.h"
#include"StageHit.h"

void Stage::Init()
{
	AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso", "shader\\PS_BloomBlur.cso");
	AddComponent<ModelRenderer>()->Load("asset\\model\\stageobj.obj");

	//�X�e�[�W�̓����蔻��
	StageHitInit(this, "asset\\model\\stageobj.obj");
}

void Stage::Uninit()
{
	StageHitExit();
}
