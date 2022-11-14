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
		XMFLOAT4	diffuse;	
	};

	//コンスタントバッファ
	struct CONSTANT_BUFFER
	{
		XMMATRIX matWVP;
		XMFLOAT4 color;
		int	 isTexture;

		//XMMATRIX	matWVP;			//ワールド・ビュー・プロダクションの合成行列
		//XMMATRIX	matNormal;		//法線変形用の行列
		//XMFLOAT4	diffuseColor;	//マテリアルの色
		//int			isTexture;		//テクスチャがあるかどうかを判断
	};

	//ヴァーテックス
	struct VERTEX
	{
		XMVECTOR position;	
		XMVECTOR uv;		
		XMVECTOR normal;	
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