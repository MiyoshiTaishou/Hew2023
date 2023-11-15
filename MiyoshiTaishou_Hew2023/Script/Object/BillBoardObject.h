#pragma once
#include "../Object/gameObject.h"

class BillBoardObject : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};	

public:
	void Init();
	void Uninit();
	void Draw();	
	void Update();
};