#include "../Sysytem/main.h"
#include "../Sysytem/main.h"
#include "renderer.h"
#include <io.h>
#include<iostream>

using namespace DirectX::SimpleMath;

D3D_FEATURE_LEVEL       Renderer::m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device*           Renderer::m_Device{};
ID3D11DeviceContext*    Renderer::m_DeviceContext{};
IDXGISwapChain*         Renderer::m_SwapChain{};
ID3D11RenderTargetView* Renderer::m_RenderTargetView{};
ID3D11DepthStencilView* Renderer::m_DepthStencilView{};

ID3D11Buffer*			Renderer::m_WorldBuffer{};
ID3D11Buffer*			Renderer::m_ViewBuffer{};
ID3D11Buffer*			Renderer::m_ProjectionBuffer{};
ID3D11Buffer*			Renderer::m_MaterialBuffer{};
ID3D11Buffer*			Renderer::m_LightBuffer{};
ID3D11Buffer*			Renderer::m_PollarBuffer{};
ID3D11Buffer*			Renderer::m_FadeBuffer{};
ID3D11Buffer*			Renderer::m_BloomBuffer{};
ID3D11Buffer*			Renderer::m_RotationBuffer{};
ID3D11Buffer*			Renderer::m_ScaleBuffer{};


ID3D11DepthStencilState* Renderer::m_DepthStateEnable{};
ID3D11DepthStencilState* Renderer::m_DepthStateDisable{};


ID3D11BlendState*		Renderer::m_BlendState[MAX_BLENDSTATE]{};
ID3D11BlendState*		Renderer::m_BlendStateATC{};
ID3D11RasterizerState*	Renderer::m_RasterizerState[3]{};

Application*			Renderer::m_Application;


