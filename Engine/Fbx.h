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
	//�}�e���A��
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4	diffuse;	
	};

	//�R���X�^���g�o�b�t�@
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;			//���[���h�E�r���[�E�v���_�N�V�����̍����s��
		XMMATRIX	matNormal;		//�@���ό`�p�̍s��
		XMFLOAT4	diffuseColor;	//�}�e���A���̐F
		int			isTexture;		//�e�N�X�`�������邩�ǂ����𔻒f
	};

	//���@�[�e�b�N�X
	struct VERTEX
	{
		XMVECTOR position;	
		XMVECTOR uv;		
		XMVECTOR normal;	
	};

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�

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