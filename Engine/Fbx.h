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
		Texture* pNormalmap;
		XMFLOAT4	diffuse;	
		XMFLOAT4 ambient;	
		XMFLOAT4 specular;	
		float shiness;	
	};

	//�R���X�^���g�o�b�t�@
	struct CONSTANT_BUFFER
	{
		XMMATRIX matW;		//���[���h�s��
		XMMATRIX matWVP;	//���[���h�E�r���[�E�v���_�N�V�����̍����s��
		XMMATRIX matNormal;	//�@���ό`�p�̍s��
		XMFLOAT4 camPos;	//�J�����̈ʒu
		XMFLOAT4 color;	//�}�e���A���̐F
		XMFLOAT4 ambient;	//����
		XMFLOAT4 specular;	//�n�C���C�g�̐F
		float shiness;	//�n�C���C�g�̋���
		int	 isTexture;	//�e�N�X�`�������邩�ǂ����𔻒f
	};

	//���@�[�e�b�N�X
	struct VERTEX
	{
		XMVECTOR position;	
		XMVECTOR uv;		
		XMVECTOR normal;	
		XMVECTOR tangent;
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