void Renderer::Init(Application* ap)
{
	HRESULT hr = S_OK;

	// ������I�u�W�F�N�g�̃A�h���X���Z�b�g
	m_Application = ap;

	// �f�o�C�X�A�X���b�v�`�F�[���쐬
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = m_Application->GetWidth();
	swapChainDesc.BufferDesc.Height = m_Application->GetHeight();
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = m_Application->GetWindow();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain( NULL,
										D3D_DRIVER_TYPE_HARDWARE,
										NULL,
										D3D11_CREATE_DEVICE_BGRA_SUPPORT,
										NULL,
										0,
										D3D11_SDK_VERSION,
										&swapChainDesc,
										&m_SwapChain,
										&m_Device,
										&m_FeatureLevel,
										&m_DeviceContext );






	// �����_�[�^�[�Q�b�g�r���[�쐬
	ID3D11Texture2D* renderTarget{};
	m_SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&renderTarget );
	m_Device->CreateRenderTargetView( renderTarget, NULL, &m_RenderTargetView );
	renderTarget->Release();


	// �f�v�X�X�e���V���o�b�t�@�쐬
	ID3D11Texture2D* depthStencile{};
	D3D11_TEXTURE2D_DESC textureDesc{};
	textureDesc.Width = swapChainDesc.BufferDesc.Width;
	textureDesc.Height = swapChainDesc.BufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	m_Device->CreateTexture2D(&textureDesc, NULL, &depthStencile);

	// �f�v�X�X�e���V���r���[�쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	m_Device->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &m_DepthStencilView);

	// ID3D11ShaderResourceView�̍쐬
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc{};
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	ID3D11ShaderResourceView* m_ShaderResourceView = nullptr;
	HRESULT result = m_Device->CreateShaderResourceView(depthStencile, &shaderResourceViewDesc, &m_ShaderResourceView);

	m_DeviceContext->PSSetShaderResources(1, 1, &m_ShaderResourceView);

	if (FAILED(result)) {
		// �G���[����
	}

	depthStencile->Release();


	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);


	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)m_Application->GetWidth();
	viewport.Height = (FLOAT)m_Application->GetHeight();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	m_DeviceContext->RSSetViewports( 1, &viewport );



	// ���X�^���C�U�X�e�[�g�ݒ�
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	D3D11_CULL_MODE cull[] = {
		D3D11_CULL_NONE,
		D3D11_CULL_FRONT,
		D3D11_CULL_BACK
	};
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.MultisampleEnable = FALSE; 
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	//rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
	rasterizerDesc.FrontCounterClockwise = true;

	for (int i = 0; i < 3; ++i)
	{
		rasterizerDesc.CullMode = cull[i];
		hr = m_Device->CreateRasterizerState(&rasterizerDesc, &m_RasterizerState[i]);		
	}	

	m_DeviceContext->RSSetState(m_RasterizerState[1]);

	// �u�����h �X�e�[�g����
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = FALSE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	m_Device->CreateBlendState(&BlendDesc, &m_BlendState[0]);

	// �u�����h �X�e�[�g���� (�A���t�@ �u�����h�p)
	//BlendDesc.AlphaToCoverageEnable = TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	m_Device->CreateBlendState(&BlendDesc, &m_BlendState[1]);

	// �u�����h �X�e�[�g���� (���Z�����p)
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	m_Device->CreateBlendState(&BlendDesc, &m_BlendState[2]);

	// �u�����h �X�e�[�g���� (���Z�����p)
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	m_Device->CreateBlendState(&BlendDesc, &m_BlendState[3]);

	SetBlendState(BS_ALPHABLEND);

	// �f�v�X�X�e���V���X�e�[�g�ݒ�
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	m_Device->CreateDepthStencilState( &depthStencilDesc, &m_DepthStateEnable );//�[�x�L���X�e�[�g

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ZERO;
	m_Device->CreateDepthStencilState( &depthStencilDesc, &m_DepthStateDisable );//�[�x�����X�e�[�g

	m_DeviceContext->OMSetDepthStencilState( m_DepthStateEnable, NULL );

	// �T���v���[�X�e�[�g�ݒ�
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MaxAnisotropy = 4;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState{};
	m_Device->CreateSamplerState( &samplerDesc, &samplerState );

	m_DeviceContext->PSSetSamplers( 0, 1, &samplerState );

	//�萔�o�b�t�@�̍쐬
	CreateConstntBuffer();	
}



void Renderer::Uninit()
{
	m_WorldBuffer->Release();
	m_ViewBuffer->Release();
	m_ProjectionBuffer->Release();
	m_LightBuffer->Release();
	m_MaterialBuffer->Release();
	m_PollarBuffer->Release();
	m_FadeBuffer->Release();
	m_RotationBuffer->Release();
	m_ScaleBuffer->Release();	

	m_DeviceContext->ClearState();
	m_RenderTargetView->Release();
	m_SwapChain->Release();
	m_DeviceContext->Release();
	m_Device->Release();
}




