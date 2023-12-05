#include "Sphere.h"
#include"../Mesh/CSphereMesh.h"
#include"../Mesh/CMeshRenderer.h"

using namespace DirectX::SimpleMath;

void Sphere::Init()
{
	//‹…‚ÌƒƒbƒVƒ…ì¬
	m_Sphere = new CSphereMesh();
	m_Sphere->Init(1.0f, Color(1, 1, 1, 1), 100, 100);

	m_MeshRenderer = new CMeshRenderer();
	m_MeshRenderer->Init(*m_Sphere);
}


void Sphere::Draw()
{
	m_MeshRenderer->Draw();
}
