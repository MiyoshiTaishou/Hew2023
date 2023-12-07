#pragma once

#include"StickObject.h"

class Shader;

class TakoyakiObject : public StickObject
{
public:

	void Init();
	void Draw();

private:

	Shader* m_Shader;
	Shader* m_OutLineShader;	
};

