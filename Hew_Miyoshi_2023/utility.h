#pragma once
#include	<functional>
#include	<thread>
#include    <filesystem>
#include    <d3d11.h>
#include    <string>
#include    <locale.h>
#include    <d3dcompiler.h>
#include    <vector>
#include	<iostream>
#include    <SimpleMath.h>
#include	"WICTextureLoader.h"
#include	<directXtex.h>
#include	"DDSTextureLoader.h"

#include    <assimp\Importer.hpp>
#include    <assimp\scene.h>
#include    <assimp\postprocess.h>
#include    <assimp/cimport.h>


void Invoke(std::function<void()> Function, int Time);

HRESULT CompileShader(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, void** ShaderObject, size_t& ShaderObjectSize, ID3DBlob** ppBlobOut);

//--------------------------------------------------------------------------------------
// シェーダーファイルを読み込む
//--------------------------------------------------------------------------------------
bool readShader(const char* csoName, std::vector<unsigned char>& byteArray);
//--------------------------------------------------------------------------------------
// ファイルの拡張子を取得する
//--------------------------------------------------------------------------------------
std::string GetFileExt(std::string filepath);
//--------------------------------------------------------------------------------------
// シェーダーをコンパイル
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
/*------------------------
 Structuredバッファを作成
--------------------------*/
bool CreateStructuredBuffer(
    ID3D11Device* device,
    unsigned int stride,				// ストライドバイト数
    unsigned int num,					// 個数
    void* data,							// データ格納メモリ先頭アドレス
    ID3D11Buffer** pStructuredBuffer	// RWStructuredBuffer
);
/*------------------------
 Structuredバッファを作成
--------------------------*/
bool CreateStructuredBufferWrite(
    ID3D11Device* device,
    unsigned int stride,				// ストライドバイト数
    unsigned int num,					// 個数
    void* data,							// データ格納メモリ先頭アドレス
    ID3D11Buffer** pStructuredBuffer	// RWStructuredBuffer
);
/*------------------------
    ShaderResourceViewを作成
--------------------------*/
bool CreateShaderResourceView(
    ID3D11Device* device,
    ID3D11Buffer* pBuffer,	// Buffer
    ID3D11ShaderResourceView** ppSRV);
/*------------------------
UnOrderedAccessViewを作成
--------------------------*/
bool CreateUnOrderAccessView(
    ID3D11Device* device,
    ID3D11Buffer* pBuffer,	                    // Buffer
    ID3D11UnorderedAccessView** ppUAV);
/*---------------------------------
STAGINGバッファを作成しコピーする
----------------------------------*/
ID3D11Buffer* CreateAndCopyToBuffer(
    ID3D11Device* device,
    ID3D11DeviceContext* devicecontext,
    ID3D11Buffer* pBuffer	// RWStructuredBuffer
);
/*------------------------
頂点バッファを作成
--------------------------*/
bool CreateVertexBuffer(
    ID3D11Device* device,
    unsigned int stride,				// １頂点当たりバイト数
    unsigned int vertexnum,				// 頂点数
    void* vertexdata,					// 頂点データ格納メモリ先頭アドレス
    ID3D11Buffer** pVertexBuffer		// 頂点バッファ
);
/*------------------------
頂点バッファを作成(ＣＰＵ書き込み可能)
--------------------------*/
bool CreateVertexBufferWrite(
    ID3D11Device* device,
    unsigned int stride,				// １頂点当たりバイト数
    unsigned int vertexnum,				// 頂点数
    void* vertexdata,					// 頂点データ格納メモリ先頭アドレス
    ID3D11Buffer** pVertexBuffer		// 頂点バッファ
);
/*------------------------
頂点バッファ(UAV)を作成
--------------------------*/
bool CreateVertexBufferUAV(
    ID3D11Device* device,
    unsigned int stride,				// １頂点当たりバイト数
    unsigned int vertexnum,				// 頂点数
    void* vertexdata,					// 頂点データ格納メモリ先頭アドレス
    ID3D11Buffer** pVertexBuffer		// 頂点バッファ
);

bool CreateConstantBuffer(
    ID3D11Device* device,
    unsigned int bytesize,
    ID3D11Buffer** pConstantBuffer			// コンスタントバッファ
);

/*----------------------------
コンスタントバッファを作成(MAPで書き換え可能)
------------------------------*/
bool CreateConstantBufferWrite(
    ID3D11Device* device,					// デバイスオブジェクト
    unsigned int bytesize,					// コンスタントバッファサイズ
    ID3D11Buffer** pConstantBuffer			// コンスタントバッファ
);

// ファイルパスからファイル名だけを取得する
std::string GetFileName(std::string filepath);

bool CreateSRVfromFile(
    const char* filename,
    ID3D11Device* device,
    ID3D11DeviceContext* device11Context,
    ID3D11ShaderResourceView** srv);


bool CreateSRVfromTGAFile(const char* filename,					// TGAファイルからシェーダーリソースビューを作成する
    ID3D11Device* device,
    ID3D11ShaderResourceView** srv);

bool CreateSRVfromWICFile(const char* filename,					// WICファイルからシェーダーリソースビューを作成する
    ID3D11Device* device,
    ID3D11DeviceContext* device11Context,
    ID3D11ShaderResourceView** srv);

// ファイルパスからファイル名だけを取得する
std::wstring GetFileNameWide(std::string filepath);

// ファイルパスから親ディレクトリを取得する
std::wstring GetParentDirectoryWide(std::string filepath);

bool CreateVertexShader(ID3D11Device* device,						// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
    const char* szFileName,
    LPCSTR szEntryPoint,
    LPCSTR szShaderModel,
    D3D11_INPUT_ELEMENT_DESC* layout,
    unsigned int numElements,
    ID3D11VertexShader** ppVertexShader,
    ID3D11InputLayout** ppVertexLayout);

bool CreatePixelShader(ID3D11Device* device,						// ピクセルシェーダーオブジェクトを生成
    const char* szFileName,
    LPCSTR szEntryPoint,
    LPCSTR szShaderModel,
    ID3D11PixelShader** ppPixelShader);

bool CreateIndexBuffer(
    ID3D11Device* device,
    unsigned int indexnum,	// 頂点数
    void* indexdata,							// インデックスデータ格納メモリ先頭アドレス
    ID3D11Buffer** pIndexBuffer);


void Invoke(std::function<void()> Function, int Time);