void Renderer::Begin()
{
	float clearColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_DeviceContext->ClearRenderTargetView( m_RenderTargetView, clearColor );
	m_DeviceContext->ClearDepthStencilView( m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}



void Renderer::End()
{
	m_SwapChain->Present( 1, 0 );
}

void Renderer::CreateConstntBuffer()
{
	// �萔�o�b�t�@����
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(Matrix);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = sizeof(float);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_WorldBuffer);
	m_DeviceContext->VSSetConstantBuffers(0, 1, &m_WorldBuffer);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_ViewBuffer);
	m_DeviceContext->VSSetConstantBuffers(1, 1, &m_ViewBuffer);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_ProjectionBuffer);
	m_DeviceContext->VSSetConstantBuffers(2, 1, &m_ProjectionBuffer);


	bufferDesc.ByteWidth = sizeof(MATERIAL);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_MaterialBuffer);
	m_DeviceContext->VSSetConstantBuffers(3, 1, &m_MaterialBuffer);
	m_DeviceContext->PSSetConstantBuffers(3, 1, &m_MaterialBuffer);


	bufferDesc.ByteWidth = sizeof(LIGHT);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_LightBuffer);
	m_DeviceContext->VSSetConstantBuffers(4, 1, &m_LightBuffer);
	m_DeviceContext->PSSetConstantBuffers(4, 1, &m_LightBuffer);

	bufferDesc.ByteWidth = sizeof(Pollar);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_PollarBuffer);
	m_DeviceContext->VSSetConstantBuffers(5, 1, &m_PollarBuffer);
	m_DeviceContext->PSSetConstantBuffers(5, 1, &m_PollarBuffer);

	bufferDesc.ByteWidth = sizeof(Fade);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_FadeBuffer);
	m_DeviceContext->VSSetConstantBuffers(6, 1, &m_FadeBuffer);
	m_DeviceContext->PSSetConstantBuffers(6, 1, &m_FadeBuffer);

	bufferDesc.ByteWidth = sizeof(Bloom);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_BloomBuffer);
	m_DeviceContext->VSSetConstantBuffers(7, 1, &m_BloomBuffer);
	m_DeviceContext->PSSetConstantBuffers(7, 1, &m_BloomBuffer);

	bufferDesc.ByteWidth = sizeof(RotationAngle);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_RotationBuffer);
	m_DeviceContext->VSSetConstantBuffers(8, 1, &m_RotationBuffer);
	m_DeviceContext->PSSetConstantBuffers(8, 1, &m_RotationBuffer);

	bufferDesc.ByteWidth = sizeof(ScaleShader);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_ScaleBuffer);
	m_DeviceContext->VSSetConstantBuffers(9, 1, &m_ScaleBuffer);
	m_DeviceContext->PSSetConstantBuffers(9, 1, &m_ScaleBuffer);

	// ���C�g������
	LIGHT light{};
	light.Enable = true;
	light.Direction = Vector4(0.5f, -1.0f, 0.8f, 0.0f);
	light.Direction.Normalize();
	light.Ambient = Color(0.2f, 0.2f, 0.2f, 1.0f);
	light.Diffuse = Color(1.5f, 1.5f, 1.5f, 1.0f);
	SetLight(light);



	// �}�e���A��������
	MATERIAL material{};
	material.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = Color(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	//�|�[��������
	Pollar pollar{};
	pollar.baseColor = { 0.0f,1.0f,0.0f,1.0f };//�x�[�X�J���[
	pollar.diffColor = { 1.0f,0.4f,0.0f,1.0f };
	pollar.lostColor = { 0.2f,0.2f,0.2f,1.0f };
	pollar.outer = 1.0f;
	pollar.inner = 0.3f;
	pollar.gauge1 = 1.0f - ((int)fmod(1, 7.0f) + 1) / 7.0f;
	pollar.gauge2 = 1.0f - fmodf(0.5, 7.0f) / 7.0f;

	SetPollar(pollar);

	//�t�F�[�h������
	Fade fade{};
	fade.alpha = 1.0f;

	SetFade(fade);

	//�u���[��
	Bloom bloom{};
	bloom.bloom = 1.0f;
	bloom.power = 5.0f;

	SetBloom(bloom);

	//��]
	RotationAngle rot{};
	rot.rotationAngle = { 0.0f,0.0f };

	SetRotationAngle(rot);

	//�T�C�Y�ύX
	ScaleShader scale{};
	scale.circlePosition = { 0.0f,0.0f };
	scale.circleRadius = 10.0f;
	scale.screenSize = { 1.0f,1.0f };

	SetScaleShader(scale);	
}




void Renderer::SetDepthEnable( bool Enable )
{
	if( Enable )
		m_DeviceContext->OMSetDepthStencilState( m_DepthStateEnable, NULL );
	else
		m_DeviceContext->OMSetDepthStencilState( m_DepthStateDisable, NULL );

}



