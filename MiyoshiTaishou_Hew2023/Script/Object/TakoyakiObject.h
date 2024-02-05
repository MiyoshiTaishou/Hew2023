#pragma once

#include"StickObject.h"

class Shader;

class TakoyakiObject : public StickObject
{
public:

	void Init();

private:

	Shader* m_Shader;
	MATERIAL m_MT;
};

