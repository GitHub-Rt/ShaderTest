#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"

#pragma comment(lib, "LibFbxSDK-MT.lib")
#pragma comment(lib, "LibXml2-MT.lib")
#pragma comment(lib, "zlib-MT.lib")

class Texture;

class Fbx
{
	//マテリアル
	struct MATERIAL
	{
		Texture* pTexture;
		Texture* pNormalmap;
		XMFLOAT4	diffuse;	
		XMFLOAT4 ambient;	
		XMFLOAT4 specular;	
		float shiness;	
	};

	//コンスタントバッファ
	struct CONSTANT_BUFFER
	{
		XMMATRIX matW;		//ワールド行列
		XMMATRIX matWVP;	//ワールド・ビュー・プロダクションの合成行列
		XMMATRIX matNormal;	//法線変形用の行列
		XMFLOAT4 camPos;	//カメラの位置
		XMFLOAT4 color;	//マテリアルの色
		XMFLOAT4 ambient;	//環境光
		XMFLOAT4 specular;	//ハイライトの色
		float shiness;	//ハイライトの強さ
		int	 isTexture;	//テクスチャがあるかどうかを判断
	};

	//ヴァーテックス
	struct VERTEX
	{
		XMVECTOR position;	
		XMVECTOR uv;		
		XMVECTOR normal;	
		XMVECTOR tangent;
	};

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;

	int* indexCount_;

public:
	Fbx();
	~Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();

private:
	void InitVertex(fbxsdk::FbxMesh* pMesh);
	void InitIndex(fbxsdk::FbxMesh* pMesh);
	void IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
};