void Renderer::SetATCEnable( bool Enable )
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	if (Enable)
		m_DeviceContext->OMSetBlendState(m_BlendStateATC, blendFactor, 0xffffffff);
	else
		m_DeviceContext->OMSetBlendState(m_BlendState[0], blendFactor, 0xffffffff);

}

void Renderer::SetWorldViewProjection2D()
{
	Matrix world;
	world = Matrix::Identity;			// �P�ʍs��ɂ���
	world = world.Transpose();			// �]�u
	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);

	Matrix view;
	view = Matrix::Identity;
	view = view.Transpose();
	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);

	Matrix projection;

	// 2D�`������㌴�_�ɂ���
	projection = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f,
		static_cast<float>(m_Application->GetWidth()),					// �r���[�{�����[���̍ŏ��w
		static_cast<float>(m_Application->GetHeight()),					// �r���[�{�����[���̍ŏ��x
		0.0f,															// �r���[�{�����[���̍ő�x
		0.0f,
		1.0f);


	projection = projection.Transpose();

	m_DeviceContext->UpdateSubresource( m_ProjectionBuffer, 0, NULL, &projection, 0, 0 );
}


void Renderer::SetWorldMatrix( Matrix* WorldMatrix )
{
	Matrix world;
	world = WorldMatrix->Transpose();					// �]�u

	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);
}

void Renderer::SetViewMatrix(Matrix* ViewMatrix )
{
	Matrix view;
	view = ViewMatrix->Transpose();						// �]�u

	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);
}

void Renderer::SetProjectionMatrix( Matrix* ProjectionMatrix )
{
	Matrix projection;
	projection = ProjectionMatrix->Transpose();

	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);
}



void Renderer::SetMaterial( MATERIAL Material )
{
	m_DeviceContext->UpdateSubresource( m_MaterialBuffer, 0, NULL, &Material, 0, 0 );
}

void Renderer::SetLight( LIGHT Light )
{
	m_DeviceContext->UpdateSubresource(m_LightBuffer, 0, NULL, &Light, 0, 0);
}

void Renderer::SetPollar(Pollar pol)
{
	m_DeviceContext->UpdateSubresource(m_PollarBuffer, 0, NULL, &pol, 0, 0);
}

void Renderer::SetFade(Fade fade)
{
	m_DeviceContext->UpdateSubresource(m_FadeBuffer, 0, NULL, &fade, 0, 0);
}

void Renderer::SetBloom(Bloom bloom)
{
	m_DeviceContext->UpdateSubresource(m_BloomBuffer, 0, NULL, &bloom, 0, 0);
}

void Renderer::SetRotationAngle(RotationAngle rot)
{
	m_DeviceContext->UpdateSubresource(m_RotationBuffer, 0, NULL, &rot, 0, 0);
}

void Renderer::SetScaleShader(ScaleShader scale)
{
	m_DeviceContext->UpdateSubresource(m_ScaleBuffer, 0, NULL, &scale, 0, 0);
}





void Renderer::CreateVertexShader( ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName )
{

	FILE* file;
	long int fsize;

	fopen_s(&file,FileName, "rb");
	assert(file);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	HRESULT hr = m_Device->CreateVertexShader(buffer, fsize, NULL, VertexShader);
	if (FAILED(hr))
	{
		std::cout << "Vertex shader creation failed! Error code: 0x" << std::hex << hr << std::endl;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONEINDEX",	0, DXGI_FORMAT_R32G32B32A32_SINT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONEWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	m_Device->CreateInputLayout(layout,
		numElements,
		buffer,
		fsize,
		VertexLayout);

	delete[] buffer;
}



void Renderer::CreatePixelShader( ID3D11PixelShader** PixelShader, const char* FileName )
{
	FILE* file;
	long int fsize;

	fopen_s(&file, FileName, "rb");
	assert(file);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	m_Device->CreatePixelShader(buffer, fsize, NULL, PixelShader);

	delete[] buffer;
}