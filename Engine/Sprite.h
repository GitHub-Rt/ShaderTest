#pragma once
#include "Direct3D.h"
#include "Texture.h"
#include "Transform.h"

#define SAFE_DELETE_ARRAY(p) if(p != nullptr){ delete[] p; p = nullptr;}

//四角形ポリゴン（三角形を２枚）を描画するクラス
class Sprite
{
	//コンスタントバッファー
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;		//ワールド行列
	};

	//頂点情報
	struct VERTEX
	{
		XMVECTOR position;	//位置
		XMVECTOR uv;		//UV
	};
protected:
	//頂点関連
	DWORD	vertexNum_;		//頂点数
	VERTEX* vertices_;		//頂点情報
	ID3D11Buffer* pVertexBuffer_;		//頂点バッファ

	//インデックス関連
	DWORD indexNum;			//インデックス数
	int* index_;			//インデックス情報
	ID3D11Buffer* pIndexBuffer_;		//インデックスバッファ

	//コンスタント関連
	ID3D11Buffer* pConstantBuffer_;		//コンスタントバッファ

	//テクスチャ関連
	Texture* pTexture_;		//テクスチャ


public:
	Sprite();
	~Sprite();

	//初期化（ポリゴンを表示するための各種情報を準備）
	//戻値：成功／失敗
	HRESULT Initialize(std::string fileName);

	//描画
	//引数：transform	トランスフォームオブジェクト
	void Draw(Transform& transform);

	//解放
	void Release();



private:
	//---------Initializeから呼ばれる関数---------
	virtual void InitVertexData();		//頂点情報の準備
	HRESULT CreateVertexBuffer();		//頂点バッファを作成

	virtual void InitIndexData();		//インデックス情報を準備
	HRESULT CreateIndexBuffer();		//インデックスバッファを作成

	HRESULT CreateConstantBuffer();		//コンスタントバッファ作成

	HRESULT LoadTexture(std::string fileName);				//テクスチャをロード


	//---------Draw関数から呼ばれる関数---------
	void PassDataToCB(DirectX::XMMATRIX worldMatrix);	//コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline();							//各バッファをパイプラインにセット
};